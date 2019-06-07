#include <Keyboard.h>

#define DEBOUNCE 10  // ms to debounce

//                U  D  L  R
byte buttons[] = {4, 5, 6, 7};
#define NUMBUTTONS sizeof(buttons)

// we will track if a button is just pressed, just released, or 'currently pressed' 
volatile byte pressed[NUMBUTTONS];
volatile byte justpressed[NUMBUTTONS]
volatile byte justreleased[NUMBUTTONS];

void setup()
{
  byte i;

  // Set all inputs pullups
  for (i=0; i<NUMBUTTONS, i++)
  {
    pinMode(buttons[i],INPUT_PULLUP);
  }
 
  // set up keyboard emulation
  Keyboard.begin();

  // Run timer2 interrupt every 15 ms 
  TCCR2A = 0;
  TCCR2B = 1<<CS22 | 1<<CS21 | 1<<CS20;

  //Timer2 Overflow Interrupt Enable
  TIMSK2 |= 1<<TOIE2;
}

// Call checkswitches when interrupt fires. 
SIGNAL(TIMER2_OVF_vect) {
  check_switches();
}

// Checks state of switches
void check_switches()
{
  static byte previousstate[NUMBUTTONS];
  static byte currentstate[NUMBUTTONS];
  static long lasttime;
  byte index;

  if (millis() // we wrapped around, lets just try again
     lasttime = millis();
  }
  
  if ((lasttime + DEBOUNCE) > millis()) {
    // not enough time has passed to debounce
    return; 
  }
  // ok we have waited DEBOUNCE milliseconds, lets reset the timer
  lasttime = millis();
  
  for (index = 0; index digitalRead(buttons[index]);   // read the button
    
    if (currentstate[index] == previousstate[index]) {
      if ((pressed[index] == LOW) && (currentstate[index] == LOW)) {
          // just pressed
          justpressed[index] = 1;
      }
      else if ((pressed[index] == HIGH) && (currentstate[index] == HIGH)) {
          // just released
          justreleased[index] = 1;
      }
      pressed[index] = !currentstate[index];  // remember, digital HIGH means NOT pressed
    }
    previousstate[index] = currentstate[index];   // keep a running tally of the buttons
  }
}


void loop()
{
 for (byte i = 0; i if (justpressed[i]) {
      justpressed[i] = 0;
      if      (i==0) Keyboard.press('w');
      else if (i==1) Keyboard.press('a');
      else if (i==2) Keyboard.press('s');
      else if (i==3) Keyboard.press('d');
    }
    if (justreleased[i]) {
      justreleased[i] = 0;
      if      (i==0) Keyboard.release('w');
      else if (i==1) Keyboard.release('a');
      else if (i==2) Keyboard.release('s');
      else if (i==3) Keyboard.release('d');
    }
  }