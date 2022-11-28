// 1- Tanuj Dave - 665028452
// 2- Lab 8
// 3- Description - plot graph based on photoresistor and potentiometer readings
// 4- Hardware working properly and lab demo circuit
// 5- https://docs.arduino.cc/built-in-examples/communication/Graph https://processing.org/reference/splitTokens_.html https://processing.org/reference/
// 6- Demo: 11/4/2022 4:05 pm grader: Amir

import processing.serial.*;

Serial myPort;        // The serial port
int xPos = 1;         // horizontal position of the graph
float inByte1 = 0;
float inByte2 = 0;
float prevh1 = 0;
float prevh2 = 0;

void setup () {
  // set the window size:
  size(400, 400);
  
  myPort = new Serial(this, Serial.list()[7], 9600);

  myPort.bufferUntil('\n');
  
  background(0);
}

void draw () {
  // setting a color
  stroke(127, 34, 255);
  line(xPos, prevh1, xPos-1, height - inByte1); // potentiometer
  
  // setting a different color
  stroke(0, 34, 255);
  line(xPos, prevh2, xPos-1, height - inByte2); // photo resistor

  if (xPos >= width) {
    xPos = 0;
    background(0);
  } else {
    xPos++;
    prevh1 = height - inByte1; // prev stored for drawing a line
    prevh2 = height - inByte2; // prev stored for drawing a line
  }
}

void serialEvent (Serial myPort) {
  String inString = myPort.readStringUntil('\n');

  if (inString != null) {
    // splitting to get differnet analog inputs
    String[] in = splitTokens(inString);
    
    // getting the analog inputs
    inByte1 = float(in[0]);
    inByte2 = float(in[1]);
    
    // print for debug
    println(in[0], in[1]);
    
    // mapping
    inByte1 = map(inByte1, 0, 1023, 0, height);
    inByte2 = map(inByte2, 0, 1023, 0, height);
  }
}
