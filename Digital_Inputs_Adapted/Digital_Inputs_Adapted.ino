#define LED_PIN 9
#define INPUT_PIN 5

bool isLedOn = false;

/*
Set output and input pins
*/
void setup() 
{
  pinMode(LED_PIN, OUTPUT);
  pinMode(INPUT_PIN, INPUT_PULLUP); // default input is high (Switch is not pressed)
  digitalWrite(LED_PIN, LOW); // initially off
}

/*
Continuously alternate the state of the LED when switch pressed.
*/
void loop() 
{
  // if the switch is pressed
  if(digitalRead(INPUT_PIN) == LOW) {
    delay(1000);  // give user time to take hand of the switch (otherwise, the program may go through 2+ states within one press, because it's that fast and we're that slow
    changeLED();
  }
}

/*
Change the state of the LED to opposite of isLedOn state.
*/
void changeLED() {
  if(isLedOn) {
    digitalWrite(LED_PIN, LOW); // it is on, turn off
  }
  else {
    digitalWrite(LED_PIN, HIGH); // it is off, turn on
  }

  isLedOn = !isLedOn; // update isOn state to opposite of current
}
