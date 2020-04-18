//
// Created by Jakob on 16.04.20.
//

#ifndef LED_RASPI_LEDCUBE_H
#define LED_RASPI_LEDCUBE_H

namespace CubeSetup {



    void startCube(int latchpin, int clkPin, int dtPin);

    void latchOn();

    void latchOff();

    void iProcess();

    unsigned char spi_transfer(unsigned char data);

    void setupSPI();

}


#endif //LED_RASPI_LEDCUBE_H
