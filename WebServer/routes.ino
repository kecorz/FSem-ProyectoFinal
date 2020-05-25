// Initial connection route:
void handleOnConnect()
{
  server.send(200, "text/html", getHTML());
}

void handleLightsOn()
{
  lightsOn = true;
  server.send(200, "text/html", getHTML());
}

void handleLightsOff()
{
  lightsOn = false;
  server.send(200, "text/html", getHTML());
}

// Aquí va el comportamiento para abrir la puerta
void handleGarageOpen()
{
  garageDoorOpen = true;
  Serial.println("Opening garage door");
  server.send(200, "text/html", getHTML());
}

// Aquí va el comportamiento para cerrar la puerta
void handleGarageClose()
{
  garageDoorOpen = false;
  Serial.println("Closing garage door");
  server.send(200, "text/html", getHTML());
}

// Data input route (/get):
void handleGet()
{
  if (server.arg("timeLightOnInput") != "")
  {
    String time = server.arg("timeLightOnInput");
    Serial.println(time);
    getSelectedTime(selectedLightOnTime, time);
    setLightOn = true;
    Serial.println("Selected on: " + String(selectedLightOnTime[0]) + ":" + String(selectedLightOnTime[1]) + " " + String(selectedLightOnTime[2]));
    //Serial.println("Server: " + String(serverTime[0]) + ":" + String(serverTime[1]) + " " + String(serverTime[2]));
  }
  if (server.arg("timeLightOffInput") != "")
  {
    String time = server.arg("timeLightOffInput");
    Serial.println(time);
    getSelectedTime(selectedLightOffTime, time);
    setLightOff = true;
    Serial.println("Selected off: " + String(selectedLightOffTime[0]) + ":" + String(selectedLightOffTime[1]) + " " + String(selectedLightOffTime[2]));
    //Serial.println("Server: " + String(serverTime[0]) + ":" + String(serverTime[1]) + " " + String(serverTime[2]));
  }
  // Aquí va el control de la intensidad:
  if (server.arg("lightIntensity") != "")
  {
    String intensity = server.arg("lightIntensity");
    Serial.println("Intensity: " + intensity);
  }
  Serial.println("Gets here");
  server.send(200, "text/html", getHTML());
}

// Route not found:
void handleNotFound()
{
  server.send(404, "text/plain", "Not found");
}
