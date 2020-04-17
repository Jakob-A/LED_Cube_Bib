/*
    Library with CubeEffects for the LED Cube
*/

#ifndef Effects_h
#define Effects_h

#include "LEDCube.h"
#include "DrawFunctions.h"

class CubeEffects
{
private:
    /* data */
public:

    CubeEffects(int latchpin, int clockpin, int datapin);

    /**
     * turns on every LED once at a time
     */
    void Jede1mal(int t);

    /**
     * Creates boxes that grow and shrink
     */
    void box_wamp(int delayt);

    void draw_positions_axis (char axis, unsigned char positions[64], int invert);

    void boxside_randsend_parallel (char axis, int origin, int delayt, int mode);

    void rain (int iterations);

    void random_filler (int delayt, int state);

    void blinky2();

    void planboing (int plane, int speedd);
    
};



#endif