
const int REED_PIN = 7; // Pin connected to reed switch
const int LED_PIN = 13; // LED pin - active-high
const int REED2_PIN = 11;
const int REED3_PIN = 6;

void setup() 
{
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
    digitalWrite(LED_PIN, HIGH); // Turn the LED on
  }
  else
  {
    digitalWrite(LED_PIN, LOW); // Turn the LED off
  }
}

