
#include <Arduino.h>
#include <TM1637Display.h>

#define CLK 2
#define DIO 3
#define LOC_1 4
#define LOC_2 5
#define LOC_3 6



#define MAIN_COUNTDOWN 120000

#define RESET_COUNTDOWN 5000
 
#define TEST_DELAY   2000

#define CODE 123

enum State
{
  Off,
  Timer,
  Reset,
  Code,
}

State program_state = State::Off; // verivle od the state and the on the begining is off

DisplayState state = Off
DisplayState state = DipsplayState::Off;

enum InputState
{
  None,
  Some,
  All,
}

InputState Love = InputState::None;

void loop () {

int input_ctr = 0;
if(digitalRead(LOC_1) == HIGH) //  a number!!! we are counting how many magnets we have on it
 {
   Input_ctr ++; //

  }
}


