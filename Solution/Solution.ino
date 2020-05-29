/* 
 *  Software configuration required to set up a Smart Home Hub with an ESP32 microcontroller.
 *  Developed by:
 *  - Ricardo Hernández Gómez
 *  - Elda Corella Perez
 *  
 *  Sistemas Embebidos
 *  Universidad Nacional Autónoma de México
 *  
 *  Pin configuration:
 *  - Temperature sensor (LM35): 34
 *  - LED pin: 4
 *  - DC Motor: 
 *      Enable: 10
 *      Mot1: 11
 *      Mot2: 12 
 *        
 */


#include <WiFi.h>
#include <WebServer.h>
#include "time.h"

// Global variables:

String LEDpwm = "0";
int contaux = 30;
bool bandera_sistema = 0;
bool flag = 0;

/// Input-Output configuration ////////

int SENSORPIN = 34;   //Temperature sensor
float temperature = 0;

// Light pins:
uint8_t LED1pin = 4;
bool lightsOn = false;

// Time variables:
// Network Time Protocol server:
const char *ntpServer = "pool.ntp.org";
// Time offset in seconds for Mexico: UTC-6
const long gmtOffset_sec = -21600;
// Daylight savings offset
const int daylightOffset_sec = 3600;
// Int arrays to save time data: [Hour, Minutes, 0-AM or 1-PM]
int selectedLightOnTime[3];
int selectedLightOffTime[3];
int serverTime[3];
// Boolean variables that indicate when there's a Light change:
bool setLightOn = false;
bool setLightOff = false;

// Garage door variables:
uint8_t EN1pin = 10;
uint8_t Mot1 = 11;
uint8_t Mot2 = 12;
bool garageDoorOpen = false;

// Doorbell variables:
uint8_t doorbellpin = 16;
bool doorbell = false;

//////PWM CONFIGURATION/////////////////////////////////////
int freq = 5000;      //PWM
int resolution = 8;
int ledChannel = 0;
int ledChannel_1 = 1;

String lightIntensity = "100";


/////////////////////////////////////////////////////

// SSID and password:
const char *ssid = "INFINITUM49F7";  // Enter SSID here
const char *password = "AMJr1mgK2K"; //Enter Password here

// Port to be used by the server:
WebServer server(80);

// Initial ESP32 setup
void setup()
{
  // Set baud rate:
  Serial.begin(115200);
  delay(100);

  // Set pin modes (input/output):
  // Light
  pinMode(LED1pin, OUTPUT);
  
  // Enable Motor pin
  pinMode(EN1pin, OUTPUT);
  //Control Motor pins 
  pinMode(Mot1, OUTPUT);
  pinMode(Mot2, OUTPUT);
  //Doorbell pin
  pinMode(doorbellpin, INPUT);

  // PWM
  // configure LED PWM functionalitites
  ledcSetup(ledChannel, freq, resolution);
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(LED1pin, ledChannel);

  // Server startup data for serial:
  Serial.println("Connecting to ");
  Serial.println(ssid);

  // Wifi connection:
  WiFi.begin(ssid, password);

  // Check wifi connection:
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("- Connected to Wifi.");

  // Print assigned IP:
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  // Set server routes:
  server.on("/", handleOnConnect);
  server.on("/get", handleGet);
  server.on("/lightsOn", handleLightsOn);
  server.on("/lightsOff", handleLightsOff);
  server.on("/garageOpen", handleGarageOpen);
  server.on("/garageClose", handleGarageClose);
  server.on("/cameras", handleCameras);
  server.onNotFound(handleNotFound);

  // Begin server:
  server.begin();
  Serial.println("HTTP server started");

  // Initialize time and get data from server:
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}

// Continuosly running code:
void loop()
{
  server.handleClient();
  lightBehavior();
  doorbellBehavior();
  ledProgram();
  updateTemperature();
}
