//
// Created by Jakob on 16.04.20.
//

#ifndef LED_RASPI_LEDCUBE_H



#define LED_RASPI_LEDCUBE_H


class Cube{

private:



    //--- Pin connected to ST_CP of 74HC595
    static int latchPin;
    //--- Pin connected to SH_CP of 74HC595
    static int clockPin;
    //--- Pin connected to DS of 74HC595
    static int dataPin;

    //--- Used for faster latching -- latchpin - 8 because PortB controls I/O -Ports from 8 to 13
    static int latchPinPORTB;

    static int current_layer;

    static void latchOn();

    static void latchOff();

    static void iProcess();

    static unsigned char spi_transfer(unsigned char data);

    void setupSPI();

public:
    Cube(int latchpin, int clockpin, int datapin);

    void begin(Cube cube);

};

#endif //LED_RASPI_LEDCUBE_H
