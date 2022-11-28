// grader : Huma Tejaswi Akkem
// 1- Tanuj Dave - 665028452
// 2- Lab 2 - Input Output
// 3- Description - blink 3 leds accrding to 3 bit coutner using 2 buttons
// 4- Hardware working properly and lab demo circuit
// 5- https://docs.arduino.cc/built-in-examples/digital/Button
// 6- Demo: in-person demonstration 1/31/2022, 4:50 pm, instructor (GRADER): Huma Tejaswi Akkem


// to check if the button was released
boolean a = true;
boolean b = true;

// 3 bit coutner as an integer
int bit3 = 0;

// increment and decrement button input
int inc = 0;
int dec = 0;

// the two buttons
const int button1 = 2;
const int button2 = 1;

// the 3 LEDs
const int led1 =  12; 
const int led2 = 11;
const int led3 = 10;

// setting up
void setup() {
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
}


// main loop
void loop() {

  // reading the button input
  inc = digitalRead(button1);
  dec = digitalRead(button2);

  // check if the button was pressed
  if (inc == HIGH) {
    if (bit3 < 7 && a) { // increment only if its less than 7 and is unpressed
      bit3++;
      a = false;
    }
  }

  // set button to unpressed
  if (inc == LOW) {
    a = true;
  }

  
  // check if the button was pressed
  if (dec == HIGH) {
    if (bit3 > 0 && b) { // decrement if greater than 7 and is unpressed
      bit3--;
      b = false;
    }
  }

  // set button to unpressed
  if (dec == LOW) {
    b = true;
  }


  // left shift integer to check the bits and set LEDs
  if (bit3 %2 == 1) digitalWrite(led1, HIGH);
  else digitalWrite(led1, LOW);
  
  if ( (bit3>>1) %2 == 1) digitalWrite(led2, HIGH);
  else digitalWrite(led2, LOW);
  
  if ( (bit3>>2) %2 == 1) digitalWrite(led3, HIGH);
  else digitalWrite(led3, LOW);
}
