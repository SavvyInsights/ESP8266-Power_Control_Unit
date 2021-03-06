#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>

// --- DEBUGGING ---
#define DEBUG // Comment out to remove all serial prints

#ifdef DEBUG
  #define out(x) Serial.print(x)
  #define outln(x) Serial.println(x)
  #define tout(x) Telnet.print(x)
  #define toutln(x) Telnet.println(x)
#else
  #define out(x)
  #define outln(x)
  #define tout(x)
  #define toutln(x)
#endif

// --- End Debugging ---
#define LCD_SCREEN// Comment out if no display

#ifdef LCD_SCREEN 
  #define sout(x) Screen.print(x)
  #define soutln(x) Screen.println(x)
#else 
  #define sout(x)
  #define soutln(x)
#endif

// *********** PIN ASSIGNMENTS ***********************

const int dht_pin = 25;
// Assign output variables to GPIO pins

const int AC1 = 16;
const int AC2 = 17; //17

// DC  12 Volt
const int DC1 = 26;//26
const int DC2 = 27;

const int button_pin = 18;

//Toggle switches starting values
String plugStatus1 = "off";
String plugStatus2 = "off";

//sliders starting value
String message = "";
String sliderValue1 = "0";
String sliderValue2 = "0";

int dutyCycle1;
int dutyCycle2;

// setting PWM properties
const int freq = 5000;
const int ledChannel1 = 0;
const int ledChannel2 = 1;

const int resolution = 8;

// ************* GLOBAL VARIABLES ***********************
int dht_timer_start = millis();
int dht_timer_period = 5; //time in seconds between readings
float dht_tempC = 0;
float dht_tempF = 0;
float dht_humidity = 0;

//bool led_on = true;
//String JSONtxt;

// ******* INCLUDE FILES *********************
#include "display.h"
#include "wifi_manager.h"
#include "web_socket.h"
#include "sensor_temp.h"

void pinSetup(){
  // Initialize AC plugs and set to HIGH - (off)
  pinMode(AC1, OUTPUT);
  pinMode(AC2, OUTPUT);
  // Set Plug outputs to HIGH
  digitalWrite(AC1, HIGH);
  digitalWrite(AC2, HIGH);

  // Initilize DC plugs and set to Low (off)
  pinMode(DC1, OUTPUT);
  pinMode(DC2, OUTPUT);
  // Set DC outpins to LOW
  digitalWrite(DC1, LOW);
  digitalWrite(DC2, LOW);

// configure LED PWM functionalitites
  ledcSetup(ledChannel1, freq, resolution);
  ledcSetup(ledChannel2, freq, resolution);

  // attach the channel to the GPIO to be controlled
  ledcAttachPin(DC1, ledChannel1);
  ledcAttachPin(DC2, ledChannel2);
}
#endif