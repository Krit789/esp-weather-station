#include <FS.h>          //this needs to be first, or it all crashes and burns...
#include <WiFiManager.h> //https://github.com/tzapu/WiFiManager
#include <WiFiClient.h>
#ifdef ESP32
#include <SPIFFS.h>
#endif

#include <ArduinoJson.h> //https://github.com/bblanchon/ArduinoJson
#include <LCD_I2C.h>
#include <ESP8266HTTPClient.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"

// select which pin will trigger the configuration portal when set to LOW
#define TRIGGER_PIN 0
#define SEALEVELPRESSURE_HPA (1013.25)

u_short timeout = 90; // seconds to run for
Adafruit_BME680 bme;  // I2C
// define your default values here, if there are different values in config.json, they are overwritten.
char api_server[60];

// flag for saving data
bool shouldSaveConfig = false;

unsigned long currentMillis, startMillis;
// WiFiManager
WiFiManager wifiManager;

DynamicJsonDocument doc(200);
// LCD Initialization
LCD_I2C lcd(0x27, 16, 2);

// callback notifying us of the need to save config
void saveConfigCallback()
{
  Serial.println("Should save config");
  shouldSaveConfig = true;
}
void superPrint(char *text, uint8_t col, uint8_t row)
{
  // Prints to both lcd and serial terminal
  String text_ = String(text);
  lcd.setCursor(col, row);
  lcd.print(text_);
  text_.trim();
  Serial.println(text_);
}

void hardResetESP()
{
  superPrint("Hard Resetting... ", 0, 1);

  SPIFFS.format();
  wifiManager.resetSettings();
  delay(2000);
  ESP.restart();
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println();
  pinMode(TRIGGER_PIN, INPUT_PULLUP);
  lcd.begin();
  lcd.backlight();
  superPrint("  Initializing", 0, 0);

  // read configuration from FS (FileSystem) json
  superPrint(" mounting FS... ", 0, 1);

  if (SPIFFS.begin())
  {
    Serial.println("mounted file system");
    if (SPIFFS.exists("/config.json"))
    {
      // file exists, reading and loading
      Serial.println("reading config file");
      File configFile = SPIFFS.open("/config.json", "r");
      if (configFile)
      {
        Serial.println("opened config file");
        size_t size = configFile.size();
        // Allocate a buffer to store contents of the file.
        std::unique_ptr<char[]> buf(new char[size]);

        configFile.readBytes(buf.get(), size);

        DynamicJsonDocument json(1024);
        auto deserializeError = deserializeJson(json, buf.get());
        serializeJson(json, Serial);
        if (!deserializeError)
        {
          Serial.println("\nparsed json");
          strcpy(api_server, json["api_server"]);
        }
        else
        {
          Serial.println("failed to load json config");
        }
        configFile.close();
      }
    }
  }
  else
  {
    superPrint(" mount FS failed  ", 0, 1);
  }
  // end read

  // Local intialization. Once its business is done, there is no need to keep it around

  // set config save notify callback
  wifiManager.setSaveConfigCallback(saveConfigCallback);

  // add all your parameters here
  WiFiManagerParameter custom_api_server("server", "Forecaster API Server (http only)", api_server, 60);
  wifiManager.addParameter(&custom_api_server);

  // set minimu quality of signal so it ignores AP's under that quality
  // defaults to 8%
  // wifiManager.setMinimumSignalQuality();

  // sets timeout until configuration portal gets turned off
  // useful to make it all retry or go to sleep
  // in seconds
  // wifiManager.setTimeout(120);

  // fetches ssid and pass and tries to connect
  // if it does not connect it starts an access point with the specified name
  // here  "AutoConnectAP"
  // and goes into a blocking loop awaiting configuration
  if (!wifiManager.autoConnect("The Forecaster", "forecaster-itkmitl"))
  {
    Serial.println("failed to connect and hit timeout");
    delay(3000);
    // reset and try again, or maybe put it to deep sleep
    ESP.restart();
    delay(5000);
  }

  // if you get here you have connected to the WiFi
  superPrint(" WiFi Connected ", 0, 1);

  // read updated parameters
  strcpy(api_server, custom_api_server.getValue());
  Serial.println("The values in the file are: ");
  Serial.println("\tapi_server : " + String(api_server));

  // save the custom parameters to FS
  if (shouldSaveConfig)
  {
    Serial.println("saving config");
    DynamicJsonDocument json(1024);
    json["api_server"] = api_server;

    File configFile = SPIFFS.open("/config.json", "w");
    if (!configFile)
    {
      Serial.println("failed to open config file for writing");
    }
    serializeJson(json, Serial);
    serializeJson(json, configFile);
    configFile.close();
    // end save
  }

  superPrint("    Local IP    ", 0, 0);
  Serial.println(WiFi.localIP());
  int len = WiFi.localIP().toString().length();
  lcd.setCursor((20 - len) / 2, 1);
  lcd.print(WiFi.localIP());

  // End of WiFi

  if (!bme.begin())
  {
    lcd.clear();
    superPrint("Error", 0, 0);
    superPrint("BME680 NotOn SPI", 0, 1);
    Serial.println("Could not find a valid BME680 sensor on SPI, check wiring!");
    while (1)
      ;
  }

  // Set up oversampling and filter initialization
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320*C for 150 ms
}

void loop()
{
  char buffer1[17];
  char buffer2[17];
  if (!bme.performReading())
  {
    superPrint("Sensor Read Fail", 0, 1);
    // Serial.println("Failed to perform reading :(");
    return;
  } else {
    lcd.setCursor(0, 0);
    sprintf(buffer1, "T%.2f%cC H%.1f%%", bme.temperature, char(223), bme.humidity);
    lcd.print(buffer1);

    lcd.setCursor(0, 1);
    sprintf(buffer2, "P:%6d hPa   ", bme.pressure, bme.gas_resistance);
    lcd.print(buffer2);
  }

  if (digitalRead(TRIGGER_PIN) == LOW)
  {
    hardResetESP();
  }

  // Read from sensor and send POST Request to API Server
  currentMillis = millis();                // get the current "time" (actually the number of milliseconds since the program started)
  if (currentMillis - startMillis >= 60000) // test whether the period has elapsed (in this case 5 seconds)
  {
    WiFiClient espWClient;
    HTTPClient http;
    String result;
    doc["temperature"] = bme.temperature;
    doc["humidity"] = bme.humidity;
    doc["barometric_pressure"] = bme.pressure;
    doc["gas"] = bme.gas_resistance / 1000.0;
    doc["altitude"] = bme.readAltitude(SEALEVELPRESSURE_HPA);
    serializeJson(doc, result);
    http.begin(espWClient, api_server);
    lcd.setCursor(0, 1);
    lcd.print(" Uploading Data ");
    http.addHeader("Content-Type", "application/json");
    int httpResponseCode = http.POST(result);
    Serial.print("HTTP Response code: ");
    if (httpResponseCode > 0)
    {
      Serial.println(httpResponseCode);
      if (httpResponseCode == 200) {

        lcd.setCursor(0, 1);
        lcd.print(" Data Uploaded! ");
      }
    }
    else
    {
      Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpResponseCode).c_str());
      Serial.printf("Request: %s", http.getString());
      lcd.setCursor(0, 0);
      lcd.print("Upload Failed :(");
      lcd.setCursor(0, 1);
      lcd.print(http.errorToString(httpResponseCode).c_str());
    }
    Serial.println(result);
    http.end();

    startMillis = currentMillis;
  }
}