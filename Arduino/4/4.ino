
// 1- Tanuj Dave - 665028452
// 2- Lab 4
// 3- Description - make leds lit based on the amount of light received by the photoreceiver
// 4- Hardware working properly and lab demo circuit
// 5- https://create.arduino.cc/projecthub/SURYATEJA/use-a-buzzer-module-piezo-speaker-using-arduino-uno-89df45
// 6- Demo: 2/28/2022 4:05 pm grader: Huma Tejaswi

// declaring all the leds and buzzer
int led1 = 8;
int led2 = 9;
int led3 = 10;
int led4 = 11;
int buzzer = 6;

// a value to take input from analog
long int val = 0;

void setup() {
  // setting all the leds and buzzer pins for output
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  val = analogRead(A0);
  Serial.println(val);

  // if no light all leds are lit
  if (val == 0) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
  } else if (val < 1023/4) { // if 1/4 of light received, light 3/4 leds
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    Serial.println("lol2");
  } else if (val < 1023/2) { // if 1/2 of light received, light 2/4 leds
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
  } else if (val < (3*1023)/4) { // if 3/4 of light received, light 1/4 leds
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
  } else {  // if max light received, light 0/4 leds
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
  }

  val = analogRead(A2); // take input from potentiometer
  
  analogWrite(buzzer, val/10); // make buzzer output vary (did /10 to make it more sensitive)
  
  delay(100); // delay
}
