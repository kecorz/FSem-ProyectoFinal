String getHTML();
String getCamerasHTML();

// Initial connection route:
void handleOnConnect()
{
  server.send(200, "text/html", getHTML());
}

// Route: Turn lights on button
void handleLightsOn()
{
  lightsOn = true;
  Serial.println("Turning lights on with this intesity: " + lightIntensity);
  server.send(200, "text/html", getHTML());
}

// Route: Turn lights off button
void handleLightsOff()
{
  lightsOn = false;
  Serial.println("Turning lights off");
  server.send(200, "text/html", getHTML());
}

// Route: Open garage door button
void handleGarageOpen()
{
  garageDoorOpen = true;
  Serial.println("Opening garage door");
  server.send(200, "text/html", getHTML());

  // Open garage instructions:
  digitalWrite(EN1pin,HIGH);
  digitalWrite(Mot1,HIGH);
  digitalWrite(Mot2, LOW);
  delay(2000);
  digitalWrite(Mot1,LOW);
  digitalWrite(Mot2, LOW);
}

// Route: Close garage door button
void handleGarageClose()
{
  garageDoorOpen = false;
  Serial.println("Closing garage door");
  server.send(200, "text/html", getHTML());

  //Close garage instructions
  digitalWrite(EN1pin,HIGH);
   digitalWrite(Mot1,LOW);
  digitalWrite(Mot2, HIGH);
  delay(2000);
  digitalWrite(Mot1,LOW);
  digitalWrite(Mot2, LOW);
}

// Route: Cameras tab
void handleCameras()
{
  Serial.println("Camera webpage ready!");
  server.send(200, "text/html", getCamerasHTML());
}

// Data input route (/get):
void handleGet()
{
  // Handle lights on time
  if (server.arg("timeLightOnInput") != "")
  {
    String time = server.arg("timeLightOnInput");
    Serial.println(time);
    getSelectedTime(selectedLightOnTime, time);
    setLightOn = true;
    Serial.println("Selected on: " + String(selectedLightOnTime[0]) + ":" + String(selectedLightOnTime[1]) + " " + String(selectedLightOnTime[2]));
    //Serial.println("Server: " + String(serverTime[0]) + ":" + String(serverTime[1]) + " " + String(serverTime[2]));
  }
  // Handle lights off time
  else if (server.arg("timeLightOffInput") != "")
  {
    String time = server.arg("timeLightOffInput");
    Serial.println(time);
    getSelectedTime(selectedLightOffTime, time);
    setLightOff = true;
    Serial.println("Selected off: " + String(selectedLightOffTime[0]) + ":" + String(selectedLightOffTime[1]) + " " + String(selectedLightOffTime[2]));
    //Serial.println("Server: " + String(serverTime[0]) + ":" + String(serverTime[1]) + " " + String(serverTime[2]));
  }
  // Handling intensity input data
  else if (server.arg("lightIntensity") != "")
  {
    lightIntensity = server.arg("lightIntensity");
    Serial.println("Intensity: " + lightIntensity);
  }
  server.send(200, "text/html", getHTML());
}

// Route not found:
void handleNotFound()
{
  server.send(404, "text/plain", "Not found");
}
