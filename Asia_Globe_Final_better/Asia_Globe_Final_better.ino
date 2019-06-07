#include <Arduino.h>
#include <TM1637Display.h>

#define CLK 2
#define DIO 3

#define LOC_1 11
#define LOC_2 7
#define LOC_3 6
#define LOC_COUNT 3

#define MAIN_TIMER_MILLIS 120000
#define RESET_TIMER_MILLIS 5000
#define LOCK_CODE 252

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

ProgramState prog_state = Off;
InputState input_state = None;
TM1637Display display(CLK, DIO);
unsigned long last_time = 0;

void setup()
{   
	pinMode(LOC_1, INPUT);
	pinMode(LOC_2, INPUT);
	pinMode(LOC_3, INPUT);

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
		input_state = None;
	}

	else if(input_ctr == LOC_COUNT)
	{
		input_state = All;
	}

	else
	{
		input_state = Some;
	}
	
	switch(prog_state)
	{
		case Off:
		{
			if(input_state == Some)
			{
				last_time = millis();
				prog_state = Timer;
			}

			else if(input_state == All)
			{
				prog_state = ShowCode;
			}
		break;
		}


		case Timer:
		{
			if(input_state == None)
			{
				prog_state = Reset;
			}

			else if(input_state == All)
			{
				prog_state = ShowCode;
			}
			else
			{
				unsigned long now = millis();
				unsigned long elapsed = now - last_time;
				if(elapsed >= MAIN_TIMER_MILLIS)
				{
					last_time = millis();
					prog_state = Reset;
				}

				display.showNumberDec(millis_to_timer(elapsed), false, 4, 1);
			}
		break;
		}
		case Reset:
		{
			unsigned long now = millis();
			unsigned long elapsed = now - last_time;
			if(elapsed >= RESET_TIMER_MILLIS)
			{
				prog_state = Off;
			}

			display.showNumberDec(millis_to_timer(elapsed), false, 4, 1);
		    break;	
		}
		

		case ShowCode:
		{
			display.showNumberDec(LOCK_CODE, false, 3,1);
			delay(1000);
			prog_state = Off;

			break;
		}
		

	}

}


