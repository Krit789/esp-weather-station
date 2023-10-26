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
#include <NTPClient.h>
#include <WiFiUdp.h>

// select which pin will trigger the configuration portal when set to LOW
#define TRIGGER_PIN 0
#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME680 bme; // I2C BME680 Sensor
// WiFiManager
WiFiManager wifiManager;

DynamicJsonDocument doc(200);
// LCD Initialization
LCD_I2C lcd(0x27, 16, 2);

// define your default values here, if there are different values in config.json, they are overwritten.
char api_server[60] = "http://forecast.jarukrit.net/api/sensor";
char ntp_server[60] = "time.cloudflare.com";

bool shouldSaveConfig = false; // flag for saving data

int pressureArray[10] = {0}; // here we store the pressure readings
byte counter = 0;
byte Z = 0;
byte month;

unsigned long currentMillis, startMillis;

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

void lcdCenterPrint(char *text)
{
  lcd.setCursor(0, 1);
  lcd.print(" ");
  // Prints to both lcd and serial terminal
  byte len = String(text).length();
  lcd.setCursor((20 - len) / 2, 1);
  lcd.print(text);
}

void hardResetESP()
{
  superPrint("Hard Resetting... ", 0, 1);

  SPIFFS.format();
  wifiManager.resetSettings();
  delay(2000);
  ESP.restart();
}

void beginWebUpload(){
    WiFiClient espWClient;
    HTTPClient http;
    String result;
    doc["temperature"] = bme.temperature;
    doc["humidity"] = bme.humidity;
    doc["barometric_pressure"] = bme.pressure;
    doc["gas"] = bme.gas_resistance / 1000.0;
    doc["altitude"] = bme.readAltitude(SEALEVELPRESSURE_HPA);
    doc["zambretti"] = Z;
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
      if (httpResponseCode == 200)
      {

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
}

void displayForecast(int seapressure){
  if (pressureArray[9] > 0 and pressureArray[0] > 0) {
      if (pressureArray[9] + pressureArray[8] + pressureArray[7] - pressureArray[0] - pressureArray[1] - pressureArray[2] >= 3) {
        // Raising Pressure
        lcdCenterPrint("Raising");
        if (Z < 3) {
          lcdCenterPrint("Sunny");
        }
        else if (Z >= 3 and Z <= 9) {
          lcdCenterPrint("Sunny Cloudy");
        }
        else if (Z > 9 and Z <= 17) {
          lcdCenterPrint("Cloudy");
        }
        else if (Z > 17) {
          lcdCenterPrint("Rainy");
        }
      }

      else if (pressureArray[0] + pressureArray[1] + pressureArray[2] - pressureArray[9] - pressureArray[8] - pressureArray[7] >= 3) {
        //FALLING Pressure
        lcdCenterPrint("Falling");
        if (Z < 4) {
          lcdCenterPrint("Sunny");
        }
        else if (Z >= 4 and Z < 14) {
          lcdCenterPrint("Sunny Cloudy");
        }
        else if (Z >= 14 and Z < 19) {
          lcdCenterPrint("Worsening");
        }
        else if (Z >= 19 and Z < 21) {
          lcdCenterPrint("Cloudy");
        }
        else if (Z >= 21) {
          lcdCenterPrint("Rainy");
        }
      }
      else {
        //STEADY Pressure
        lcdCenterPrint("Steady");
        if (Z < 5) {
          lcdCenterPrint("Sunny");
        }
        else if (Z >= 5 and Z <= 11) {
          lcdCenterPrint("Sunny Cloudy");
        }
        else if (Z > 11 and Z < 14) {
          lcdCenterPrint("Cloudy");
        }
        else if (Z >= 14 and Z < 19) {
          lcdCenterPrint("Worsening");
        }
        else if (Z >= 19) {
          lcdCenterPrint("Rainy");
        }
      }
    }
    else {
      if (seapressure < 1005) {
        lcdCenterPrint("Rainy");
      }
      else if (seapressure >= 1005 and seapressure <= 1015) {
        lcdCenterPrint("Cloudy");
      }
      else if (seapressure > 1015 and seapressure < 1025) {
        lcdCenterPrint("Sunny Cloudy");
      }
      else {
        lcdCenterPrint("Rainy");
      }
    }
}

int calc_zambretti(int curr_pressure, int prev_pressure, byte mon)
{
  if (curr_pressure < prev_pressure)
  {
    // FALLING
    if (mon >= 4 and mon <= 9)
    // summer
    {
      if (curr_pressure >= 1030)
        return 2;
      else if (curr_pressure >= 1020 and curr_pressure < 1030)
        return 8;
      else if (curr_pressure >= 1010 and curr_pressure < 1020)
        return 18;
      else if (curr_pressure >= 1000 and curr_pressure < 1010)
        return 21;
      else if (curr_pressure >= 990 and curr_pressure < 1000)
        return 24;
      else if (curr_pressure >= 980 and curr_pressure < 990)
        return 24;
      else if (curr_pressure >= 970 and curr_pressure < 980)
        return 26;
      else if (curr_pressure < 970)
        return 26;
    }
    else
    {
      // winter
      if (curr_pressure >= 1030)
        return 2;
      else if (curr_pressure >= 1020 and curr_pressure < 1030)
        return 8;
      else if (curr_pressure >= 1010 and curr_pressure < 1020)
        return 15;
      else if (curr_pressure >= 1000 and curr_pressure < 1010)
        return 21;
      else if (curr_pressure >= 990 and curr_pressure < 1000)
        return 22;
      else if (curr_pressure >= 980 and curr_pressure < 990)
        return 24;
      else if (curr_pressure >= 970 and curr_pressure < 980)
        return 26;
      else if (curr_pressure < 970)
        return 26;
    }
  }
  else if (curr_pressure > prev_pressure)
  {
    // RAISING
    if (mon >= 4 and mon <= 9)
    {
      // summer
      if (curr_pressure >= 1030)
        return 1;
      else if (curr_pressure >= 1020 and curr_pressure < 1030)
        return 2;
      else if (curr_pressure >= 1010 and curr_pressure < 1020)
        return 3;
      else if (curr_pressure >= 1000 and curr_pressure < 1010)
        return 7;
      else if (curr_pressure >= 990 and curr_pressure < 1000)
        return 9;
      else if (curr_pressure >= 980 and curr_pressure < 990)
        return 12;
      else if (curr_pressure >= 970 and curr_pressure < 980)
        return 17;
      else if (curr_pressure < 970)
        return 17;
    }
    else
    // winter
    {
      if (curr_pressure >= 1030)
        return 1;
      else if (curr_pressure >= 1020 and curr_pressure < 1030)
        return 2;
      else if (curr_pressure >= 1010 and curr_pressure < 1020)
        return 6;
      else if (curr_pressure >= 1000 and curr_pressure < 1010)
        return 7;
      else if (curr_pressure >= 990 and curr_pressure < 1000)
        return 10;
      else if (curr_pressure >= 980 and curr_pressure < 990)
        return 13;
      else if (curr_pressure >= 970 and curr_pressure < 980)
        return 17;
      else if (curr_pressure < 970)
        return 17;
    }
  }
  else
  {
    if (curr_pressure >= 1030)
      return 1;
    else if (curr_pressure >= 1020 and curr_pressure < 1030)
      return 2;
    else if (curr_pressure >= 1010 and curr_pressure < 1020)
      return 11;
    else if (curr_pressure >= 1000 and curr_pressure < 1010)
      return 14;
    else if (curr_pressure >= 990 and curr_pressure < 1000)
      return 19;
    else if (curr_pressure >= 980 and curr_pressure < 990)
      return 23;
    else if (curr_pressure >= 970 and curr_pressure < 980)
      return 24;
    else if (curr_pressure < 970)
      return 26;
  }
  return 0;
}

int station2sealevel(int p, int height, int t)
{ // from pressure at our height to sea level
  return (double)p * pow(1 - 0.0065 * (double)height / (t + 0.0065 * (double)height + 273.15), -5.275);
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
// hardResetESP();
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
          strcpy(ntp_server, json["ntp_server"]);
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

  // set config save notify callback
  wifiManager.setSaveConfigCallback(saveConfigCallback);

  // add all your parameters here
  WiFiManagerParameter custom_api_server("server", "Forecaster API Server (http only)", api_server, 60);
  WiFiManagerParameter custom_ntp_server("ntp_server", "NTP Server", ntp_server, 60);
  wifiManager.addParameter(&custom_api_server);
  wifiManager.addParameter(&custom_ntp_server);

  // fetches ssid and pass and tries to connect
  // if it does not connect it starts an access point with the specified name
  // here  "The Forecaster"
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
  strcpy(ntp_server, custom_ntp_server.getValue());
  Serial.println("The values in the file are: ");
  Serial.println("\tapi_server : " + String(api_server));
  Serial.println("\tntp_server : " + String(ntp_server));

  // save the custom parameters to FS
  if (shouldSaveConfig)
  {
    Serial.println("saving config");
    DynamicJsonDocument json(1024);
    json["api_server"] = api_server;
    json["ntp_server"] = ntp_server;

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

  // Syncing time with NTP Server
  WiFiUDP ntpUDP;
  NTPClient timeClient(ntpUDP, ntp_server);
  superPrint("Requesting Time ", 0, 0);
  superPrint("from NTP Server ", 0, 1);
  timeClient.begin();
  timeClient.setTimeOffset(25200);
  timeClient.update();
  time_t epochTime = timeClient.getEpochTime();
  Serial.print("Epoch Time: ");
  Serial.println(epochTime);
  struct tm *ptm = gmtime ((time_t *)&epochTime); 
  month = ptm->tm_mon + 1;

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
  }
  else
  {
    lcd.setCursor(0, 0);
    sprintf(buffer1, "T%.2f%cC H%.1f%%", bme.temperature, char(223), bme.humidity);
    lcd.print(buffer1);

    // lcd.setCursor(0, 1);
    // sprintf(buffer2, "P:%6d hPa", bme.pressure, bme.gas_resistance);
    // lcd.print(buffer2);
  }

  if (digitalRead(TRIGGER_PIN) == LOW)
  {
    hardResetESP();
  }

  int seapressure = station2sealevel((int)bme.pressure, (int)bme.readAltitude(SEALEVELPRESSURE_HPA), (int)bme.temperature);

  currentMillis = millis();                 // get the current "time" (actually the number of milliseconds since the program started)
  if (currentMillis - startMillis >= 60000) // test whether the period has elapsed (in this case 5 seconds)
  {

    if (counter == 10)  // if we read 10 values and filled up the array, we shift the array content
    {
      for (int i = 0; i < 9; i++) {   // we shift the array one position to the left
        pressureArray[i] = pressureArray[i + 1];
      }
      pressureArray[counter - 1] = seapressure;
    }
    else {        // this code fills up the pressure array value by value until is filled up
      pressureArray[counter] = seapressure;
      counter++;
    }
    Z = calc_zambretti((pressureArray[9] + pressureArray[8] + pressureArray[7]) / 3, (pressureArray[0] + pressureArray[1] + pressureArray[2]) / 3, month);
    beginWebUpload(); // Create a POST Request to api server
    startMillis = currentMillis;
  }
  displayForecast(seapressure);
}