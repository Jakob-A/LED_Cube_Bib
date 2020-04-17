// ==========================================================================================
//   Draw functions
// ==========================================================================================
#include "DrawFunctions.h"


/**
* Turn on LED at the coordinates x,y,z 
*/
void Draw::setvoxel(int x, int y, int z)
{
  if (inrange(x, y, z))
    cube[z][y] |= (1 << x);
}

/**
* Turn of LED at the coordinates x,y,z
*/
void Draw::clrvoxel(int x, int y, int z)
{
  if (inrange(x, y, z))
    cube[z][y] &= ~(1 << x);
}


/**
* This function validates that we are drawing inside the cube.
*/
unsigned char Draw::inrange(int x, int y, int z)
{
  if (x >= 0 && x < 8 && y >= 0 && y < 8 && z >= 0 && z < 8)
  {
    return 0x01;
  } else
  {
    // One of the coordinates was outside the cube.
    return 0x00;
  }
}

/**
* Get the current status of the LED
*/
unsigned char Draw::getvoxel(int x, int y, int z)
{
  if (inrange(x, y, z))
  {
    if (cube[z][y] & (1 << x))
    {
      return 0x01;
    } else
    {
      return 0x00;
    }
  } else
  {
    return 0x00;
  }
}

/**
* changes the state of the LED to the state into the state written in 'state'
*/
void Draw::altervoxel(int x, int y, int z, int state)
{
  if (state)
  {
    setvoxel(x, y, z);
  } else
  {
    clrvoxel(x, y, z);
  }
}

/**
* Fill a value into all 64 byts of the cube buffer
* Mostly used for clearing. fill(0x00)
* or setting all on. fill(0xff)
*/
void Draw::fill (unsigned char pattern)
{
  int z;
  int y;
  for (z = 0; z < 8; z++)
  {
    for (y = 0; y < 8; y++)
    {
      cube[z][y] = pattern;
    }
  }
}

/**
* Flip the state of a LED.
*/ 
void Draw::flpvoxel(int x, int y, int z)
{
  if (inrange(x, y, z))
    cube[z][y] ^= (1 << x);
}

/**
* Makes sure x1 is alwas smaller than x2
* This is usefull for functions that uses for loops,
* to avoid infinite loops
*/
void Draw::argorder(int ix1, int ix2, int *ox1, int *ox2)
{
  if (ix1 > ix2)
  {
    int tmp;
    tmp = ix1;
    ix1 = ix2;
    ix2 = tmp;
  }
  *ox1 = ix1;
  *ox2 = ix2;
}


/////////////////
// Function wich fill a hole plane
////////////////


/**
* Sets all LEDs along a X/Y plane at a given point
* on axis Z
*/
void Draw::setplane_z (int z)
{
  int i;
  if (z >= 0 && z < 8)
  {
    for (i = 0; i < 8; i++)
      cube[z][i] = 0xff;
  }
}

/**
* Clears LED - plane at given z - coordinate
*/
void Draw::clrplane_z (int z)
{
  int i;
  if (z >= 0 && z < 8)
  {
    for (i = 0; i < 8; i++)
      cube[z][i] = 0x00;
  }
}

/**
* Sets all LEDs along a Z/Y plane at a given point
* on axis X
*/
void Draw::setplane_x (int x)
{
  int z;
  int y;
  if (x >= 0 && x < 8)
  {
    for (z = 0; z < 8; z++)
    {
      for (y = 0; y < 8; y++)
      {
        cube[z][y] |= (1 << x);
      }
    }
  }
}


/**
* Clears LED - plane at given x - coordinate
*/
void Draw::clrplane_x (int x)
{
  int z;
  int y;
  if (x >= 0 && x < 8)
  {
    for (z = 0; z < 8; z++)
    {
      for (y = 0; y < 8; y++)
      {
        cube[z][y] &= ~(1 << x);
      }
    }
  }
}

/**
* Sets all LEDs along a Z/X plane at a given point
* on axis X
*/
void Draw::setplane_y (int y)
{
  int z;
  if (y >= 0 && y < 8)
  {
    for (z = 0; z < 8; z++)
      cube[z][y] = 0xff;
  }
}

/**
* Clears LED - plane at given y - coordinate
*/
void Draw::clrplane_y (int y)
{
  int z;
  if (y >= 0 && y < 8)
  {
    for (z = 0; z < 8; z++)
      cube[z][y] = 0x00;
  }
}

/**
* Sets all LEDs along a plane at a given point
* on axis 'axis'
*/
void Draw::setplane (char axis, unsigned char i)
{
  switch (axis)
  {
    case AXIS_X:
      setplane_x(i);
      break;

    case AXIS_Y:
      setplane_y(i);
      break;

    case AXIS_Z:
      setplane_z(i);
      break;
  }
}

/**
* Clears all LEDs along a plane at a given point
* on axis 'axis'
*/
void Draw::clrplane (char axis, unsigned char i)
{
  switch (axis)
  {
    case AXIS_X:
      clrplane_x(i);
      break;

    case AXIS_Y:
      clrplane_y(i);
      break;

    case AXIS_Z:
      clrplane_z(i);
      break;
  }
}


// ===================================================================
// Draw boxes
// ===================================================================

/**
 *  Draw a box with all walls drawn and all LEDs inside set
*/
void Draw::box_filled(int x1, int y1, int z1, int x2, int y2, int z2)
{
  int iy;
  int iz;

  Draw::argorder(x1, x2, &x1, &x2);
  Draw::argorder(y1, y2, &y1, &y2);
  Draw::argorder(z1, z2, &z1, &z2);

  for (iz = z1; iz <= z2; iz++)
  {
    for (iy = y1; iy <= y2; iy++)
    {
      cube[iz][iy] |= byteline(x1, x2);
    }
  }

}

/**
 *  Darw a hollow box with side walls.
*/
void Draw::box_walls(int x1, int y1, int z1, int x2, int y2, int z2)
{
  int iy;
  int iz;

  argorder(x1, x2, &x1, &x2);
  argorder(y1, y2, &y1, &y2);
  argorder(z1, z2, &z1, &z2);

  for (iz = z1; iz <= z2; iz++)
  {
    for (iy = y1; iy <= y2; iy++)
    {
      if (iy == y1 || iy == y2 || iz == z1 || iz == z2)
      {
        cube[iz][iy] = byteline(x1, x2);
      } else
      {
        cube[iz][iy] |= ((0x01 << x1) | (0x01 << x2));
      }
    }
  }

}

/**
 * Draw a wireframe box. This only draws the corners and edges, no walls.
*/
void Draw::box_wireframe(int x1, int y1, int z1, int x2, int y2, int z2)
{
  int iy;
  int iz;

  argorder(x1, x2, &x1, &x2);
  argorder(y1, y2, &y1, &y2);
  argorder(z1, z2, &z1, &z2);

  // Lines along X axis
  cube[z1][y1] = byteline(x1, x2);
  cube[z1][y2] = byteline(x1, x2);
  cube[z2][y1] = byteline(x1, x2);
  cube[z2][y2] = byteline(x1, x2);

  // Lines along Y axis
  for (iy = y1; iy <= y2; iy++)
  {
    setvoxel(x1, iy, z1);
    setvoxel(x1, iy, z2);
    setvoxel(x2, iy, z1);
    setvoxel(x2, iy, z2);
  }

  // Lines along Z axis
  for (iz = z1; iz <= z2; iz++)
  {
    setvoxel(x1, y1, iz);
    setvoxel(x1, y2, iz);
    setvoxel(x2, y1, iz);
    setvoxel(x2, y2, iz);
  }

}

/**
 * Returns a byte with a row of 1's drawn in it. 
 * byteline(2,5) gives 0b00111100
*/
char Draw::byteline (int start, int end)
{
  return ((0xff << start) & ~(0xff << (end + 1)));
}

/**
 * MSB becomes LSB, LSB becomes MSB.
*/
char Draw::flipbyte (char byte)
{
  char flop = 0x00;

  flop = (flop & 0b11111110) | (0b00000001 & (byte >> 7));
  flop = (flop & 0b11111101) | (0b00000010 & (byte >> 5));
  flop = (flop & 0b11111011) | (0b00000100 & (byte >> 3));
  flop = (flop & 0b11110111) | (0b00001000 & (byte >> 1));
  flop = (flop & 0b11101111) | (0b00010000 & (byte << 1));
  flop = (flop & 0b11011111) | (0b00100000 & (byte << 3));
  flop = (flop & 0b10111111) | (0b01000000 & (byte << 5));
  flop = (flop & 0b01111111) | (0b10000000 & (byte << 7));
  return flop;
}


/**
 * Draw a line between any coordinates in 3d space.
 * Uses integer values for input, so dont expect smooth animations.
*/
void Draw::line(int x1, int y1, int z1, int x2, int y2, int z2)
{
  float xy; // how many voxels do we move on the y axis for each step on the x axis
  float xz; // how many voxels do we move on the y axis for each step on the x axis
  unsigned char x, y, z;
  unsigned char lasty, lastz;

  // We always want to draw the line from x=0 to x=7.
  // If x1 is bigget than x2, we need to flip all the values.
  if (x1 > x2)
  {
    int tmp;
    tmp = x2; x2 = x1; x1 = tmp;
    tmp = y2; y2 = y1; y1 = tmp;
    tmp = z2; z2 = z1; z1 = tmp;
  }


  if (y1 > y2)
  {
    xy = (float)(y1 - y2) / (float)(x2 - x1);
    lasty = y2;
  } else
  {
    xy = (float)(y2 - y1) / (float)(x2 - x1);
    lasty = y1;
  }

  if (z1 > z2)
  {
    xz = (float)(z1 - z2) / (float)(x2 - x1);
    lastz = z2;
  } else
  {
    xz = (float)(z2 - z1) / (float)(x2 - x1);
    lastz = z1;
  }



  // For each step of x, y increments by:
  for (x = x1; x <= x2; x++)
  {
    y = (xy * (x - x1)) + y1;
    z = (xz * (x - x1)) + z1;
    setvoxel(x, y, z);
  }

}

/**
 *  Shift the entire contents of the cube along an axis
 * This is great for effects where you want to draw something
 * on one side of the cube and have it flow towards the other
 * side. Like rain flowing down the Z axiz.
*/
void Draw::shift (char axis, int direction)
{
  int i, x , y;
  int ii, iii;
  int state;

  for (i = 0; i < 8; i++)
  {
    if (direction == -1)
    {
      ii = i;
    } else
    {
      ii = (7 - i);
    }


    for (x = 0; x < 8; x++)
    {
      for (y = 0; y < 8; y++)
      {
        if (direction == -1)
        {
          iii = ii + 1;
        } else
        {
          iii = ii - 1;
        }

        if (axis == AXIS_Z)
        {
          state = getvoxel(x, y, iii);
          altervoxel(x, y, ii, state);
        }

        if (axis == AXIS_Y)
        {
          state = getvoxel(x, iii, y);
          altervoxel(x, ii, y, state);
        }

        if (axis == AXIS_X)
        {
          state = getvoxel(iii, y, x);
          altervoxel(ii, y, x, state);
        }
      }
    }
  }

  if (direction == -1)
  {
    i = 7;
  } else
  {
    i = 0;
  }

  for (x = 0; x < 8; x++)
  {
    for (y = 0; y < 8; y++)
    {
      if (axis == AXIS_Z)
        clrvoxel(x, y, i);

      if (axis == AXIS_Y)
        clrvoxel(x, i, y);

      if (axis == AXIS_X)
        clrvoxel(i, y, x);
    }
  }
}

// Delay loop.
// This is not calibrated to milliseconds,
// but we had allready made to many effects using this
// calibration when we figured it might be a good idea
// to calibrate it.
void Draw::delay_ms(uint16_t x)
{
    uint8_t y, z;
    for ( ; x > 0 ; x--) {
        for ( y = 0 ; y < 90 ; y++) {
            for ( z = 0 ; z < 6 ; z++) {
                asm volatile ("nop");
            }
        }
    }
}
