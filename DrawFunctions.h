/*
    Library with draw functions for the LED Cube
*/

#ifndef Draw_h
#define Draw_h

#include <string.h>
#include <Time.h>
#include <Wire.h>


#define AXIS_X 1
#define AXIS_Y 2
#define AXIS_Z 3



/**
* Turn on LED at the coordinates x,y,z
*/
    void setvoxel(int x, int y, int z);

/**
* Turn of LED at the coordinates x,y,z
*/
    void clrvoxel(int x, int y, int z);

/**
* This function validates that we are drawing inside the cube.
*/
    unsigned char inrange(int x, int y, int z);

/**
* Get the current status of the LED
*/
    unsigned char getvoxel(int x, int y, int z);

/**
* changes the state of the LED to the state into the state written in 'state'
*/
    void altervoxel(int x, int y, int z, int state);

/**
* Fill a value into all 64 byts of the cube buffer
* Mostly used for clearing. fill(0x00)
* or setting all on. fill(0xff)
*/
    void fill(unsigned char pattern);

/**
* Flip the state of a LED.
*/
    void flpvoxel(int x, int y, int z);

/**
* Makes sure x1 is alwas smaller than x2
* This is usefull for functions that uses for loops,
* to avoid infinite loops
*/
    void argorder(int ix1, int ix2, int *ox1, int *ox2);

/**
* Sets all LEDs along a X/Y plane at a given point
* on axis Z
*/
    void setplane_z(int z);

/**
* Clears LED - plane at given z - coordinate
*/
    void clrplane_z(int z);

/**
* Sets all LEDs along a Z/Y plane at a given point
* on axis X
*/
    void setplane_x(int x);

/**
* Clears LED - plane at given x - coordinate
*/
    void clrplane_x(int x);

/**
* Sets all LEDs along a Z/X plane at a given point
* on axis X
*/
    void setplane_y(int y);

/**
* Clears LED - plane at given y - coordinate
*/
    void clrplane_y(int y);

/**
* Sets all LEDs along a plane at a given point
* on axis 'axis'
*/
    void setplane(char axis, unsigned char i);

/**
* Clears all LEDs along a plane at a given point
* on axis 'axis'
*/
    void clrplane(char axis, unsigned char i);

/**
 *  Draw a box with all walls drawn and all LEDs inside set
*/
    void box_filled(int x1, int y1, int z1, int x2, int y2, int z2);

/**
 *  Darw a hollow box with side walls.
*/
    void box_walls(int x1, int y1, int z1, int x2, int y2, int z2);

/**
 * Draw a wireframe box. This only draws the corners and edges, no walls.
*/
    void box_wireframe(int x1, int y1, int z1, int x2, int y2, int z2);

/**
 * Returns a byte with a row of 1's drawn in it.
 * byteline(2,5) gives 0b00111100
*/
    char byteline(int start, int end);

/**
 * MSB becomes LSB, LSB becomes MSB.
*/
    char flipbyte(char byte);

/**
 * Draw a line between any coordinates in 3d space.
 * Uses integer values for input, so dont expect smooth animations.
*/
    void line(int x1, int y1, int z1, int x2, int y2, int z2);

/**
 *  Shift the entire contents of the cube along an axis
 * This is great for effects where you want to draw something
 * on one side of the cube and have it flow towards the other
 * side. Like rain flowing down the Z axiz.
*/
    void shift(char axis, int direction);

/**
 * delay milliseconds
 * @param x
 */
    void delay_ms(uint16_t x);


#endif
