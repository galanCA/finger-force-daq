// Libraries
#include "HX711.h"
#include <WiFi.h>
#include "esp_timer.h"

/** Macro **/
#define _DEBUG
#define _TIMETEST
// Base
// 1000 iterations took 96752 milliseconds (96752 microseconds per invocation)
// 5000 iterations took 483734 milliseconds (96746 microseconds per invocation)


/** WiFi constants **/
// Router definitions
const char * networkName = "";
const char * networkPswd = "";

// Host
const char * host = "";
const int port = 3333;

/** Sensor definitions **/ 
#define calibration_factor -9830

// ESP32 -> HX711
// VUSB -> VDD (V3.3 -> VDD for 10Hz)
// V3.3 -> VCC
// GND -> GND
#define DOUT 17 //-> DAT
#define CLK 16 //-> CLK

// Variable definition
WiFiClient client;
HX711 scale;
long data;
float currentTime;
char msg[24];

void connectToWiFi(const char * ssid, const char * pwd) {
  int ledState = 0;

  printLine();
  Serial.println("Connecting to WiFi network: " + String(ssid));
  WiFi.begin(ssid, pwd);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    //digitalWrite(LED_PIN, ledState);
    //ledState = (ledState + 1) % 2;
    delay(500);
  }
  
  Serial.println();
  Serial.println("connected to WiFi");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void connectToServer(const char * IP, const int Port) {
  if (client.connect(IP, Port)) {
    Serial.println("Server connected");
    client.flush();
  }
}

void setup() {
  Serial.begin(2000000);
  // Connect to router
  connectToWiFi(networkName, networkPswd);

  // Connect to server
  connectToServer(host, port);

  //setup load sensor
  scale.begin(DOUT, CLK);
  scale.set_scale(calibration_factor);
  scale.tare();
  long zero_factor = scale.read_average(); //Get a baseline reading

}

void printLine() {
  Serial.println();
  for (int i = 0; i<30; i++)
    Serial.print("-");
  Serial.println();
}

void createMessage(){
  sprintf(msg,"%.3f\t%.2f\n", millis()/1000., scale.read());
  //Serial.println(scale.read());
}


void loop() {
#ifndef _TIMETEST
  createMessage();
#ifdef _DEBUG
  Serial.print(msg);
#endif
  //client.write(msg);
#else
  const unsigned MEASUREMENTS = 100;
  uint64_t tstart = esp_timer_get_time();

  for (int retries = 0; retries < MEASUREMENTS; retries++) {
      createMessage(); // This is the thing you need to measure
  }

  uint64_t tend = esp_timer_get_time();

  printf("%u iterations took %llu milliseconds (%llu microseconds per invocation) frequency is %.3f Hz\n",
         MEASUREMENTS, (tend - tstart)/1000, (tend - tstart)/MEASUREMENTS, MEASUREMENTS/float(tend - tstart)*1000. );
#endif
}
