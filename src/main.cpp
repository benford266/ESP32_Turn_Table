// Author: BFGarage
// Date: 2021-09-26
// Description: This code is for an ESP32 to control a stepper motor using a web server. 
//The ESP32 will create an access point with the SSID "ESP32-Turn-Table" and password "SpinAround". 
//The ESP32 will host a web server that will allow the user to start and stop the stepper motor. 
//The stepper motor will spin 200 steps in the clockwise direction when the user presses the start button. 
//The stepper motor will stop spinning when the user presses the stop button. 
//The ESP32 will print the state of the stepper motor to the serial monitor. 
//The ESP32 will also print the IP address of the access point to the serial monitor. 
//The ESP32 will use the WiFi library to create the access point and the WiFiServer library to host the web server. 
//The ESP32 will use the FS library to store the HTML code for the web page.
//The ESP32 will use the Arduino library to control the stepper motor.

// Include the required libraries
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiAP.h>
#include <WebServer.h>
#include <MobaTools.h>


// Stepper Configuration
const byte dirPin       = 32; // connect to DIR of the stepper motor driver
const byte stepPin      = 33; // connect to STEP of the stepper motor driver
const byte enaPin       = 25; // connect to Enable of the stepper motor driver

enum class Controller {STOP, LEFT, RIGHT, CONTL, CONTR};  // Controller actions
const int STEPS_REVOLUTION = 3200;                         // 
MoToStepper myStepper( STEPS_REVOLUTION, STEPDIR );       // Stepper direction 


//Wifi Configuration
const char* ssid     = "ESP32-Turn-Table";
const char* password = "SpinAround";
WebServer server(80);

#include "website.h"

void esp32Stepper(const Controller action) {
  switch (action) {
    case Controller::LEFT:
      myStepper.doSteps(-STEPS_REVOLUTION); // Stepper turns one revolution left
      break;
    case Controller::RIGHT:
      myStepper.doSteps(STEPS_REVOLUTION); // Stepper turns one revolution right
      break;
    case Controller::CONTL:
      myStepper.rotate( -1 ); // Stepper turns left
      break;
    case Controller::CONTR:
      myStepper.rotate( 1 ); // Stepper turns right
      break;
    case Controller::STOP:
      myStepper.rotate( 0 ); // Stop stepper
      break;
  }
}

void handleStepper() {       
  char htmlTemp[sizeof(HTMLTEXT)+15];
  long htSpeed = 150000;
  long htRamp = 100;
  if (server.hasArg("left")) esp32Stepper(Controller::LEFT);  
  if (server.hasArg("right")) esp32Stepper(Controller::RIGHT); 
  if (server.hasArg("contl")) esp32Stepper(Controller::CONTL); 
  if (server.hasArg("contr")) esp32Stepper(Controller::CONTR);   
  if (server.hasArg("stop"))  esp32Stepper(Controller::STOP);    
  if (server.hasArg("speed")) htSpeed = 10*server.arg("speed").toInt(); 
  if (server.hasArg("ramp"))  htRamp = server.arg("ramp").toInt();

  if (server.hasArg("setSpeed")) {
    // seting speed and ramp
    htRamp = myStepper.setSpeedSteps(htSpeed);
  }
  if (server.hasArg("setRamp")) {
    // seting ramp length
    htRamp = myStepper.setRampLen(htRamp);
  }

  int htmlSize = snprintf( htmlTemp, sizeof(htmlTemp), HTMLTEXT, htSpeed/10, htRamp );
  server.send(200, "text/html", htmlTemp);
}

void setup() {
  // Set up Serial
  Serial.begin(115200);

  // Set up Stepper
  myStepper.attach( stepPin, dirPin );               // Step- und Dir-Pin 
  myStepper.attachEnable( enaPin, 10, LOW );         // Enable Pin 
  myStepper.setSpeed( 2000 );                        // 200 U/min
  myStepper.setRampLen( 300 );                       // Ramp Lenght 300 Steps

  // Set up Wifi
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.mode(WIFI_AP);                                // Set ESP32 in Access Point Mode
  WiFi.softAP(ssid,password);

  server.on ("/stepper", handleStepper);           // Im Browser "http://192.168.4.1/stepper" 
  server.begin();                                    // Start the web server

}

void loop() {
  server.handleClient(); 
}




