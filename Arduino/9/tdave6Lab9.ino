// 1- Tanuj Dave - 665028452
// 2- Lab 9
// 3- Description - make lcd print based on the amount of light received by the photoreceiver
// 4- Hardware working properly and lab demo circuit
// 5- https://create.arduino.cc/projecthub/SURYATEJA/use-a-buzzer-module-piezo-speaker-using-arduino-uno-89df45
// 6- Demo: 4/11/2022 4:35 pm grader: Amir

#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// a value to take input from analog
long int val = 0;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  Serial.begin(9600);
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);

  lcd.clear();
  val = analogRead(A0);
  Serial.println(val);

  // if no light 
  if (val < 10) {
    lcd.print("dark");
  } else if (val < 1023/4) { // if 1/4 of light received
    lcd.print("partially dark");
  } else if (val < 1023/2) { // if 1/2 of light received
    lcd.print("medium");
  } else if (val < (3*1023)/4) { // if 3/4 of light received
    lcd.print("partially lit");
  } else {  // if max light received
    lcd.print("fully lit");
  }

  delay(100);
}
