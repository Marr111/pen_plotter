uint8_t penna = 5;

uint8_t stepPin1 = 9;
uint8_t dirPin1 = 11;
int steps1 = 200; // you should increase this if you are using
// some of microstepping modes

uint8_t stepPin2 = 3;
uint8_t dirPin2 = 5;
int steps2 = 200; // you should increase this if you are using
// some of microstepping modes

int usDelay = 700; // minimal is 950 for full step mode and NEMA15 motor
// minimal is 35 for sixteenth step mode

void setup() {
  Serial.begin(9600);
  pinMode(stepPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);

  pinMode(stepPin2, OUTPUT);
  pinMode(dirPin2, OUTPUT);

  pinMode(penna, OUTPUT);
}

void loop() {
  digitalWrite(penna, HIGH);

  for (int st = 1; st < 15; st++) {
    steps1 = 100 * st;
    steps2 = 100 * st;
    
    for (int i = 0; i < 3; i++) {
      digitalWrite(dirPin1, HIGH); // motor direction cw

      for (int x = 0; x < steps1; x++) {
        digitalWrite(stepPin1, HIGH);
        delayMicroseconds(usDelay);
        digitalWrite(stepPin1, LOW);
        delayMicroseconds(usDelay);
      }

      digitalWrite(dirPin2, HIGH);

      for (int x = 0; x < steps2; x++) {
        digitalWrite(stepPin2, HIGH);
        delayMicroseconds(usDelay);
        digitalWrite(stepPin2, LOW);
        delayMicroseconds(usDelay);
      }

      digitalWrite(dirPin1, LOW);

      for (int x = 0; x < steps1; x++) {
        digitalWrite(stepPin1, HIGH);
        delayMicroseconds(usDelay);
        digitalWrite(stepPin1, LOW);
        delayMicroseconds(usDelay);
      }

      digitalWrite(dirPin2, LOW);

      for (int x = 0; x < steps2; x++) {
        digitalWrite(stepPin2, HIGH);
        delayMicroseconds(usDelay);
        digitalWrite(stepPin2, LOW);
        delayMicroseconds(usDelay);
      }
    }
  }
  digitalWrite(penna, LOW);
}
