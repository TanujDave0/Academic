int record = 2;
int pe = 3;
int df = 5;

int p = 10000; // 10 secs
int r = 10000;

void setup() {
    Serial.begin(9600);
    pinMode(record , OUTPUT);
    pinMode(pe , OUTPUT);
    pinMode(df , OUTPUT);
}

void loop() {
    // read from serial
    while (Serial.available() > 0) {
        char inChar = (char)Serial.read();
        if (inChar == 'p' || inChar == 'P') {
            digitalWrite(pe , HIGH);
            delay(50);
            digitalWrite(pe , LOW);
            delay(p);
            break;
        } else if (inChar == 'r' || inChar == 'R') {
            digitalWrite(record , HIGH);
            delay(r);
            digitalWrite(record , LOW);
        }
    }
    
    Serial.println("Enter r to record, p to play");
    delay(500);
}
