int switchPin = 2;              // switch is connected to pin 2
    int led1Pin = 8;
    int led2pin = 4;

    int val;                        // variable for reading the pin status
    int val2;                       // variable for reading the delayed status
    int buttonState;                // variable to hold the button state
    int Mode = 0;              // What mode is the light in?

    void setup() {
      pinMode(switchPin, INPUT);  
      // Set the switch pin as input
      pinMode(led1Pin, OUTPUT);
      pinMode(led2pin, OUTPUT);
      buttonState = digitalRead(switchPin);   // read the initial state
    }

    void loop(){
      val = digitalRead(switchPin);      // read input value and store it in val
      delay(10);                         // 10 milliseconds is a good amount of time
      val2 = digitalRead(switchPin);     // read the input again to check for bounces
      if (val == val2) {                 // make sure we got 2 consistant readings!
        if (val != buttonState) {          // the button state has changed!
          if (val == LOW) {                // check if the button is pressed
            if (Mode == 0) {          
              Mode = 1;               
            } else {
                if (Mode == 1) {        
                Mode = 2;           
            } else {
                if (Mode == 2) {      
                Mode = 3;           
            } else {
                if (Mode == 3) { 
                Mode = 0;          
                  }
            }
           }
          }
         }
        }
        buttonState = val;                 // save the new state in our variable
      }

      // Now do whatever the lightMode indicates
      if (Mode == 0) { // all-off
        digitalWrite(led1Pin, LOW);
        digitalWrite(led2pin, LOW);
      }

      if (Mode == 1) { 
        digitalWrite(led1Pin, HIGH);
        digitalWrite(led2pin, LOW);
      }

      if (Mode == 2) { 
        digitalWrite(led1Pin, LOW);
        digitalWrite(led2pin, HIGH);
      }
      if (Mode == 3)  { 
        digitalWrite(led1Pin, HIGH);
        digitalWrite(led2pin, HIGH);
      }    
    }

