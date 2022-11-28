// grader : Amir
// 1- Tanuj Dave - 665028452
// 2- Lab 1 - Get started with Arduino
// 3- Description - Blink 3 LEDs in a sequence
// 4- Hardware working properly and lab demo circuit
// 5- no references
// 6- Demo: in-person demonstration 1/24/2022, 4:25 pm, instructor (GRADER): Amir


int period = 500;
unsigned long time_now = 0;


void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(9, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  
  while(millis() < time_now + period) {}
  time_now += period;
  digitalWrite(LED_BUILTIN, LOW);

  while(millis() < time_now + period) {}
  time_now += period;

  digitalWrite(12, HIGH);

  while(millis() < time_now + period) {}
  time_now += period;
  digitalWrite(12, LOW);

  while(millis() < time_now + period) {}
  time_now += period;

  digitalWrite(9, HIGH);

  while(millis() < time_now + period) {}
  time_now += period;
  digitalWrite(9, LOW);

  while(millis() < time_now + period) {}
  time_now += period;
}
