// 1- Tanuj Dave - 665028452
// 2- Lab 7
// 3- Description - display prompts and time as interrupted by buttons
// 4- Hardware working properly and lab demo circuit
// 5- https://www.arduino.cc/en/Reference/Millis https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/ https://docs.arduino.cc/learn/electronics/lcd-displays 
// 6- Demo: 4/4/2022 3:55 pm grader: anshuman

#include <LiquidCrystal.h>

//declaring variables for the lcd
const int rs = 12, en = 11, d4 = 7, d5 = 6, d6 = 5, d7 = 4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


// declaring buttons
int button1 = 2;
int button2 = 3;

// boolean to trank button 1 pressed
bool bp = false;

// stroe the previous millis();
unsigned  long prev = 0;

void setup() {
  // lcd
  lcd.begin(16, 2);
  
  // buttons for interrupts
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);

  // attaching interrupt functions
  attachInterrupt(digitalPinToInterrupt(button1), b1, RISING);
  attachInterrupt(digitalPinToInterrupt(button2), b2, RISING);
}

void loop() {
  // if the buttons is not pressed
  if (!bp) {
    lcd.setCursor(0,0);
    lcd.print("We have been waiting for ");
    lcd.setCursor(0, 1);
    lcd.print((millis() - prev) / 1000);
    lcd.print("s");
    delay(500); // wait for some time for lcd to show the prompt properly
    lcd.clear();
  } else { // if it is pressed print the prompt
    lcd.setCursor(0,0);
    lcd.print("Interrupt received!");
    lcd.setCursor(0,1);
    lcd.print("Press button 2 to continue");
    delay(500); // wait for some time for lcd to show the prompt properly
    lcd.clear();
  }
  
}

// button 2 interrupt
void b2() {
  if (bp) { // if buttons 1 is not pressed, then skip over
    prev = millis(); // store the current millis for sub
    bp = false; // set button 1 to unpressed
  }
}

// button 1 interrupt
void b1() {
  if (!bp) { // if it is pressed then skip over
    bp = !bp; // change the state
  }
}
