//il foglio è 27.000 per 21.000
//uno millimetro sono 100 step
#include <math.h>

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
int penna = 6;

const int RED_PIN = 4;    // Pin rosso
const int GREEN_PIN = 7;  // Pin verde
const int BLUE_PIN = 5;   // Pin blu

int x;
int y;
int xobb;
int yobb;
int xparziale;
int yparziale;

float carattere;
bool haLettere = false;
int raggio;
int cm;
int i;
int alfa;

const int maxLunghezza = 50;   // Lunghezza massima della stringa
char caratteri[maxLunghezza];  // Vettore per i caratteri

void setup() {
  Serial.begin(9600);
  pinMode(fc1, INPUT_PULLUP);
  pinMode(fc2, INPUT_PULLUP);
  pinMode(stepPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);
  pinMode(stepPin2, OUTPUT);
  pinMode(dirPin2, OUTPUT);
  pinMode(ms1, OUTPUT);
  pinMode(ms2, OUTPUT);
  pinMode(ms3, OUTPUT);
  pinMode(penna, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  digitalWrite(ms1, LOW);
  digitalWrite(ms2, HIGH);
  digitalWrite(ms3, LOW);
  digitalWrite(penna, LOW);
  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, LOW);

  velocitamotori(1);
  go_home();

  movimentox(7000);          //limuite foglio 9000
  movimentoy(4600, "alto");  //limite foglio 4800
  velocitamotori(3);
  raggio = 4000;
  A();
}

void loop() {
}

void velocitamotori(int velocita) {
  switch (velocita) {
    case 1:  //full step
      digitalWrite(ms1, LOW);
      digitalWrite(ms2, LOW);
      digitalWrite(ms3, LOW);
      //  velocita = 1;
      Serial.println("Modalità: Full Step (1)");
      break;
    case 2:  //HALF_STEP
      digitalWrite(ms1, HIGH);
      digitalWrite(ms2, LOW);
      digitalWrite(ms3, LOW);
      //  velocita = 2;
      Serial.println("Modalità: Half Step (1/2)");
      break;
    case 3:  //QUARTER_STEP
      digitalWrite(ms1, HIGH);
      digitalWrite(ms2, HIGH);
      digitalWrite(ms3, LOW);
      //  velocita = 4;
      Serial.println("Modalità: Quarter Step (1/4)");
      break;
    case 4:  //EIGHTH_STEP
      digitalWrite(ms1, HIGH);
      digitalWrite(ms2, HIGH);
      digitalWrite(ms3, LOW);
      // velocita = 8;
      Serial.println("Modalità: Eighth Step (1/8)");
      break;
    case 5:  //SIXTEENTH_STEP
      digitalWrite(ms1, HIGH);
      digitalWrite(ms2, HIGH);
      digitalWrite(ms3, HIGH);
      //  velocita = 16;
      Serial.println("Modalità: Sixteenth Step (1/16)");
      break;
    default:
      // Default a full step se valore non valido
      digitalWrite(ms1, LOW);
      digitalWrite(ms2, LOW);
      digitalWrite(ms3, LOW);
      // velocita = 1;
      Serial.println("Modalità: Full Step (default)");
  }
}

void movimento(int yobb, int direzione) {  //movimento da posizione attuale a yobb
  if (direzione == "alto") {
    digitalWrite(dirPin2, LOW);  // direzione avanti
for (int i = 0; i < yobb; i++) {  // Conta solo i passi di differenza
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(usDelay);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(usDelay);
    if (digitalRead(fc1) > 1018) {
      delay(3000);
      break;
    }
}
  } else if (direzione == "basso") {
    digitalWrite(dirPin2, HIGH);  // direzione avanti
    for (int i = 0; i < yobb; i++) {  // Conta solo i passi di differenza
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(usDelay);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(usDelay);
    if (digitalRead(fc1) > 1018) {
      delay(3000);
      break;
    }
  }
  }else if (direzione == "destra") {
    digitalWrite(dirPin2, LOW);  // direzione avanti
    for (int i = 0; i < yobb; i++) {  // Conta solo i passi di differenza
    digitalWrite(stepPin1, HIGH);
    delayMicroseconds(usDelay);
    digitalWrite(stepPin1, LOW);
    delayMicroseconds(usDelay);
    if (digitalRead(fc1) > 1018) {
      delay(3000);
      break;
    }
    }
  } else if (direzione == "sinistra") {
    digitalWrite(dirPin2, HIGH);  // direzione avanti
    for (int i = 0; i < yobb; i++) {  // Conta solo i passi di differenza
    digitalWrite(stepPin1, HIGH);
    delayMicroseconds(usDelay);
    digitalWrite(stepPin1, LOW);
    delayMicroseconds(usDelay);
    if (digitalRead(fc1) > 1018) {
      delay(3000);
      break;
    }
  }
  }
  y = yobb;  // Aggiorna la posizione attuale
  Serial.print("la y e a ");
  Serial.println(y);
}

void go_home() {
  digitalWrite(dirPin1, LOW);   // senso antiorario
  digitalWrite(dirPin2, HIGH);  // senso antiorario

  // Muove il motore fino a che il finecorsa NON è premuto
  while (analogRead(fc2) > 1018) {
    //  Serial.println(analogRead(fc2));
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

void A() {
  Serial.println("Hai chiamato la funzione A()");
  digitalWrite(penna, HIGH);
  movimentoy(3000, "alto");
  delay(1000);
  movimentox(2000);
  delay(1000);
  movimentoy(3000, "basso");
  delay(1000);
  movimentoy(2000, "alto");
  delay(1000);
  movimentox(2000);
  delay(1000);
  digitalWrite(penna, LOW);
}

/*void L() {
  Serial.println("Hai chiamato la funzione L()");
  digitalWrite(penna, HIGH);
  int yl = y - 3000;
  int xl = x - 2000;
  movimentoy(yl);
  movimentox(xl);
  digitalWrite(penna, LOW);
}

void O() {
  Serial.println("Hai chiamato la funzione O()");
  digitalWrite(penna, HIGH);
  int step = raggio / 6;
   movimentox(2 * step);  // semicerchio superiore
  movimentoy(step);
  movimentox(2 * step);
  movimentoy(step);
  movimentox(step);
  movimentoy(2 * step);
  movimentox(step);
  movimentoy(4 * step);
  movimentox(-step / 2);
  movimentoy(2 * step);
  movimentox(-step / 2);
  movimentoy(step);
  movimentox(-2 * step / 2);
  movimentoy(step);
  movimentox(-4 * step / 2);  // semicerchio negativo
  movimentoy(-step / 10);
  movimentox(-step);
  movimentoy(-step / 7);
  movimentox(-step / 2);
  movimentoy(-step / 7);
  movimentox(-step / 2);
  movimentoy(-2 * step);
  movimentox(step / 7);

  movimentox(2 * step);  // semicerchio superiore
  movimentoy(step);
  movimentox(2 * step);
  movimentoy(step);
  movimentox(step);
  movimentoy(2 * step);
  movimentox(step);
  movimentoy(4 * step);
  movimentox(-step / 2);
  movimentoy(2 * step);
  movimentox(-step / 2);
  movimentoy(step);
  movimentox(-step);
  movimentoy(step);
  movimentox(-2 * step);  // semicerchio inferiore
  movimentoy(-step / 1.75);
  movimentox(-step);
  movimentoy(-step / 1.75);
  movimentox(-step / 2);
  movimentoy(-step / 1.75);
  movimentox(-step / 2);
  movimentoy(-4 * step / 3);
  movimentox(step);
  movimentoy(-2 * step / 1.75);
  movimentox(step);
  movimentoy(-step / 1.75);
  movimentox(2 * step);
  movimentoy(-step / 1.75);
  movimentox(2 * step);
  digitalWrite(penna, LOW);
}*/