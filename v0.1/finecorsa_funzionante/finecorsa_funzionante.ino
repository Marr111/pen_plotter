// 

int usDelay = 700;  // tempo tra step

const int dirPin1 = 2;
const int stepPin1 = 3;
const int ms1 = 8;
const int ms2 = 9;
const int ms3 = 10;
const int fc1 = A1;

int i;
void setup() {
  pinMode(fc1, INPUT_PULLUP);
  pinMode(stepPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);
  Serial.begin(9600);
  pinMode(ms1, OUTPUT);
  pinMode(ms2, OUTPUT);
  pinMode(ms3, OUTPUT);
  digitalWrite(ms1, LOW);
  digitalWrite(ms2, HIGH);
  digitalWrite(ms3, LOW);

  Serial.println(analogRead(fc1));

    digitalWrite(dirPin1, HIGH);  // senso antiorario

  // Muove il motore fino a che il finecorsa NON è premuto
  while (analogRead(fc1) >1018) {
      Serial.println(analogRead(fc1));
    for (i = 0; i < 10; i++) {
    digitalWrite(stepPin1, HIGH);
    delayMicroseconds(usDelay);
    digitalWrite(stepPin1, LOW);
    delayMicroseconds(usDelay);
      }
  }

   Serial.println("Finecorsa attivato, motore fermo");
}

void loop() {
  digitalWrite(dirPin1, HIGH);  // senso antiorario

 // for (i = 0; i < 1000; i++) {
  //  digitalWrite(stepPin1, HIGH);
   // delayMicroseconds(usDelay);
   // digitalWrite(stepPin1, LOW);
   // delayMicroseconds(usDelay);
//  }
}
