
// 1- Tanuj Dave - 665028452
// 2- Lab 3
// 3- Description - display name and scrolling quote on a led screen
// 4- Hardware working properly and lab demo circuit
// 5- https://docs.arduino.cc/learn/electronics/lcd-displays
// 6- Demo: 2/21/2022 4:20 pm grader: Huma Tejaswi


// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

// creating the variables
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
String quote = " \"Uneasy lies the head that wearth the crown.\" ";
long int show = 0; // index to start the quote on the display from

void setup() {
  // setting up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.print("Tanuj Dave"); // printing my name
}

void loop() {
  // set the cursor to (16,1):
  lcd.setCursor(0, 1);

  // printing all the character in the quote form the starting index (show) and wrapping it around  
  for(int i = 0; i < 16; i++) {
    lcd.print(quote[(show+i)%quote.length()]);
  }

  // delaying to make it readable
  delay(300);
  show++; // incrementing to the next index
}
