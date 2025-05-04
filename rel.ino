const int dirPin1 = 2;
const int stepPin1 = 3;
const int dirPin2 = 13;
const int stepPin2 = 11;
const int ms1 = 8;
const int ms2 = 9;
const int ms3 = 10;

int rele = 6;

void setup() {
  pinMode(stepPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);
  pinMode(stepPin2, OUTPUT);
  pinMode(dirPin2, OUTPUT);
  pinMode(ms1, OUTPUT);
  pinMode(ms2, OUTPUT);
  pinMode(ms3, OUTPUT);

  pinMode(rele, OUTPUT);
}

void loop() {
  digitalWrite(stepPin1, LOW);
  digitalWrite(dirPin1, LOW);
  digitalWrite(stepPin2, LOW);
  digitalWrite(dirPin2, LOW);
  digitalWrite(ms1, LOW);
  digitalWrite(ms2, LOW);
  digitalWrite(ms3, LOW);

  digitalWrite(rele, LOW);
  delay(5000);
  digitalWrite(rele, HIGH);
  delay(5000);
}
