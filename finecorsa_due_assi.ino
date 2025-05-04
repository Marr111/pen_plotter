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

  // Muove il motore fino a che il finecorsa NON è premuto
  while (analogRead(fc2) > 1018) {
    Serial.println(analogRead(fc2));
    for (i = 0; i < 10; i++) {
      digitalWrite(stepPin2, HIGH);
      delayMicroseconds(usDelay);
      digitalWrite(stepPin2, LOW);
      delayMicroseconds(usDelay);
    }
  }
  Serial.println("Finecorsa y attivato, motore fermo");

  while (analogRead(fc1) > 1018) {
    //  Serial.println(analogRead(fc1));
    for (i = 0; i < 10; i++) {
      digitalWrite(stepPin1, HIGH);
      delayMicroseconds(usDelay);
      digitalWrite(stepPin1, LOW);
      delayMicroseconds(usDelay);
    }
  }
  Serial.println("Finecorsa x attivato, motore fermo");

  x = 0;
  y = 0;
}

void loop() {
 movimentox(5000);
 movimentoy(5000);

  // for (i = 0; i < 1000; i++) {
  //  digitalWrite(stepPin1, HIGH);
  // delayMicroseconds(usDelay);
  // digitalWrite(stepPin1, LOW);
  // delayMicroseconds(usDelay);
  //  }
}


void movimentox(int xobb) {  //movimento da (inserire valore) a (inserire valore)
  encoder((xobb - x), 0);

  if (xobb > x) {
    digitalWrite(dirPin1, LOW);  // motor direction ccw
    for (int i = 0; i < (xobb - x); i++) {
      digitalWrite(stepPin1, HIGH);
      delayMicroseconds(usDelay);
      digitalWrite(stepPin1, LOW);
      delayMicroseconds(usDelay);
    }
  } else if (xobb < x) {
    digitalWrite(dirPin1, LOW);  // motor direction ccw
    for (int i = 0; i < (x - xobb); i++) {
      digitalWrite(stepPin1, HIGH);
      delayMicroseconds(usDelay);
      digitalWrite(stepPin1, LOW);
      delayMicroseconds(usDelay);
    }
  } else {
    delay(100);
  }
}

void movimentoy(int yobb) {
  encoder(0,(yobb - y));

  if (yobb > y) {
    digitalWrite(dirPin2, HIGH);  // motor direction ccw
    for (int i = 0; i < (yobb - y); i++) {
      digitalWrite(stepPin2, HIGH);
      delayMicroseconds(usDelay);
      digitalWrite(stepPin2, LOW);
      delayMicroseconds(usDelay);
    }
  } else if (yobb < y) {
    digitalWrite(dirPin2, LOW);  // motor direction ccw
    for (int i = 0; i < (y - yobb); i++) {
      digitalWrite(stepPin2, HIGH);
      delayMicroseconds(usDelay);
      digitalWrite(stepPin2, LOW);
      delayMicroseconds(usDelay);
    }
  } else {
    delay(100);
  }
}

void encoder(int differenzax, int differenzay) {
  x = x + differenzax;
  y = y + differenzay;
}