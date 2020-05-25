#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>

WebServer server ( 80 );

/// ESTABLECEMOS LA RED A LA QUE NOS VAMOS A CONECTAR ///////

const char* ssid ="INFINITUM49F7";
const char* password = "AMJr1mgK2K";

//Variables Globales

String LEDpwm = "0";
int contaux = 30;
bool bandera_sistema = 0;
bool flag = 0;

/// CONFIFGURAMOS ENTRADAS Y SALIDAS GPIO ////////

//SENSOR
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



///////PARA EL MANEJO DE INTERRUPCIONES///////////////
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


//////PARA EL PWM/////////////////////////////////////
int ledPwm = 13;      //SELECCIONAMOS EL PIN DE SALIDA GPIO
int ledPwm1 = 12;      //SELECCIONAMOS EL PIN DE SALIDA GPIO
int ledPwm2 = 14;      //SELECCIONAMOS EL PIN DE SALIDA GPIO
int freq = 5000;      //CONFIGURACIONES DE PWM
int resolution = 8;
int ledChannel = 0;
int ledChannel_1 = 1;


/////////////////////////////////////////////////////

void setup() 
{
  pinMode(TRIG, OUTPUT);  // trigger como salida
  pinMode(ECO, INPUT);    // echo como entrada
 pinMode(LED, OUTPUT);   // LED como salida
  //Serial.begin(9600);     // inicializacion de comunicacion serial a 9600 bps
  pinMode(LEDPIN, OUTPUT);   //ESTABLECEMOS LOS PINES DE SALIDA
  pinMode(ledPin, OUTPUT);
  pinMode(ledPwm, OUTPUT);
  Serial.begin(9600);
  connectToWifi();
  beginServer();

  //////////PARA EL MANEJO DE INTERRUPCIONES POR TIMER//////////
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 1000000, true);
  timerAlarmEnable(timer);
  //////////////////////////////////////////////////////////////

  /////////PARA EL MANEJO DE PWM (CONFIGURACIÓN) ///////////////////////////////
    // configure LED PWM functionalitites
    ledcSetup(ledChannel, freq, resolution);
    // attach the channel to the GPIO to be controlled
    ledcAttachPin(ledPwm, ledChannel);
    
     // configure LED PWM1 functionalitites
    ledcSetup(ledChannel_1, freq, resolution);
    // attach the channel to the GPIO to be controlled
    ledcAttachPin(ledPwm1, ledChannel_1);

  //////////////////////////////////////////////////////////////
}

void loop() { //CICLO INFINITO
 
 server.handleClient(); //INICIAMOS EL CLIENTE
 getTemperature();      //INICIAMOS LA CONVERSION DE TEMPERATURA
 delay(250);

 ////////////////////////////////////SENSOR
 digitalWrite(TRIG, HIGH);     // generacion del pulso a enviar
  delay(1);       // al pin conectado al trigger
  digitalWrite(TRIG, LOW);    // del sensor
  
  DURACION = pulseIn(ECO, HIGH);  // con funcion pulseIn se espera un pulso
            // alto en Echo
  DISTANCIA = DURACION / 58.2;    // distancia medida en centimetros
  Serial.println(DISTANCIA);    // envio de valor de distancia por monitor serial
  delay(200);       // demora entre datos

    if (DISTANCIA <= 12 && DISTANCIA >= 0){  // si distancia entre 0 y 20 cms.
    digitalWrite(LED, HIGH);      // enciende LED
    Serial.println("Enciende LED D:");
    delay(DISTANCIA * 10);      // demora proporcional a la distancia
    digitalWrite(LED, LOW);     // apaga LED
    }   
   
    
    
 /////CONTADOR DE INTERRUPCIONES//////////////////////////////
 if (interruptCounter > 0) {
  
    portENTER_CRITICAL(&timerMux);
    interruptCounter--;
    portEXIT_CRITICAL(&timerMux);
 
    totalInterruptCounter++;
 
    Serial.print("An interrupt as occurred. Total number: ");
    Serial.println(totalInterruptCounter);

    //ESTABLECEMOS EL NUMERO DE INTERRUPCIONES A CONTAR PARA REALIZAR UNA ACCION
    if (totalInterruptCounter == 10){ //CONTADOR :)
      
         Serial.print(LEDpwm);
        if(banderaInterrupciones == 0 && flag != 1){
          
             digitalWrite(ledPin, HIGH);

             
   
             banderaInterrupciones = 1;     
        }else{
             digitalWrite(ledPin, LOW);
             
             banderaInterrupciones = 0;
        }
     
        totalInterruptCounter=0;
      }

      if(bandera_sistema == 1){
            contaux --;
            
        }

     if(contaux == 0){
              
       ledcWrite(ledChannel, 0);         // PMW1
      ledcWrite(ledChannel_1, 0);        // PWM2
      digitalWrite(ledPin, LOW);        //  LED PAGINA
      digitalWrite(LEDPIN, LOW);        //LED INTERRUPCIONES
      contaux = 30;
      flag = 1;
 
  
     }
    Serial.print("CONTADOR_AUX:");
     Serial.println(contaux);
  }
////////////////////////////////////////////////////////////////


}

void connectToWifi()
{
  WiFi.enableSTA(true);
  
  delay(2000);

  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print("No conecta :(");
    }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");

  Serial.println(WiFi.localIP());
}

void beginServer()
{
  server.on ( "/", handleRoot );
  server.begin();
  Serial.println ( "HTTP server started" );
}

void handleRoot(){ 
  if ( server.hasArg("LED") ) {
    handleSubmit();
  } else {
    server.send ( 200, "text/html", getPage() );
  }  
}

/////CONVERTIDOR ANALÓGICO DIGITAL/////////////////////////
void getTemperature()
{
  temperature =  ((analogRead(SENSORPIN) * 500 )/4096.0);
  //Serial.println(analogRead(SENSORPIN));
  Serial.println(WiFi.localIP());
}
//////////////////////////////////////////////////////////

//FUNCION QUE VERIFICA TODOS LOS VALORES RECIBIDOS POR LA PAGINA WEB ////
void handleSubmit() {

  String LEDValue;
  String DowmSystem;
  
  
  LEDValue = server.arg("LED");
  LEDpwm = server.arg("PWM");
  DowmSystem = server.arg("SISTEMA");

  
  Serial.println("Set GPIO "); 
  Serial.print(LEDValue);
  
  ledcWrite(ledChannel, LEDpwm.toInt());        // EL VALOR DEL PWM PUEDE IR DE 0 A 255
  ledcWrite(ledChannel_1, LEDpwm.toInt());        // EL VALOR DEL PWM PUEDE IR DE 0 A 255
 
  
  if ( LEDValue == "1" ) {
    digitalWrite(LEDPIN, HIGH);
    ledState = "On";
    server.send ( 200, "text/html", getPage() );
  }
  else if( LEDValue == "0" ) 
  {
    digitalWrite(LEDPIN, LOW);
    ledState = "Off";
    server.send ( 200, "text/html", getPage() );
  } else 
  {
    Serial.println("Error Led Value");
  }

  if( DowmSystem  == "0"){
    
    bandera_sistema = 1;
  }

  
}

//CONTIENE TODO EL CÓDIGO DE LA PAGINA WEB
String getPage(){
  String page= "<html lang=en-EN><head><meta http-equiv='refresh' content='60'/>";
  page +="  <head>";
  page +="  <link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/3.4.0/css/bootstrap.min.css'>";
  page +="  <script src='https://maxcdn.bootstrapcdn.com/bootstrap/3.4.0/js/bootstrap.min.js'></script>";
  page +="  <script src='https://ajax.googleapis.com/ajax/libs/jquery/3.4.1/jquery.min.js'></script>";
  page +="  <title>WebServer ESP32</title>";
  page +="  <style>";
  page +="    .nav{";
  page +="        background: #202753;";
  page +="        font-size: 15px;";
  page +="      color: #d8bdfa;";
  page +="      text-align: center;";
  page +="    }";
  page +="    .back{";
  page +="      background: #1b374f;";
  page +="    }";
  page +="    .foot{";
  page +="      background: #121111;";
  page +="      position: absolute;";
  page +="      bottom: 0;";
  page +="        width: 100%;";
  page +="        height: 26%;";
  page +="      overflow: hidden;";
  page +="      color: #b4b3b3;";
  page +="    }";
  page +="    .parrafoLabel{";
  page +="      color: white;";
  page +="      text-align: center;";
  page +="      margin-top: 20px;";
  page +="      bottom: 5px;";
  page +="      font-size:15px;";
  page +="    }";
  page +="    .parrafoTemperatura{";
  page +="      color: white;";
  page +="      text-align: center;";
  page +="      margin-top: 20px;   ";
  page +="      font-size:15px;";
  page +="    }";
  page +="    .finalFooter{";
  page +="      background: #242424;";
  page +="      font-size: 15px;";
  page +="      width: 100%;";
  page +="      height: 38%;";
  page +="      text-align: center;";
  page +="      color:#d0d0d0;";
  page +="    }";
  page +="    .prueba{";
  page +="      padding:11px;";
  page +="      height:25%;";
  page +="    }";
  page +="    .resultado{";
  page +="      margin-top: 5px;";
  page +="      text-align: center;";
  page +="      font-size: 45px;";
  page +="      color: white;";
  page +="    }";
  page +="    .botonEnviar{";
  page +="      margin-top: 10px;";
  page +="    }";
  page +="    @media (max-width: 600px){";
  page +="      .back{";
  page +="        background: #1b374f;";
  page +="        }";
  page +="    .foot{";
  page +="      background: #121111;";
  page +="      position: relative;";
  page +="      margin-top: 30px;";
  page +="        width: 100%;";
  page +="        height: 40%;";
  page +="      color: #b4b3b3;";
  page +="      overflow: visible;";
  page +="      }";
  page +="    .finalFooter{";
  page +="      background: #242424;";
  page +="      font-size: 10px;";
  page +="      width: 100%;";
  page +="      height: 35%;";
  page +="      text-align: center;";
  page +="      color:#d0d0d0;";
  page +="      }";
  page +="    }";
  page +="    </style>";
  page +="</head>";
  page +="<body class='back'>";
  page +="<p class='nav'> ESP32 WebSever</p>";
  page +="  <p class='parrafoLabel'> TEMPERATURA: </p>";
  page +="  <div class='resultado'>";
  page +=    temperature;
  page +="   &deg;C";
  page +="  </div>";
  page +="  <p class='parrafoTemperatura'> ESTADO LED: </p>";
  page +="  <div style='text-align: center; font-size: 30px; color:white;'> ";
  page +="    <br>";
  page +="    <form action='/' method='POST'>";
  page +="    <INPUT type='radio' name='LED' value='1'>ON";
  page +="    <INPUT type='radio' name='LED' value='0'>OFF";
  page +="    <br>";
  page +="    <br>";
  page +="     <INPUT type='radio' name='SISTEMA' value='0'>DOWN SYSTEM";
  page +="      <div class ='contenedor'>";
  page +="        <div class='slidecontainer'>";
  page +="          <INPUT type='range' name='PWM' min='1' max='255' value='50' class='slider' id='myRange'>";
  page +="          <p>Value: <span id='demo'></span></p>";
  page +="        </div>";
  page +="     </div>";
  page +="   <script>";
  page +="     var slider = document.getElementById('myRange')";
  page +="     var output = document.getElementById('demo')";
  page +="     output.innerHTML = slider.value";
  page +="     slider.oninput = function() {";
  page +="     output.innerHTML = this.value;0 }";
  page +="   </script>";
  page +="      <INPUT class='btn btn-success' type='submit' value='Enviar'>";
  page +="  </form>";
  page +="  </div>";
  page +="<footer class='foot'>";
  page +="    <div class='row'>";
  page +="      <div class='col-md-6 mt-md-0 mt-3'>";
  page +="        <p style='margin: 10px;'>PROYECTO FINAL:</p>";
  page +="        <p style= 'margin: 10px;'>Sistema Casa Inteligente con ESP32</p>";
  page +="      </div>";
  page +="    <div class='col-md-3 mb-md-0 mb-3'>";
  page +="        <h5 class='text-uppercase'>Autores:</h5>";
  page +="        <ul class='list-unstyled'>";
  page +="          <li>";
  page +="            <a href='#!'>Corella Perez Elda</a>";
  page +="          </li>";
  page +="          <li>";
  page +="            <a href='#!'>Fuentes Samaniego Irving</a>";
  page +="          </li>";
  page +="        </ul>";
  page +="      </div>";
  page +="    <div class='col-md-3 mb-md-0 mb-3'>";
  page +="        <h5 class='text-uppercase'>PROFESOR:</h5>";
  page +="        <ul class='list-unstyled'>";
  page +="          <li>";
  page +="            <a href='#!'>Ing.Ruben Anaya Garcia</a>";
  page +="          </li>";
  page +="        </ul>";
  page +="      </div>";
  page +="    </div>";
  page +="  <div class='finalFooter'>";
  page +="    <p class='prueba'>Microcomputadoras</p>";
  page +="    <p>©Semestre 2020-1</p>";
  page +="  </div>";
  page +="</footer>";
  page +="</body>";
  page +="</html>";
  return page;
}
