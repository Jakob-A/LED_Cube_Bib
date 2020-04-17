/*
    Library with CubeEffects for the LED Cube
*/

#include "DrawFunctions.h"
#include "CubeText.h"
#include "CubeEffects.h"
#include "/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino/USBAPI.h"
#include "/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino/HardwareSerial.h"
#include "Arduino.h"

CubeEffects::CubeEffects(int latchpin, int clockpin, int datapin){

    Cube cube(latchpin, clockpin, datapin);

    cube.begin();


}

void CubeEffects::Jede1mal(int t){
  Serial.print("Wartung gestartet");
  int xc=0;
  int yc=0;
  int zc=0;
  for (int i = 0;i<512;i++){
    if(Serial.available()>0){
    break;
    }
    xc++;
    if(xc == 8){
      xc = 0;
      yc++;
      if(yc == 8){
        yc = 0;
        zc++;
        if(zc == 8){
        zc = 0;  
        }
      }
    }    
    Draw::setvoxel(xc,yc,zc);
    delay(t);
    Draw::clrvoxel(xc,yc,zc);
    delay(t);
  }
}

void CubeEffects::box_wamp(int delayt)
{
  for (int k = 0; k < 3; k++) {
    for (int i = 0; i < 4; i++) {
      Draw::fill(0x00);
      Draw::box_filled(3 - i, 3 - i, 3 - i, 4 + i, 4 + i, 4 + i);
      Draw::delay_ms(delayt);
    }
    for (int i = 3; i >= 0; i--) {
      Draw::fill(0x00);
      Draw::box_filled(3 - i, 3 - i, 3 - i, 4 + i, 4 + i, 4 + i);
      Draw::delay_ms(delayt);
    }
  }

  for (int k = 0; k < 3; k++) {
    for (int i = 0; i < 4; i++) {
      Draw::fill(0x00);
      Draw::box_walls(3 - i, 3 - i, 3 - i, 4 + i, 4 + i, 4 + i);
      Draw::delay_ms(delayt);
    }
    for (int i = 3; i >= 0; i--) {
      Draw::fill(0x00);
      Draw::box_walls(3 - i, 3 - i, 3 - i, 4 + i, 4 + i, 4 + i);
      Draw::delay_ms(delayt);
    }
  }

  for (int k = 0; k < 3; k++) {
    for (int i = 0; i < 4; i++) {
      Draw::fill(0x00);
      Draw::box_wireframe(3 - i, 3 - i, 3 - i, 4 + i, 4 + i, 4 + i);
      Draw::delay_ms(delayt);
    }
    for (int i = 3; i >= 0; i--) {
      Draw::fill(0x00);
      Draw::box_wireframe(3 - i, 3 - i, 3 - i, 4 + i, 4 + i, 4 + i);
      Draw::delay_ms(delayt);
    }
  }
}

void CubeEffects::draw_positions_axis (char axis, unsigned char positions[64], int invert)
{
  int x, y, p;

  Draw::fill(0x00);

  for (x = 0; x < 8; x++)
  {
    for (y = 0; y < 8; y++)
    {
      if (invert)
      {
        p = (7 - positions[(x * 8) + y]);
      } else
      {
        p = positions[(x * 8) + y];
      }

      if (axis == AXIS_Z)
        Draw::setvoxel(x, y, p);

      if (axis == AXIS_Y)
        Draw::setvoxel(x, p, y);

      if (axis == AXIS_X)
        Draw::setvoxel(p, y, x);
    }
  }

}


void CubeEffects::boxside_randsend_parallel (char axis, int origin, int delayt, int mode)
{
  int i;
  int done;
  unsigned char cubepos[64];
  unsigned char pos[64];
  int notdone = 1;
  int notdone2 = 1;
  int sent = 0;

  for (i = 0; i < 64; i++)
  {
    pos[i] = 0;
  }

  while (notdone)
  {
    if (mode == 1)
    {
      notdone2 = 1;
      while (notdone2 && sent < 64)
      {
        i = rand() % 64;
        if (pos[i] == 0)
        {
          sent++;
          pos[i] += 1;
          notdone2 = 0;
        }
      }
    } else if (mode == 2)
    {
      if (sent < 64)
      {
        pos[sent] += 1;
        sent++;
      }
    }

    done = 0;
    for (i = 0; i < 64; i++)
    {
      if (pos[i] > 0 && pos[i] < 7)
      {
        pos[i] += 1;
      }

      if (pos[i] == 7)
        done++;
    }

    if (done == 64)
      notdone = 0;

    for (i = 0; i < 64; i++)
    {
      if (origin == 0)
      {
        cubepos[i] = pos[i];
      } else
      {
        cubepos[i] = (7 - pos[i]);
      }
    }


    Draw::delay_ms(delayt);

    draw_positions_axis(axis, cubepos, 0);

  }

}


void CubeEffects::rain (int iterations)
{
  int i, ii;
  int rnd_x;
  int rnd_y;
  int rnd_num;

   
  for (ii = 0; ii < iterations; ii++)
  {
    rnd_num = rand() % 4;
    
    if(Serial.available()>0){ 
    break;
    }
    for (i = 0; i < rnd_num; i++)
    {
      if(Serial.available()>0){ 
        break;
      }
      rnd_x = rand() % 8;
      rnd_y = rand() % 8;
      Draw::setvoxel(rnd_x, rnd_y, 7);
      
    }

    Draw::delay_ms(800);
    Draw::shift(AXIS_Z, -1);
  }
}

// Set or clear exactly 512 voxels in a random order.
void CubeEffects::random_filler (int delayt, int state)
{
  int x, y, z;
  int loop = 0;

    
  if (state == 1)
  {
    Draw::fill(0x00);
  } else
  {
    Draw::fill(0xff);
  }

  while (loop < 511)
  {
    x = rand() % 8;
    y = rand() % 8;
    z = rand() % 8;

    if ((state == 0 && Draw::getvoxel(x, y, z) == 0x01) || (state == 1 && Draw::getvoxel(x, y, z) == 0x00))
    {
      Draw::altervoxel(x, y, z, state);
      Draw::delay_ms(delayt);
      loop++;
    }
  }
}

void CubeEffects::blinky2()
{
  int i, r;
  Draw::fill(0x00);

  for (r = 0; r < 2; r++)
  {
    i = 750;
    while (i > 0)
    {
      Draw::fill(0x00);
      Draw::delay_ms(i);

      Draw::fill(0xff);
      Draw::delay_ms(100);

      i = i - (15 + (1000 / (i / 10)));
    }

    Draw::delay_ms(1000);

    i = 750;
    while (i > 0)
    {
      Draw::fill(0x00);
      Draw::delay_ms(751 - i);

      Draw::fill(0xff);
      Draw::delay_ms(100);

      i = i - (15 + (1000 / (i / 10)));
    }
  }

}

// Draw a plane on one axis and send it back and forth once.
void CubeEffects::planboing (int plane, int speedd)
{
  int i;
  for (i = 0; i < 8; i++)
  {
    Draw::fill(0x00);
    Draw::setplane(plane, i);
    Draw::delay_ms(speedd);
  }

  for (i = 7; i >= 0; i--)
  {
    Draw::fill(0x00);
    Draw::setplane(plane, i);
    Draw::delay_ms(speedd);
  }
}