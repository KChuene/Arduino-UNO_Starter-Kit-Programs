#define RED 3
#define GREEN 5
#define BLUE 6


int* RGB_code = NULL;

/**
  Setup output pins and the initial color.
**/
void setup() {
  // put your setup code here, to run once:
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
}

/**
  Create and initialise and RGB code
**/
int* initRGB(int* code) {
  // Don't create instance if already exist
  if(!code) {
    code = new int[3];
  }
  
  // Re/init bits to 0
  for(int i=0; i<3; i++) {
    code[i] = 0;
  }

  return code;
}

/**
  Convert decimal value to it's binary representation (last 3 bits) in integer array format
**/
int* getBinaryCode(int decimal) {
  
  if(decimal < 0 || decimal > 7) {
    return NULL;
  }
  
  int* code = initRGB(NULL); // {0, 0, 0}

  // Counting from pos 2 to 0 (3 bits) each remainder (decimal mod 2) will either be 1 or 0
  int remainder = decimal;
  int bitPos = 2;
  while(decimal > 0 && bitPos >= 0) {

    // Set bit at bitPos to remainder
    remainder = decimal % 2;
    code[bitPos] = remainder;

    bitPos--;
    decimal = decimal / 2;
  }
  return code;
}

/**
  Set provided output pin to HIGH based on the provided codeBit (1=HIGH, 0=LOW)
**/
void outputRGB(int codeBit, int pin) {
  if(codeBit > 0) {
    digitalWrite(pin, HIGH);
  }
  else {
    digitalWrite(pin, LOW);
  }
}

/*
  Output all possible RGB colors using a digital signal.
*/
void digitalRGB() {
  // 1. Count from 0 to 7 (repeatedly), numbers 0 to 7 represent the possible colors (000 to 111)
  // 2. convert each number to binary and 
  // 3. set the RGB bits to corespond to each number bit, and output

  for(int decimal = 0; decimal <= 7; decimal++) {
    RGB_code = getBinaryCode(decimal);

    // default to black, if could not convert decimal
    if(RGB_code == NULL) {
      RGB_code = initRGB(NULL);
    }

    // check each RGB code bit
    // set RGB OUTPUT to correspond to RGB code bit (HIGH/1 or LOW/0)
    outputRGB(RGB_code[0], RED);
    outputRGB(RGB_code[1], GREEN);
    outputRGB(RGB_code[2], BLUE);

    // wait 1 second before next color
    delay(1000);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalRGB();
}
