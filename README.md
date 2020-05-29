# FSem-ProyectoFinal

 Software configuration required to set up a Smart Home Hub with an ESP32 microcontroller.
 
 Developed by:
 - Ricardo Hernández Gómez
 - Elda Corella Perez
  
 Sistemas Embebidos
 Universidad Nacional Autónoma de México
  
 Pin configuration:
 - Temperature sensor (LM35): 34
 - LED pin: 4
 - DC Motor: 
    Enable: 10
    Mot1: 11
    Mot2: 12 


## Using the implementation
Open the project using **Arduino IDE**. An ESP32 microcontroller and a micro USB cable to connect it to the computer are also required.

Don't forget to write you home network's credentials in the global variables presented at the beginning of the **Solution.ino** file.

    const char *ssid = "";  // Enter SSID here
    const char *password = ""; //Enter Password here
    
Use the **Serial Monitor** to check the microcontroller's IP, and access via any web browser on any device.

![Desktop Control](https://github.com/kecorz/FSem-ProyectoFinal/blob/master/Screenshots/desktop.png)

![Mobile Control](https://github.com/kecorz/FSem-ProyectoFinal/blob/master/Screenshots/desktop2.png)

![Desktop Cameras](https://github.com/kecorz/FSem-ProyectoFinal/blob/master/Screenshots/mobile.png)

![Mobile Cameras](https://github.com/kecorz/FSem-ProyectoFinal/blob/master/Screenshots/mobile2.png)
