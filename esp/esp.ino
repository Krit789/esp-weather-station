#include <FS.h>          //this needs to be first, or it all crashes and burns...
#include <WiFiManager.h> //https://github.com/tzapu/WiFiManager

#ifdef ESP32
#include <SPIFFS.h>
#endif

#include <ArduinoJson.h> //https://github.com/bblanchon/ArduinoJson
#include <LCD_I2C.h>
// select which pin will trigger the configuration portal when set to LOW
#define TRIGGER_PIN 0

u_short timeout = 90; // seconds to run for

// define your default values here, if there are different values in config.json, they are overwritten.
char api_server[60];

// flag for saving data
bool shouldSaveConfig = false;

unsigned long currentMillis, startMillis;

// WiFiManager
WiFiManager wifiManager;

// LCD Initialization
LCD_I2C lcd(0x27, 16, 2);

// callback notifying us of the need to save config
void saveConfigCallback()
{
  Serial.println("Should save config");
  shouldSaveConfig = true;
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
  WiFiManagerParameter custom_api_server("server", "Forecaster API Server", api_server, 60);

  // set config save notify callback
  wifiManager.setSaveConfigCallback(saveConfigCallback);

  // set static ip
  //  wifiManager.setSTAStaticIPConfig(IPAddress(10, 0, 1, 99), IPAddress(10, 0, 1, 1), IPAddress(255, 255, 255, 0));

  // add all your parameters here
  wifiManager.addParameter(&custom_api_server);

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
}

void loop()
{
  lcd.setCursor(0, 0);
  lcd.print("      Ready     ");
  // lcd.noBacklight();
  // is configuration portal requested?
  if (digitalRead(TRIGGER_PIN) == LOW)
  {
    // set configportal timeout
    wifiManager.setConfigPortalTimeout(timeout);
    Serial.println("Started Config Portal");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("90sec Web Portal");
    lcd.setCursor(0, 1);
    lcd.print("Config over Wifi");
    delay(700);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SSID:      ");
    lcd.setCursor(0, 1);
    lcd.print("The Forecaster");
    delay(3000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("PW: forecaster");
    lcd.setCursor(0, 1);
    lcd.print("    -itkmitl");
    delay(3000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(" Webpage ");
    lcd.setCursor(0, 1);
    lcd.print(" IP: 192.168.4.1");
    // lcd.backlight();
    if (!wifiManager.startConfigPortal("The Forecaster", "forecaster-itkmitl"))
    {
      Serial.println("Config Portal Timeout... restarting");
      delay(3000);
      // reset and try again, or maybe put it to deep sleep
      ESP.restart();
      delay(5000);
    }

    // if you get here you have connected to the WiFi
    Serial.println("connected...yeey :)");
  }

  // Server POST Request
  currentMillis = millis();  //get the current "time" (actually the number of milliseconds since the program started)
  if (currentMillis - startMillis >= 5000)  //test whether the period has elapsed
  {


    startMillis = currentMillis;  //IMPORTANT to save the start time of the current LED state.
  }


  // put your main code here, to run repeatedly:
}