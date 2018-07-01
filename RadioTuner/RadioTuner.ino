//
// RadioTuner
//
// Arduino based FM/AM tuner
// Developed with [embedXcode](http://embedXcode.weebly.com)
//
// Author 		Doug Mason
// 				Doug Mason
//
// Date			6/30/18 1:51 PM
// Version		1.0
//
// Copyright	© Doug Mason, 2018
// Licence		1.0
//
// See         ReadMe.txt for references
//


// Core library for code-sense - IDE-based
// !!! Help: http://bit.ly/2AdU7cu
#if defined(ENERGIA) // LaunchPad specific
#include "Energia.h"
#elif defined(TEENSYDUINO) // Teensy specific
#include "Arduino.h"
#elif defined(ESP8266) // ESP8266 specific
#include "Arduino.h"
#elif defined(ARDUINO) // Arduino 1.8 specific
#include "Arduino.h"
#else // error
#error Platform not defined
#endif // end IDE

#include <EEPROM.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include <TEA5767Radio.h>

const int fmRange = 20;
const int interruptPin = 2;

// initializing the LCD display
const int rs = 11, en = 12, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// initializing the tuner module library
TEA5767Radio radio = TEA5767Radio();
float station = 0.0;

int pot = A0;
bool reset = false;

void setFrequency()
{
    Serial.print("selected station: ");
    Serial.print(station);
    Serial.println("");
    
    reset = true;
}

void setup()
{
    Wire.begin();
    Serial.begin(9600);
    lcd.begin(16, 2);
    
    pinMode(pot, INPUT);
    pinMode(interruptPin, INPUT);
    attachInterrupt(digitalPinToInterrupt(interruptPin), setFrequency, CHANGE);
}

void loop()
{
    int input = analogRead(pot);
    float percent = input / 1024.0;
    float delta = fmRange * percent;
    station = 88.0 + delta;
    station = round(station * 10.0) / 10.0;
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("station: ");
    lcd.print(station);
    
    if (reset) {
        reset = false;
        radio.setFrequency(station);
    }
    
    delay(200);
}




































