/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly. Turns LED on and off 
  faster after a certain amount of time has passed (it alarms for a few seconds), and then 
  resets.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
*/

int secPast = 0;
int timeout = 60;
bool execAlarm = false;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  if(execAlarm) {
    alarm(); // make alarm (timeout)
  }

  // Restart / continue counting
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  count();                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  count();                       // wait for a second
}

void count() {
  // unnecessary (all this can be done in calling function
  
  delay(1000);
  if(secPast < timeout) {
    execAlarm = false;
    secPast += 1; // one more second has past (record)
  }
  else {
    secPast = 0;  // time passed has reached timeout (reset)
    execAlarm = true; // can raise alarm (blink faster)
  }
}

void alarm() {

    // alarm for a few(10) seconds then break (snooze, sought of) - blink twice each second
    for(int s = 1; s <= 10; s++) {
      // NOT GOOD - Logic of covering 10 seconds of blinks might be off
      digitalWrite(LED_BUILTIN, HIGH);
      delay(200);
      digitalWrite(LED_BUILTIN, LOW);
      delay(200);
      digitalWrite(LED_BUILTIN, HIGH);
      delay(200);
      digitalWrite(LED_BUILTIN, LOW);
      delay(200);
      // last HIGH outside of loop
    }
    
}
