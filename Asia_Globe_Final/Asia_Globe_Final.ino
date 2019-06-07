#include <Arduino.h>

#include <TM1637Display.h>



#define CLK 2

#define DIO 3



#define LOC_1 4

#define LOC_2 5

#define LOC_3 6

#define LOC_COUNT 3



#define MAIN_TIMER_MILLIS 120000

#define RESET_TIMER_MILLIS 5000

#define LOCK_CODE 123



enum ProgramState
{

	Off,

	Timer,

	Reset,

	ShowCode,

};



enum InputState

{

	None,

	Some,

	All,

};



int millis_to_timer(unsigned long millis)

{

	float secs = millis / 1000.0;

	float mins = secs / 60.0;

	secs = (mins - floor(mins)) * 60.0;

	mins = floor(mins);

	return (int)mins * 100 + (int)secs;

}



ProgramState prog_state = ProgramState::Off;

InputState input_state = InputState::None;

TM1637Display display(CLK, DIO);

unsigned long last_time = 0;



void setup()

{

	display.setBrightness(0x0f);

}



void loop()

{

	int input_ctr = 0;

	if(digitalRead(LOC_1) == HIGH)

	{

		input_ctr++;

	}

	if(digitalRead(LOC_2) == HIGH)

	{

		input_ctr++;

	}

	if(digitalRead(LOC_3) == HIGH)

	{

		input_ctr++;

	}



	if(input_ctr == 0)

	{

		input_state = InputState::None;

	}

	else if(input_ctr == LOC_COUNT)

	{

		input_state = InputState::All;

	}

	else

	{

		input_state = InputState::Some;

	}



	switch(prog_state)

	{

		case ProgramState::Off:

		{

			if(input_state == InputState::Some)

			{

				last_time = millis();

				prog_state = ProgramState::Timer;

			}

			else if(input_state == InputState::All)

			{

				prog_state = ProgramState::ShowCode;

			}

		}

		case ProgramState::Timer:

		{

			if(input_state == InputState::None)

			{

				prog_state = ProgramState::Reset;

			}

			else if(input_state == InputState::All)

			{

				prog_state = ProgramState::ShowCode;

			}

			else

			{

				unsigned long now = millis();

				unsigned long elapsed = now - last_time;

				if(elapsed >= MAIN_TIMER_MILLIS)

				{

					last_time = millis();

					prog_state = ProgramState::Reset;

				}

				display.showNumberDec(millis_to_timer(elapsed), false, 4, 1);

			}

		}

		case ProgramState::Reset:

		{

			unsigned long now = millis();

			unsigned long elapsed = now - last_time;

			if(elapsed >= RESET_TIMER_MILLIS)

			{

				prog_state = ProgramState::Off;

			}

			display.showNumberDec(millis_to_timer(elapsed), false, 4, 1);

		}

		case ProgramState::ShowCode:

		{

			display.showNumberDec(LOCK_CODE, false, 3,1);

			delay(1000);

			prog_state = ProgramState::Off;

		}

	}

}
