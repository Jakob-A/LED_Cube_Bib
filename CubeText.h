/*
    Library with functions to write text at the LED Cube
*/

#ifndef CText_h
#define CText_h



class CText
{




private:
        /* data */

        /**
         * seperates the two digits of a number below 100
         */
        static void Vereinzeln(int k, int *Zehner, int *Einer);

        
        static unsigned char bitswap (unsigned char x);

    public:
        /**
         * gets Text and writes it onto the LED Cube
         */
        static void effect_textBle(int delayt, char * input);

        /**
         * Displays the time on the Cube
         */
        static void effect_textUHR(int minutes, int hours, int seconds);

        /**
         * Prints numbers passed by 'time' to one side of the Cube
         */
        static int printOutside(int time, int side);
};


#endif
