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
    delay(300); // wait (give time to release), QUESTION: without this line (delay) LED may switch-on and back off OR off and back on, quickly (almost as if not responding to button push)

    // wait for switch to be release (switch toggle/press completes on release), user is press-holding
    while(digitalRead(INPUT_PIN) == LOW) {
      // busy wait
    }
    
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
