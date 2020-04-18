#include <Arduino.h>
#include <TimerOne.h>
#include <string.h>
#include <Time.h>
#include <Wire.h>
#include <DS1307RTC.h>
#include "DrawFunctions.h"
#include "CubeText.h"
#include "CubeEffects.h"
#include "LEDCube.h"


//--- Pin connected to ST_CP of 74HC595
#define LATCHPIN 10
//--- Pin connected to SH_CP of 74HC595
#define CLOCKPIN 13
//--- Pin connected to DS of 74HC595
#define DATAPIN 11


CubeEffects LEDCube();

void setup(){
  LEDCube().begin(LATCHPIN, CLOCKPIN, DATAPIN);
  
  }

void loop(){

    while (!Serial.available()){

        LEDCube().rain(100);

    }

}
