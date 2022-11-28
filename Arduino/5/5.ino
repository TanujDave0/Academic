// 1- Tanuj Dave- 665028452
// 2- Lab 5 - Communication 
// 3- Take date and time input from user from serial monitor and diplay the time starting from given time on lcd display
// 4- working hardware and correct circuit
// 5- : http://arduino.cc/en/Reference/Serial#.UwYyzfldV8E http://arduino.cc/en/Serial/Available#.UwYy2PldV8E http://arduino.cc/en/Serial/ReadBytesUntil#.UwYy6_ldV8E http://playground.arduino.cc/Code/Time#.UwYyQPldV8E https://docs.arduino.cc/learn/electronics/lcd-displays
// 6- Demo: https://youtu.be/fIJ8qbujJyY

// impoting the libraries
#include <LiquidCrystal.h>
#include <Time.h>
#include <TimeLib.h>

// creating booleans to keep track of the inputs
boolean d = false;
boolean t = true;

// declaring variables to take input
int dd = 0;
int mm = 0;
int yyyy = 0;

int hh = 0;
int mi = 0;
int ss = 0;

// lcd variables
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// list of all maximum dates for each month (non-leap year)
int dates[] = {31,28,31,30,31,30,31,31,30,31,30,31};

void setup() {
  Serial.begin(9600); // begining the serial monitor
  lcd.begin(16, 2); // begining the lcd
  lcd.print("the timekeeper");
}

void loop() {
  // put your main code here, to run repeatedly:

  // if correct inputs are not yet given
  while (!d) {
    Serial.flush();
    t = true; // assume that inputs are true.
    Serial.println("Please enter a date and time (mm/dd/yyyy hh/mm/ss) (seperated by a space): ");

    // wait till input given
    while (Serial.available() == 0) {
      
    }

    // take all input
    char b[19];
    int s = Serial.readBytesUntil('\n', b, 19);

    // convert chars to integers
    mm = (b[0]-'0')*10 + (b[1]-'0');
    dd = (b[3]-'0')*10 + (b[4]-'0');
    yyyy = (b[6]-'0')*1000 + (b[7]-'0')*100 + (b[8]-'0')*10 + (b[9]-'0');

//    Serial.println(mm);
//    Serial.println(dd);
//    Serial.println(yyyy);
//    
    hh = (b[11]-'0')*10 + (b[12]-'0');
    mi = (b[14]-'0')*10 + (b[15]-'0');
    ss = (b[17]-'0')*10 + (b[18]-'0');

//    Serial.println(hh);
//    Serial.println(mi);
//    Serial.println(ss);


     // check for all date and time constraints
    if (mm < 0 || mm > 12) {
      Serial.println("Please enter month between 1 and 12");
      t = false;
    }
    if (dd < 0 || (yyyy%4 == 0 && mm == 2 && dd > 29) || (yyyy%4 > 0 && mm == 2 && dd > 28) || dd > dates[mm-1]) {
      Serial.println("Please enter a valid date by month");
      t = false;
    }
    if (yyyy < 0) {
      Serial.println("Please enter a valid date by year");
      t = false;
    }
    if (hh < 0 || hh > 23) {
      Serial.println("Please enter a valid hour");
      t = false;
    }
    if (mi < 0 || mi > 59) {
      Serial.println("Please enter a valid minute");
      t = false;
    }
    if (ss < 0 || ss > 59) {
      Serial.println("Please enter a valid second");
      t = false;
    }

    // if the inputs are within correct bounds
    if (t) {
      d = true;
      setTime(hh,mi,ss,dd,mm,yyyy); // set the time
    }
    Serial.flush();
  }

   // if correct inputs taken
  if (d) {
    lcd.clear();
    
    // print info
    lcd.setCursor(0, 0);
    lcd.print("date: ");
    lcd.setCursor(0,1);
    lcd.print("time: ");

     // print date
    lcd.setCursor(6, 0);
  
    lcd.print(month());
    lcd.print("/");
    lcd.print(day());
    lcd.print("/");
    lcd.print(year());

    // print time
    lcd.setCursor(6, 1);
  
    lcd.print(hour());
    lcd.print(":");
    lcd.print(minute());
    lcd.print(":");
    lcd.print(second());
  
    delay(1000); // wait for a second
  }
}


// wrong leap year date
// 02/30/2020 23/59/57

// wrong non leap year date
// 02/29/2021 23/59/57

// wrong date
// 04/31/2021 23/59/57

// wrong month
// 13/30/2021 23/59/57

// wrong hour
// 12/12/2021 29/59/57

// wrong minute
// 12/12/2021 23/67/57

// wrong second
// 12/12/2021 23/55/99

// right leap year
// 02/28/2020 23/59/57

// right non leap year
// 02/28/2021 23/59/57
