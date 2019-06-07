
 /*
 * This is the Arduino code for TM1637 4 digits display.
 *  * 
 * Written by Ahmad S. for Robojax Video
 * Date: Dec 06, 2017, in Ajax, Ontario, Canada
 * Permission granted to share this code given that this
 * note is kept with the code.
 * Disclaimer: this code is "AS IS" and for educational purpose only.
 * 
 */

/*
 * Original code from https://github.com/avishorp/TM1637
 * Modified for Robojax video on Dec 06, 2017

 */
#include <Arduino.h>
#include <TM1637Display.h>

// Module connection pins (Digital Pins)
#define CLK 2
#define DIO 3

// The amount of time (in milliseconds) between tests
#define TEST_DELAY   2000


TM1637Display display(CLK, DIO);

void setup()
{
}

void loop()
{


  display.setBrightness(0x0f);

  uint8_t data[] = { 0x0, 0x0, 0x0, 0x0 };
  display.setSegments(data);
  display.showNumberDec(333, false, 3,1);
  delay(TEST_DELAY);
  
  display.setSegments(data);
  display.showNumberDec(333, false, 3, 1);
  delay(TEST_DELAY);

  display.setSegments(data);
  for(int i=0; i<=500; i++)
  {
    display.showNumberDec(i);
  }

}
 
