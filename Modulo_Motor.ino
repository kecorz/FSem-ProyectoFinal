// LOGICA DE FUNCIONAMIENTO DEL MOTOR

//SE UTILIZARAN TRES PINES (DOS DIRECCIONES Y UN ENABLE)

///////// Configuraciones GPIO para motor ///////
int Mot1 = ;
int Mot2 = ;
int EnableMot = ;
int speed = 130;
int contadorMotor = 0;

void setup(){

	pinMode(Mot1, OUTPUT);
  	pinMode(Mot2, OUTPUT);
 	pinMode(EnableMot, OUTPUT);

}

void loop(){

	/// Velocidad que tendra el motor //
 		analogWrite(EnableMot,speed);
 	//digitalWrite(EnableMot, HIGH); //

_
}

void handleSubmit(){
	
	String Motor;

	Motor = server.arg("MOTOR"); //Obtenemos el valor de la oagina web 


		if ( Motor == "1"){ //La puerta se abre
		
  		digitalWrite(Mot1, LOW);
 		digitalWrite(Mot2, HIGH); 
  		delay(2000);
  		digitalWrite(Mot1, LOW);
 		digitalWrite(Mot2, LOW); 

	}else if(Motor  == "0"){ //La puerta se cierra

  		digitalWrite(Mot1, HIGH);
  		digitalWrite(Mot2, LOW); 
  		delay(2000);
  		digitalWrite(Mot1, LOW);
 		digitalWrite(Mot2, LOW);

  	}


}	



