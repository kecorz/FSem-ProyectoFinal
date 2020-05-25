#include <WiFi.h>
#include <WebServer.h>
#include "time.h"

// Global variables:

String LEDpwm = "0";
int contaux = 30;
bool bandera_sistema = 0;
bool flag = 0;

/// Input-Output configuration ////////

// Movement sensor
int TRIG = 26;      // trigger en pin 10
int ECO = 25;      // echo en pin 9
int LED = 33;      // LED en pin 3
int DURACION;
int DISTANCIA;

int LEDPIN = 32;      //CONTROLA AL LED DE PÁGINA WEB
int SENSORPIN = 34;   //CONTROLA EL SENSOR DE TEMPERATURA
int ledPin = 27;
float temperature = 0;
String  ledState = "OFF";

// Para probar utilicé el pin 4 para conectar un led:
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
bool garageDoorOpen = false;

// Esta variable se activa cuando se presiona el botón. Si es true, aparece un mensaje en la página.
// Doorbell variables:
bool doorbell = true;

//////PWM CONFIGURATION/////////////////////////////////////
int ledPwm = 13;      //SELECCIONAMOS EL PIN DE SALIDA GPIO
int ledPwm1 = 12;      //SELECCIONAMOS EL PIN DE SALIDA GPIO
int ledPwm2 = 14;      //SELECCIONAMOS EL PIN DE SALIDA GPIO
int freq = 5000;      //CONFIGURACIONES DE PWM
int resolution = 8;
int ledChannel = 0;
int ledChannel_1 = 1;


/////////////////////////////////////////////////////

///////INTERRUPTION HANDLING///////////////
volatile int interruptCounter;
int totalInterruptCounter; 
bool banderaInterrupciones=0;
 
hw_timer_t * timer = NULL; //configuraciones para el timer 
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

void IRAM_ATTR onTimer() {
  portENTER_CRITICAL_ISR(&timerMux);
  interruptCounter++;
  portEXIT_CRITICAL_ISR(&timerMux); 
}
//////////////////////////////////////////////////////


// SSID and password:
const char *ssid = "INFINITUM49F7";  // Enter SSID here
const char *password = "AMJr1mgK2K"; //Enter Password here

// Port to be used by the server:
WebServer server(80);

void setup()
{
  // Set baud rate:
  Serial.begin(115200);
  delay(100);

  // Set pin modes (input/output):
  pinMode(LED1pin, OUTPUT);

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
  server.onNotFound(handleNotFound);

  // Begin server:
  server.begin();
  Serial.println("HTTP server started");

  // Initialize time and get data from server:
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}

void loop()
{
  server.handleClient();
  lightBehavior();
  ledProgram();
}
