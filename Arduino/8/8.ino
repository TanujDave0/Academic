
// 1- Tanuj Dave - 665028452
// 2- Lab 8
// 3- Description - plot graph based on photoresistor and potentiometer readings
// 4- Hardware working properly and lab demo circuit
// 5- https://docs.arduino.cc/built-in-examples/communication/Graph https://processing.org/reference/splitTokens_.html https://processing.org/reference/
// 6- Demo: 4/11/2022 4:05 pm grader: Amir

void setup() {
  // initialize the serial communication:
  Serial.begin(9600);
}

void loop() {
  // getting and printing the reading from potentiometer
  Serial.print(analogRead(A0));
  Serial.print(" "); // adding a space to seperate the readings

  // getting and printing the reading from the photoresistor
  Serial.println(analogRead(A1));
  delay(10);
}
