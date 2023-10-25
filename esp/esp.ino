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
Adafruit_BME680 bme; // I2C
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

void hardResetESP()
{
  lcd.setCursor(0, 1);
  lcd.print("Hard Resetting... ");
  Serial.println("Hard Resetting FS... ");

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
  lcd.setCursor(0, 0);
  lcd.print("  Initializing");

  // read configuration from FS json
  // read configuration from FS json
  Serial.println("mounting FS...");

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

#if defined(ARDUINOJSON_VERSION_MAJOR) && ARDUINOJSON_VERSION_MAJOR >= 6
        DynamicJsonDocument json(1024);
        auto deserializeError = deserializeJson(json, buf.get());
        serializeJson(json, Serial);
        if (!deserializeError)
        {
#else
        DynamicJsonBuffer jsonBuffer;
        JsonObject &json = jsonBuffer.parseObject(buf.get());
        json.printTo(Serial);
        if (json.success())
        {
#endif
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
    Serial.println("failed to mount FS");
  }
  // end read

  // The extra parameters to be configured (can be either global or just in the setup)
  // After connecting, parameter.getValue() will get you the configured value
  // id/name placeholder/prompt default length

  // WiFiManager



  // Local intialization. Once its business is done, there is no need to keep it around

  // set config save notify callback
  wifiManager.setSaveConfigCallback(saveConfigCallback);

  // add all your parameters here
  WiFiManagerParameter custom_api_server("server", "Forecaster API Server", api_server, 60);
  wifiManager.addParameter(&custom_api_server);

  // reset settings - for testing
  // wifiManager.resetSettings();

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
  Serial.println("connected...yeey :)");

  // read updated parameters
  strcpy(api_server, custom_api_server.getValue());
  Serial.println("The values in the file are: ");
  Serial.println("\tapi_server : " + String(api_server));

  // save the custom parameters to FS
  if (shouldSaveConfig)
  {
    Serial.println("saving config");
#if defined(ARDUINOJSON_VERSION_MAJOR) && ARDUINOJSON_VERSION_MAJOR >= 6
    DynamicJsonDocument json(1024);
#else
    DynamicJsonBuffer jsonBuffer;
    JsonObject &json = jsonBuffer.createObject();
#endif
    json["api_server"] = api_server;

    File configFile = SPIFFS.open("/config.json", "w");
    if (!configFile)
    {
      Serial.println("failed to open config file for writing");
    }

#if defined(ARDUINOJSON_VERSION_MAJOR) && ARDUINOJSON_VERSION_MAJOR >= 6
    serializeJson(json, Serial);
    serializeJson(json, configFile);
#else
    json.printTo(Serial);
    json.printTo(configFile);
#endif
    configFile.close();
    // end save
  }

  Serial.println("local ip");
  Serial.println(WiFi.localIP());

  // End of WiFi 

  if (!bme.begin()) {
    Serial.println("Could not find a valid BME680 sensor on SPI, check wiring!");
    while (1);
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
  if (! bme.performReading()) {
    Serial.println("Failed to perform reading :(");
    return;
  }
  if (digitalRead(TRIGGER_PIN) == LOW)
  {
    hardResetESP();
  }

  // Server POST Request
  currentMillis = millis();                // get the current "time" (actually the number of milliseconds since the program started)
  if (currentMillis - startMillis >= 5000) // test whether the period has elapsed
  {
    WiFiClient espWClient;
    HTTPClient http;
    String result;
    doc["temperature"] = bme.temperature;
    doc["humidity"] = bme.humidity;
    doc["barometric_pressure"] = bme.pressure;
    doc["gas"] = bme.gas_resistance / 1000.0;
    serializeJson(doc, result);
    http.begin(espWClient, api_server);
    http.addHeader("Content-Type", "application/json");
    int httpResponseCode = http.POST(result);
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    Serial.println(api_server);
    // Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpResponseCode).c_str());
    // Free resources
    http.end();

    startMillis = currentMillis; // IMPORTANT to save the start time of the current LED state.
  }

  // put your main code here, to run repeatedly:
}