#include <Arduino.h>
#include <TM1637Display.h>

#define CLK 2
#define DIO 3

const int REED_PIN = 7; // Pin connected to reed switch
const int LED_PIN = 13; // LED pin - active-high
const int REED2_PIN = 11;
const int REED3_PIN = 6;

TM1637Display display(CLK, DIO);

void setup() 
{ 
  display.setBrightness(0x0f); // I am setting Brightness
  Serial.begin(9600);
  // Since the other end of the reed switch is connected to ground, we need
  // to pull-up the reed switch pin internally.
  pinMode(REED_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  pinMode(REED2_PIN, INPUT_PULLUP);
  pinMode(REED3_PIN, INPUT_PULLUP);
}

void loop() 
{
  int check_sw1 = digitalRead(REED_PIN);
  int check_sw2 = digitalRead(REED2_PIN);
  int check_sw3 = digitalRead(REED3_PIN);

  if (check_sw1 == LOW and check_sw2 == LOW and check_sw3 == LOW) // If the pin reads low, the switch is closed.
  {
    Serial.println("Done");
    digitalWrite(LED_PIN, HIGH);
    display.showNumberDec(562, false, 3,1);
  }
  else
  {
    digitalWrite(LED_PIN, LOW); // Turn the LED off
  }
}
