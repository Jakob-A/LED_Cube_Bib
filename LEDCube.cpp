//
// Created by Jakob on 16.04.20.
//

#include <avr/io.h>
#include "LEDCube.h"
#include "DrawFunctions.h"
#include "Arduino.h"
#include "TimerOne.h"
#include <string.h>
#include <Time.h>
#include <Wire.h>
#include <DS1307RTC.h>




Cube::Cube(int latchpin, int clockpin, int datapin){

    latchPin = latchpin;
    clockPin = clockpin;
    dataPin = datapin;
    latchPinPORTB = latchPin - 8;

    current_layer = 0;

}

void Cube::begin(Cube cube){
    
    Serial.begin(9600);

    //layer pins
    for (int i = 2; i < 10; i++)
    {
        pinMode(i, OUTPUT);
    }

    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);

    digitalWrite(latchPin, LOW);
    digitalWrite(dataPin, LOW);
    digitalWrite(clockPin, LOW);

    //--- Setup to run SPI
    setupSPI();

    //--- Activate the PWM timer
    Timer1.initialize(100); // Timer for updating pwm pins
    Timer1.attachInterrupt(iProcess);
    setSyncProvider(RTC.get);
}

//--- Direct port access latching
void Cube::latchOn() {
    bitSet(PORTB, latchPinPORTB);
}
void Cube::latchOff() {
    bitClear(PORTB, latchPinPORTB);
}

//--- This process is run by the timer and does the PWM control
//sets the RCK Pin On so if it was off before the Data is stored into the IC's
void Cube::iProcess() {
    //last layer store
    int oldLayerBit = current_layer + 2;

    //increment layer count
    current_layer++;
    if (current_layer >= 8) {
        current_layer = 0;
    }

    //--- Run through all the shift register values and send them (last one first)
    // latching in the process
    latchOff();
    for (int i = 0 ; i < 8 ; i++) {
        spi_transfer(Draw::cube[current_layer][i]);
    }

    //Hide the old layer
    digitalWrite(oldLayerBit, LOW);
    //New data on the pins
    latchOn();
    //new layer high
    digitalWrite(current_layer + 2, HIGH);
}

//--- The really fast SPI version of shiftOut
unsigned char Cube::spi_transfer(unsigned char data)
{
    SPDR = data;        // Start the transmission
    loop_until_bit_is_set(SPSR, SPIF);
    return SPDR;        // return the received byte, we don't need that
}

//--- Used to setup SPI based on current pin setup
//    this is called in the setup routine;
void Cube::setupSPI() {
    byte clr;
    SPCR |= ( (1 << SPE) | (1 << MSTR) ); // enable SPI as master
    SPCR &= ~( (1 << SPR1) | (1 << SPR0) ); // clear prescaler bits
    clr = SPSR; // clear SPI status reg
    clr = SPDR; // clear SPI data reg
    SPSR |= (1 << SPI2X); // set prescaler bits
    delay(10);
}
