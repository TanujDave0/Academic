// 1- Tanuj Dave - 665028452
// 2- Lab 6
// 3- Description - make leds lit based on the amount of light received by the photoreceiver
// 4- Hardware working properly and lab demo circuit
// 5- https://create.arduino.cc/projecthub/SBR/working-with-an-led-and-a-push-button-71d8c1 https://www.arduino.cc/en/reference/serial
// 6- Demo: 3/28/2022 4:23 pm grader: Anjani


// declaring variables for led and button
int led = 8;
int button = 7;

// state of the led
int s = 0;
int b = 0; // reading serial
boolean bp = true; // button pressed tracker

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(button, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) { // if other arduino sent something
    int a = Serial.read();
    if (a) { // if its 1
      s = (s+1)%2; // change the state
      if (s) {
        digitalWrite(led, HIGH); // if state is 1 light the led
      } else {
        digitalWrite(led, LOW); // if state is 0 turn off the led
      }
    }
  }

  b = digitalRead(button); // read the button
  
  if (b == HIGH && bp) { // if button is pressed and previpusly was not pressed
    Serial.write(1); // send signal to other arduino
    bp = false;
  }
  
  if (b == LOW){ // if the button is low
    bp = true; // set button pressed to true
  }
  
  delay(10);
}
