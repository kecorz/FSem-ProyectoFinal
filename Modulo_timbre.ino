// Modulo de timbre
//Conectar un pin a negativo con una resistencia (esp32)
//El otro pin ira a vcc


int timbre = ;
int timbre_LED = ;

void setup(){
	
	pinMode(timbre, INPUT);
	pinMode(timbre_LED, OUTPUT);
}

void loop(){

int state_push = digitalRead(timbre);

//Preguntamos por el estado del push
if(state_push == HIGH){
	
	digitalWrite(timbre_LED,HIGH);
	//PRENDER LED O CUALQUIER OTRA ACCION

}
else{
	digitalWrite(timbre_LED, LOW):

	//APAGAR LED O CUALQUIER OTRA ACCION
}


_
}

