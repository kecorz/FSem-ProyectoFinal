// Light behavior:
void lightBehavior()
{
  if (lightsOn)
  {
    digitalWrite(LED1pin, HIGH);
    ledcWrite(ledChannel, lightIntensity.toInt());
  }
  else
  {
    digitalWrite(LED1pin, LOW);
    ledcWrite(ledChannel, 0);
  }
}

// Led program behavior:
void ledProgram()
{
  getServerTime(serverTime);
  if (setLightOn && selectedLightOnTime[0] == serverTime[0] && selectedLightOnTime[1] == serverTime[1] && selectedLightOnTime[2] == serverTime[2])
  {
    Serial.println("Led ON NOW!!!!!!!!!!!");
    digitalWrite(LED1pin, HIGH);
    ledcWrite(ledChannel, lightIntensity.toInt());
    setLightOn = false;
    lightsOn = true;
  }
  if (setLightOff && selectedLightOffTime[0] == serverTime[0] && selectedLightOffTime[1] == serverTime[1] && selectedLightOffTime[2] == serverTime[2])
  {
    Serial.println("Led OFF NOW!!!!!!!!!!!");
    digitalWrite(LED1pin, LOW);
    ledcWrite(ledChannel, 0);
    setLightOff = false;
    lightsOn = false;
  }
}

// Doorbell behavior:
void doorbellBehavior()
{
  int state_push = digitalRead(doorbellpin);
  if(state_push == HIGH)
  {
    Serial.println("Someone is at the door");
    doorbell = true;
  }
  else{
    doorbell = false;
  }
}

// Update Temperature behavior
void updateTemperature()
{
  temperature =  ((analogRead(SENSORPIN) * 500 )/4096.0);
  //Serial.println(analogRead(SENSORPIN));
}
