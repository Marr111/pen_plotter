int usDelay = 700;  // tempo tra step

const int dirPin1 = 2;
const int stepPin1 = 3;
const int dirPin2 = 13;
const int stepPin2 = 11;
const int ms1 = 8;
const int ms2 = 9;
const int ms3 = 10;
const int fc2 = A1;
const int fc1 = A0;

int steps = 0;
int x;
int y;
int xobb;
int yobb;
int i;

void setup() {
  pinMode(fc1, INPUT_PULLUP);
  pinMode(fc2, INPUT_PULLUP);
  pinMode(stepPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);
  pinMode(stepPin2, OUTPUT);
  pinMode(dirPin2, OUTPUT);
  Serial.begin(9600);
  pinMode(ms1, OUTPUT);
  pinMode(ms2, OUTPUT);
  pinMode(ms3, OUTPUT);
  digitalWrite(ms1, LOW);
  digitalWrite(ms2, HIGH);
  digitalWrite(ms3, LOW);

  Serial.println(analogRead(fc2));

  digitalWrite(dirPin1, LOW);   // senso antiorario
  digitalWrite(dirPin2, HIGH);  // senso antiorario
  x = 0;
  y = 0;
}

void loop() {
  movimentox(-500); // 90steps sono un millimetro
  movimentoy(-500);
}


void  movimentox(int xobb) {  //movimento da (inserire valore) a (inserire valore)
  if (xobb > x) {
    digitalWrite(dirPin1, HIGH);  // motor direction ccw
    for (int x;x < xobb; x++) {
      Serial.println(x);
      digitalWrite(stepPin1, HIGH);
      delayMicroseconds(usDelay);
      digitalWrite(stepPin1, LOW);
      delayMicroseconds(usDelay);
      if (digitalRead(fc1) == LOW) break;
    }
  } else if (xobb < x) {
    if (x - xobb < 0) {
      Serial.println("error");
return;
    }
    digitalWrite(dirPin1, LOW);  // motor direction ccw
    for (int x; x > xobb; x--) {
      digitalWrite(stepPin1, HIGH);
      delayMicroseconds(usDelay);
      digitalWrite(stepPin1, LOW);
      delayMicroseconds(usDelay);
      if (digitalRead(fc1) == LOW) break;
    }
  } else {
    delay(100);
  }
}

void movimentoy(int yobb) {
  if (yobb > y) {
    digitalWrite(dirPin2, LOW);  // motor direction ccw
    for (int y ; y <= yobb; y++) {
      Serial.println(y);
      digitalWrite(stepPin2, HIGH);
      delayMicroseconds(usDelay);
      digitalWrite(stepPin2, LOW);
      delayMicroseconds(usDelay);
      if (digitalRead(fc1) == LOW) 
      break;
    }
  } else if (yobb < y) {
    if (y - yobb < 0) {
      Serial.println("error");
      return;
    }
    digitalWrite(dirPin2, HIGH);  // motor direction ccw
    for (int y; y > yobb; y--) {
      Serial.println(y);
      digitalWrite(stepPin2, HIGH);
      delayMicroseconds(usDelay);
      digitalWrite(stepPin2, LOW);
      delayMicroseconds(usDelay);
      if (digitalRead(fc1) == LOW) break;
    }
  } else {
    delay(100);
  }
}