#define BUZZER_PIN 12
#define RLED_PIN 11
#define YLED_PIN 10
#define GLED_PIN 9
#define START_BTN_PIN 7

/*
Timer "class" represents the characteristics and behaviour of a timer
*/
struct Timer {
  // ATTRIBUTES
  int settime = 30; // seconds
  int processingDelay = 5;// minus 5 seconds for time to process (output, check status, etc.) while timer running

  // METHODS
};

/*
Turn LED on and then off.
*/
void blinkLED(int ledPin, int sec) {
  digitalWrite(ledPin, HIGH);
  delay(sec);
  digitalWrite(ledPin, LOW);
  delay(sec);
}

/*
Starts the timer, with status update and stops it when time is completed.
Returns true if completes without forced stop, false otherwise.
*/
bool start() {
  Timer current;
  
  current.settime = current.settime - current.processingDelay; // set actual time to run
  while(current.settime > 0) {
    delay(1000);
    current.settime--; // 1 second past

    if(digitalRead(START_BTN_PIN) == LOW) {
      delay(1000);
      
      return false; // premature stoppage, user decided to stop timer
    }

    blinkLED(YLED_PIN, 500);
  }

  return true; // successful completion
}

/*
Ring the buzzer for a few seconds. At a custom tone set by len and pauseSec.
*/
void ringBuzzer(int len, int pauseSec) {
  digitalWrite(GLED_PIN, HIGH); // show status
  
  for(int count = 0; count < 3; count++) {
    // One ring - 3 beeps
    for(int beep = 1; beep <= 3; beep++) {
      digitalWrite(BUZZER_PIN, HIGH);
      delay(len);
      digitalWrite(BUZZER_PIN, LOW);
      delay(len);
    }
    delay(pauseSec); // wait for next ring
  }

  digitalWrite(GLED_PIN, LOW); // clear status
}

/*
The main program of the timer. A stoppage loop that will start the timer when the start button is pressed.
*/
void stopLoop() {
  if(digitalRead(START_BTN_PIN) == LOW) {
    delay(1000); // give time to release button
    
    bool completed = start(); // start timer, start button pressed

    if(completed) {
      ringBuzzer(500, 1000); // ring; indicate timer successfully stopped, before re-entering stop loop
    }
  }

  // otherwise continue stoppage loop, red LED keeps blinking
  blinkLED(RLED_PIN, 1000);
}
 
void setup() {
  // Register output pins and input pins
  pinMode(RLED_PIN, OUTPUT);
  pinMode(YLED_PIN, OUTPUT);
  pinMode(GLED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(START_BTN_PIN, INPUT_PULLUP);
}

void loop() { 
  stopLoop();
}
