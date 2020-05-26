// Light behavior:
void lightBehavior()
{
  if (lightsOn)
  {
    digitalWrite(LED1pin, HIGH);
  }
  else
  {
    digitalWrite(LED1pin, LOW);
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
    setLightOn = false;
    lightsOn = true;
  }
  if (setLightOff && selectedLightOffTime[0] == serverTime[0] && selectedLightOffTime[1] == serverTime[1] && selectedLightOffTime[2] == serverTime[2])
  {
    Serial.println("Led OFF NOW!!!!!!!!!!!");
    digitalWrite(LED1pin, LOW);
    setLightOff = false;
    lightsOn = false;
  }
}

// Aquí debe ir el comportamiento para el tiembre:
void doorbellBehavior()
{
}
