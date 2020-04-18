//
// Created by Jakob on 16.04.20.
//

#ifndef LED_RASPI_LEDCUBE_H
#define LED_RASPI_LEDCUBE_H

//holds value for all the pins, [x][y][z]
unsigned char cube[8][8];

//--- Used for faster latching -- latchpin - 8 because PortB controls I/O -Ports from 8 to 13
int lchPinPORTB;

int current_layer = 0;

void startCube(int latchpin, int clkPin, int dtPin);

void latchOn();

void latchOff();

void iProcess();

unsigned char spi_transfer(unsigned char data);

void setupSPI();




#endif //LED_RASPI_LEDCUBE_H
