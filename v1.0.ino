//il foglio è 27.000 per 21.000
//uno millimetro sono 100 step

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

int pulsblu = A5;
int pulsgiallo = A4;
int pulsbianco = A3;
int pulsrosso = A2;

float carattere;
bool finecorsa1attivato;
bool finecorsa2attivato;
int i;
unsigned long int nparole;

const int maxLunghezza = 50;   // Lunghezza massima della stringa
char caratteri[maxLunghezza];  // Vettore per i caratteri

void setup() {
  led("arancione");
  Serial.begin(9600);
  pinMode(fc1, INPUT_PULLUP);
  pinMode(fc2, INPUT_PULLUP);
  pinMode(pulsblu, INPUT_PULLUP);
  pinMode(pulsgiallo, INPUT_PULLUP);
  pinMode(pulsbianco, INPUT_PULLUP);
  pinMode(pulsrosso, INPUT_PULLUP);
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
  Serial.println("pronto");
  velocitamotori(3);
}

void loop() {
  led("verde");
  /*Serial.print("il pulsante blu e a  ");
  Serial.println(analogRead(pulsblu));

 Serial.print("il pulsante rosso e a  ");
  Serial.println(analogRead(pulsrosso));

  Serial.print("il pulsante bianco e a  ");
  Serial.println(analogRead(pulsbianco));

   if (analogRead(pulsblu) < 1021) {  //blu
    delay(500);
    if (analogRead(pulsblu) < 1021) {
    led("rosso");
    alfabeto();}
  }

  if (analogRead(pulsrosso) < 1021) {  //rosso
    delay(1000);
    led("viola");
    go_home();
  }

  if (analogRead(pulsbianco) < 1021) {  //bianco
    delay(1000);
    led("viola");
    acapo();
  }*/

  letturaseriale();
  delay(1000);
}

void letturaseriale() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');

    int lunghezza = input.length();
    if (lunghezza > maxLunghezza) lunghezza = maxLunghezza;

    for (int i = 0; i < lunghezza; i++) {
      caratteri[i] = input.charAt(i);
    }

    for (int i = 0; i < lunghezza; i++) {
      if (nparole > 39000) {
        acapo();
      }
      char c = caratteri[i];

      if (isAlpha(c)) {
        nparole = nparole + 1500;
        Serial.print(nparole);
        c = toupper(c);
        switch (c) {
          case 'A': A(); break;
          case 'B': B(); break;
          case 'C': C(); break;
          case 'D': D(); break;
          case 'E': E(); break;
          case 'F': EFFE(); break;
          case 'G': G(); break;
          case 'H': H(); break;
          case 'I': I(); break;
          case 'J': J(); break;
          case 'K': K(); break;
          case 'L': L(); break;
          case 'M': M(); break;
          case 'N': N(); break;
          case 'O': O(); break;
          case 'P': P(); break;
          case 'Q': Q(); break;
          case 'R': R(); break;
          case 'S': S(); break;
          case 'T': T(); break;
          case 'U': U(); break;
          case 'V': V(); break;
          case 'W': W(); break;
          case 'X': X(); break;
          case 'Y': Y(); break;
          case 'Z': Z(); break;
          default:
            Serial.print("Carattere non valido: ");
            Serial.println(c);
            break;
        }
      } else if (isdigit(c)) {
        if (nparole > 39000) {
          acapo();
        }
        nparole = nparole + 2300;
        Serial.print(nparole);
        int cifra = c - '0';  // Converte il carattere in numero intero
        numero(cifra);
      } else if (c == ' ') {
        if (nparole > 39000) {
          acapo();
        }
        nparole = nparole + 1000;
        Serial.print(nparole);
        spazio();
      } else if (c == '|') {
        acapo();
      } else if (c == '-') {
        alfabeto();
      } else {
        Serial.print("Carattere non riconosciuto: ");
        Serial.println(c);
      }
    }

    Serial.println("Fine scrittura.\n");

    Serial.println("Inserisci una parola con lettere A-->Z o cifre 0-9:");
  }
}

void movimentoAlto(int obb) {
  digitalWrite(dirPin2, HIGH);  // Direzione alto
  for (int i = 0; i < obb; i++) {
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(usDelay);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(usDelay);
    if (analogRead(fc1) < 1018) {
      led("rosso");
      Serial.println("Finecorsa attivato errore");
      delay(3000);
      break;
    }
  }
}

void movimentoBasso(int obb) {
  digitalWrite(dirPin2, LOW);  // Direzione basso
  for (int i = 0; i < obb; i++) {
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(usDelay);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(usDelay);
    if (analogRead(fc1) < 1018) {
      Serial.println("Finecorsa attivato errore");
      led("rosso");
      delay(3000);
      break;
    }
  }
}

void movimentoDestra(int obb) {
  digitalWrite(dirPin1, HIGH);  // Direzione destra
  for (int i = 0; i < obb; i++) {
    digitalWrite(stepPin1, HIGH);
    delayMicroseconds(usDelay);
    digitalWrite(stepPin1, LOW);
    delayMicroseconds(usDelay);
    if (analogRead(fc1) < 1018) {
      Serial.println("Finecorsa attivato errore");
      led("rosso");
      delay(3000);
      break;
    }
  }
}

void movimentoSinistra(int obb) {
  digitalWrite(dirPin1, LOW);  // Direzione sinistra
  for (int i = 0; i < obb; i++) {
    digitalWrite(stepPin1, HIGH);
    delayMicroseconds(usDelay);
    digitalWrite(stepPin1, LOW);
    delayMicroseconds(usDelay);
    if (analogRead(fc1) < 1018) {
      Serial.println("Finecorsa attivato errore");
      led("rosso");
      delay(3000);
      break;
    }
  }
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

void go_home() {
  velocitamotori(1);
  led("arancione");
  digitalWrite(dirPin1, LOW);   // senso antiorario
  digitalWrite(dirPin2, HIGH);  // senso antiorario

  // Muove il motore fino a che il finecorsa NON è premuto
  while (analogRead(fc2) > 1020) {
    // Serial.println(analogRead(fc2));
    for (i = 0; i < 10; i++) {
      digitalWrite(stepPin2, HIGH);
      delayMicroseconds(usDelay);
      digitalWrite(stepPin2, LOW);
      delayMicroseconds(usDelay);
    }
  }

  Serial.println("Finecorsa y attivato, motore fermo");

  while (analogRead(fc1) > 1020) {
    // Serial.println(analogRead(fc1));
    for (i = 0; i < 10; i++) {
      digitalWrite(stepPin1, HIGH);
      delayMicroseconds(usDelay);
      digitalWrite(stepPin1, LOW);
      delayMicroseconds(usDelay);
    }
  }
  digitalWrite(dirPin2, LOW);
  digitalWrite(dirPin1, HIGH);
  Serial.println("Finecorsa x attivato, motore fermo");

  for (int i = 0; i < 100; i++) {  //piccolo spostamento per non leggere le fotocellule
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(usDelay);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(usDelay);
  }

  for (int i = 0; i < 100; i++) {
    digitalWrite(stepPin1, HIGH);
    delayMicroseconds(usDelay);
    digitalWrite(stepPin1, LOW);
    delayMicroseconds(usDelay);
  }
  movimentoBasso(4900);
  movimentoDestra(6800);
}

void numero(int cifra) {
  switch (cifra) {
    case 0: zero(); break;
    case 1: uno(); break;
    case 2: due(); break;
    case 3: tre(); break;
    case 4: quattro(); break;
    case 5: cinque(); break;
    case 6: seii(); break;
    case 7: sette(); break;
    case 8: otto(); break;
    case 9: nove(); break;
    default:
      Serial.print("Cifra non valida: ");
      Serial.println(cifra);
      break;
  }
}

void led(String colorName) {
  // Converto la stringa in minuscolo per standardizzare
  colorName.toLowerCase();

  // Valori RGB (per catodo comune: 0 = spento, 255 = acceso)
  int r = 0;
  int g = 0;
  int b = 0;

  if (colorName == "rosso") {
    r = 255;
    g = 0;
    b = 0;
  } else if (colorName == "verde") {
    r = 0;
    g = 255;
    b = 0;
  } else if (colorName == "blu") {
    r = 0;
    g = 0;
    b = 255;
  } else if (colorName == "giallo") {
    r = 255;
    g = 255;
    b = 0;
  } else if (colorName == "rosa") {
    r = 255;
    g = 0;
    b = 127;
  } else if (colorName == "azzurro") {
    r = 80;
    g = 216;
    b = 251;
  } else if (colorName == "viola") {
    r = 128;
    g = 0;
    b = 128;
  } else if (colorName == "arancione") {
    r = 243;
    g = 164;
    b = 5;
  } else {
    // Colore non riconosciuto → LED spento
    r = g = b = 0;
  }

  // Scrive i valori PWM invertiti per LED ad anodo comune
  analogWrite(RED_PIN, r);
  analogWrite(GREEN_PIN, g);
  analogWrite(BLUE_PIN, b);
  // Se il colore non è riconosciuto, il LED rimane spento (tutti i pin a 0)
}

void spazio() {
  Serial.println("Hai chiamato la funzione spazio()");
  digitalWrite(penna, LOW);
  movimentoSinistra(1300);
}

void acapo() {
  Serial.println(nparole);
  velocitamotori(1);
  float movimentoreset = nparole / 6.135;
  Serial.println(movimentoreset);
  movimentoDestra(movimentoreset);
  movimentoAlto(400);
  velocitamotori(3);
  nparole = 0;
}

void alfabeto() {
  Serial.println("Inizia la stampa di alfabeto e numeri");

  // Lettere maiuscole
  A();
  B();
  C();
  D();
  E();
  EFFE();
  G();
  H();
  I();
  J();
  K();
  L();
  M();
  N();
  O();
  P();
  Q();
  R();
  S();
  T();
  U();
  V();
  W();
  nparole = 40000;
  acapo();
  X();
  Y();
  Z();

  // Numeri
  zero();
  uno();
  due();
  tre();
  quattro();
  cinque();
  seii();
  sette();
  otto();
  nove();

  Serial.println("Completata la stampa di alfabeto e numeri");
}

void A() {
  Serial.println("Hai chiamato la funzione A()");
  movimentoAlto(2000);
  digitalWrite(penna, HIGH);

  movimentoBasso(2000);
  movimentoSinistra(1300);
  movimentoAlto(2000);
  movimentoBasso(1200);
  movimentoDestra(1300);

  digitalWrite(penna, LOW);
  movimentoBasso(800);
  movimentoSinistra(2000);
}

void B() {
  Serial.println("Hai chiamato la funzione B()");
  digitalWrite(penna, HIGH);

  movimentoSinistra(1000);
  for (int i = 0; i < 30; i++) {
    movimentoSinistra(10);
    movimentoAlto(10);
  }
  movimentoAlto(400);
  for (int i = 0; i < 30; i++) {
    movimentoDestra(10);
    movimentoAlto(10);
  }
  movimentoDestra(1000);
  movimentoSinistra(1000);
  for (int i = 0; i < 30; i++) {
    movimentoSinistra(10);
    movimentoAlto(10);
  }
  movimentoAlto(400);
  for (int i = 0; i < 30; i++) {
    movimentoDestra(10);
    movimentoAlto(10);
  }
  movimentoDestra(1000);
  movimentoBasso(2000);

  digitalWrite(penna, LOW);
  movimentoSinistra(2300);
}

void C() {
  Serial.println("Hai chiamato la funzione C()");
  movimentoAlto(2000);
  movimentoSinistra(1300);
  digitalWrite(penna, HIGH);

  movimentoDestra(1300);
  movimentoBasso(2000);
  movimentoSinistra(1300);

  digitalWrite(penna, LOW);
  movimentoSinistra(700);
}

void D() {
  Serial.println("Hai chiamato la funzione D()");
  digitalWrite(penna, HIGH);

  movimentoSinistra(700);
  for (int i = 0; i < 50; i++) {
    movimentoSinistra(15);
    movimentoAlto(10);
  }
  movimentoAlto(1000);
  for (int i = 0; i < 50; i++) {
    movimentoDestra(15);
    movimentoAlto(10);
  }
  movimentoDestra(700);
  movimentoBasso(2000);

  digitalWrite(penna, LOW);
  movimentoSinistra(2300);

  digitalWrite(penna, LOW);
}

void E() {
  Serial.println("Hai chiamato la funzione E()");
  movimentoSinistra(1300);
  digitalWrite(penna, HIGH);

  movimentoDestra(1300);
  movimentoAlto(1000);
  movimentoSinistra(700);
  movimentoDestra(700);
  movimentoAlto(1000);
  movimentoSinistra(1300);

  digitalWrite(penna, LOW);
  movimentoBasso(2000);
  movimentoSinistra(1300);
}

void EFFE() {
  Serial.println("Hai chiamato la funzione F()");
  movimentoSinistra(1300);
  digitalWrite(penna, HIGH);

  movimentoDestra(1300);
  movimentoAlto(2000);
  movimentoBasso(1000);
  movimentoSinistra(1000);

  digitalWrite(penna, LOW);
  movimentoSinistra(1000);
  movimentoBasso(1000);
}

void G() {
  Serial.println("Hai chiamato la funzione G()");
  movimentoSinistra(1300);
  digitalWrite(penna, HIGH);

  movimentoDestra(1300);
  movimentoAlto(2000);
  movimentoSinistra(1300);
  movimentoBasso(700);
  movimentoDestra(600);
  movimentoSinistra(1200);
  movimentoDestra(600);

  digitalWrite(penna, LOW);
  movimentoBasso(1300);
  movimentoSinistra(1000);
}

void H() {
  Serial.println("Hai chiamato la funzione H()");
  digitalWrite(penna, HIGH);

  movimentoAlto(2000);
  movimentoBasso(1000);
  movimentoSinistra(1300);
  movimentoBasso(1000);
  movimentoAlto(2000);

  digitalWrite(penna, LOW);
  movimentoBasso(2000);
  movimentoSinistra(1300);
}

void I() {
  Serial.println("Hai chiamato la funzione I()");
  digitalWrite(penna, HIGH);

  movimentoAlto(200);
  digitalWrite(penna, LOW);
  movimentoAlto(300);
  digitalWrite(penna, HIGH);
  movimentoAlto(1500);

  digitalWrite(penna, LOW);
  movimentoBasso(2000);
  movimentoSinistra(1000);
}

void J() {
  Serial.println("Hai chiamato la funzione J()");
  digitalWrite(penna, HIGH);
  movimentoSinistra(1300);
  movimentoDestra(650);
  movimentoAlto(1650);
  for (int i = 0; i < 30; i++) {
    movimentoDestra(10);
    movimentoAlto(10);
  }
  movimentoDestra(650);

  digitalWrite(penna, LOW);
  movimentoBasso(2000);
  movimentoSinistra(2500);
}

void K() {
  Serial.println("Hai chiamato la funzione K()");
  digitalWrite(penna, HIGH);

  movimentoAlto(1000);
  for (int i = 0; i < 100; i++) {
    movimentoBasso(10);
    movimentoSinistra(13);
  }
  for (int i = 0; i < 100; i++) {
    movimentoDestra(13);
    movimentoAlto(10);
  }
  for (int i = 0; i < 100; i++) {
    movimentoAlto(10);
    movimentoSinistra(13);
  }
  for (int i = 0; i < 100; i++) {
    movimentoDestra(13);
    movimentoBasso(10);
  }
  movimentoAlto(1000);

  digitalWrite(penna, LOW);
  movimentoBasso(2000);
  movimentoSinistra(2300);
}

void L() {
  Serial.println("Hai chiamato la funzione L()");
  digitalWrite(penna, HIGH);

  movimentoAlto(2000);
  movimentoSinistra(1300);

  digitalWrite(penna, LOW);
  movimentoSinistra(1000);
  movimentoBasso(2000);
}

void M() {
  Serial.println("Hai chiamato la funzione M()");
  movimentoAlto(2000);
  digitalWrite(penna, HIGH);

  movimentoBasso(2000);
  for (int i = 0; i < 50; i++) {
    movimentoSinistra(14);
    movimentoAlto(13);
  }
  for (int i = 0; i < 50; i++) {
    movimentoSinistra(14);
    movimentoBasso(13);
  }
  movimentoAlto(2000);

  digitalWrite(penna, LOW);
  movimentoSinistra(1000);
  movimentoBasso(2000);
}

void N() {
  Serial.println("Hai chiamato la funzione N()");
  movimentoAlto(2000);
  digitalWrite(penna, HIGH);

  movimentoBasso(2000);
  for (int i = 0; i < 80; i++) {
    movimentoSinistra(15);
    movimentoAlto(25);
  }
  movimentoBasso(2000);

  digitalWrite(penna, LOW);
  movimentoSinistra(1000);
}

void O() {
  Serial.println("Hai chiamato la funzione O()");
  digitalWrite(penna, HIGH);

  movimentoSinistra(1300);
  movimentoAlto(2000);
  movimentoDestra(1300);
  movimentoBasso(2000);

  digitalWrite(penna, LOW);
  movimentoSinistra(2000);
}

void P() {
  Serial.println("Hai chiamato la funzione P()");
  digitalWrite(penna, HIGH);

  movimentoSinistra(1300);
  movimentoAlto(900);
  movimentoDestra(1300);
  movimentoBasso(900);
  movimentoAlto(2000);

  digitalWrite(penna, LOW);
  movimentoBasso(2000);
  movimentoSinistra(2300);
}

void Q() {
  Serial.println("Hai chiamato la funzione Q()");
  digitalWrite(penna, HIGH);

  movimentoSinistra(1300);
  movimentoAlto(2000);
  movimentoDestra(1300);
  movimentoBasso(2000);
  digitalWrite(penna, LOW);
  movimentoSinistra(800);
  movimentoAlto(1400);
  digitalWrite(penna, HIGH);
  for (int i = 0; i < 80; i++) {
    movimentoSinistra(10);
    movimentoAlto(10);
  }

  digitalWrite(penna, LOW);
  movimentoBasso(2200);
  movimentoSinistra(500);
}

void R() {
  Serial.println("Hai chiamato la funzione R()");
  digitalWrite(penna, HIGH);

  movimentoSinistra(1300);
  movimentoAlto(900);
  movimentoDestra(1300);
  movimentoBasso(900);
  movimentoAlto(2000);
  movimentoBasso(1100);
  for (int i = 0; i < 105; i++) {
    movimentoSinistra(13);
    movimentoAlto(10);
  }

  digitalWrite(penna, LOW);
  movimentoBasso(2000);
  movimentoSinistra(700);
}

void S() {
  Serial.println("Hai chiamato la funzione S()");
  movimentoSinistra(2000);
  digitalWrite(penna, HIGH);

  movimentoDestra(1000);
  for (int i = 0; i < 30; i++) {
    movimentoDestra(20);
    movimentoAlto(10);
  }
  movimentoAlto(400);
  for (int i = 0; i < 30; i++) {
    movimentoSinistra(10);
    movimentoAlto(10);
  }
  movimentoSinistra(1000);
  for (int i = 0; i < 30; i++) {
    movimentoSinistra(10);
    movimentoAlto(10);
  }
  movimentoAlto(400);
  for (int i = 0; i < 20; i++) {
    movimentoDestra(20);
    movimentoAlto(10);
  }
  movimentoDestra(1000);

  digitalWrite(penna, LOW);

  movimentoSinistra(2000);
  movimentoBasso(2000);
}

void T() {
  Serial.println("Hai chiamato la funzione T()");
  digitalWrite(penna, HIGH);

  movimentoSinistra(1300);
  movimentoDestra(650);
  movimentoAlto(2000);

  digitalWrite(penna, LOW);
  movimentoBasso(2000);
  movimentoSinistra(650);
  movimentoSinistra(1000);
}

void U() {
  Serial.println("Hai chiamato la funzione U()");
  digitalWrite(penna, HIGH);

  movimentoAlto(2000);
  movimentoSinistra(1300);
  movimentoBasso(2000);

  digitalWrite(penna, LOW);
  movimentoSinistra(1000);
}

void V() {
  Serial.println("Hai chiamato la funzione V()");
  digitalWrite(penna, HIGH);

  for (int i = 0; i < 80; i++) {
    movimentoSinistra(10);
    movimentoAlto(25);
  }
  for (int i = 0; i < 80; i++) {
    movimentoSinistra(10);
    movimentoBasso(25);
  }

  digitalWrite(penna, LOW);
  movimentoSinistra(1000);
}

void W() {
  Serial.println("Hai chiamato la funzione W()");
  digitalWrite(penna, HIGH);

  for (int i = 0; i < 50; i++) {
    movimentoSinistra(10);
    movimentoAlto(40);
  }
  for (int i = 0; i < 50; i++) {
    movimentoSinistra(7);
    movimentoBasso(13);
  }

  for (int i = 0; i < 50; i++) {
    movimentoSinistra(7);
    movimentoAlto(13);
  }

  for (int i = 0; i < 50; i++) {
    movimentoSinistra(10);
    movimentoBasso(40);
  }


  digitalWrite(penna, LOW);
  movimentoSinistra(1000);
}

void X() {
  Serial.println("Hai chiamato la funzione X()");
  digitalWrite(penna, HIGH);

  for (int i = 0; i < 80; i++) {
    movimentoSinistra(15);
    movimentoAlto(25);
  }
  digitalWrite(penna, LOW);
  movimentoDestra(1300);
  digitalWrite(penna, HIGH);
  for (int i = 0; i < 80; i++) {
    movimentoSinistra(15);
    movimentoBasso(25);
  }

  digitalWrite(penna, LOW);
  movimentoSinistra(1000);
}

void Y() {
  Serial.println("Hai chiamato la funzione Y()");
  digitalWrite(penna, HIGH);

  for (int i = 0; i < 50; i++) {
    movimentoSinistra(15);
    movimentoAlto(13);
  }
  movimentoAlto(1400);
  movimentoBasso(1400);
  for (int i = 0; i < 50; i++) {
    movimentoSinistra(15);
    movimentoBasso(13);
  }

  digitalWrite(penna, LOW);
  movimentoSinistra(1000);
}

void Z() {
  Serial.println("Hai chiamato la funzione Z()");
  digitalWrite(penna, HIGH);

  movimentoSinistra(1300);
  for (int i = 0; i < 130; i++) {
    movimentoDestra(10);
    movimentoAlto(15);
  }
  movimentoSinistra(1300);

  digitalWrite(penna, LOW);
  movimentoSinistra(1000);
  movimentoBasso(2000);
}

void zero() {
  Serial.println("Hai chiamato la funzione zero()");
  digitalWrite(penna, HIGH);

  movimentoSinistra(1300);
  movimentoAlto(2000);
  movimentoDestra(1300);
  movimentoBasso(2000);
  for (int i = 0; i < 100; i++) {
    movimentoSinistra(13);
    movimentoAlto(20);
  }

  digitalWrite(penna, LOW);
  movimentoSinistra(700);
  movimentoBasso(2000);
}

void uno() {
  Serial.println("Hai chiamato la funzione uno()");
  movimentoSinistra(300);
  movimentoAlto(2000);
  digitalWrite(penna, HIGH);

  movimentoBasso(2000);
  for (int i = 0; i < 50; i++) {
    movimentoDestra(10);
    movimentoAlto(10);
  }

  digitalWrite(penna, LOW);
  movimentoSinistra(1300);
  movimentoBasso(500);
}

void due() {
  Serial.println("Hai chiamato la funzione due()");
  digitalWrite(penna, HIGH);

  movimentoSinistra(1000);
  for (int i = 0; i < 30; i++) {
    movimentoSinistra(10);
    movimentoAlto(10);
  }
  movimentoAlto(400);
  for (int i = 0; i < 92; i++) {
    movimentoDestra(13);
    movimentoAlto(15);
  }
  movimentoSinistra(1300);

  digitalWrite(penna, LOW);
  movimentoBasso(2000);
  movimentoSinistra(1000);
}

void tre() {
  Serial.println("Hai chiamato la funzione tre()");
  digitalWrite(penna, HIGH);

  movimentoSinistra(1300);
  movimentoAlto(1000);
  movimentoDestra(700);
  movimentoSinistra(700);
  movimentoAlto(1000);
  movimentoDestra(1300);

  digitalWrite(penna, LOW);
  movimentoBasso(2000);
  movimentoSinistra(2300);
}

void quattro() {
  Serial.println("Hai chiamato la funzione quattro()");
  digitalWrite(penna, HIGH);

  movimentoAlto(1500);
  movimentoSinistra(1300);
  movimentoDestra(600);
  movimentoAlto(700);
  movimentoBasso(1400);

  digitalWrite(penna, LOW);
  movimentoSinistra(600);
  movimentoBasso(700);
}

void cinque() {
  Serial.println("Hai chiamato la funzione cinque()");
  movimentoSinistra(2000);
  digitalWrite(penna, HIGH);

  movimentoDestra(1500);
  movimentoAlto(1000);
  movimentoSinistra(1200);
  for (int i = 0; i < 30; i++) {
    movimentoSinistra(10);
    movimentoAlto(10);
  }
  movimentoAlto(400);
  for (int i = 0; i < 20; i++) {
    movimentoDestra(20);
    movimentoAlto(10);
  }
  movimentoDestra(1000);

  digitalWrite(penna, LOW);

  movimentoSinistra(2000);
  movimentoBasso(2000);
}

void seii() {  // Rinominato da seii a sei per coerenza
  Serial.println("Hai chiamato la funzione sei()");
  digitalWrite(penna, HIGH);

  movimentoSinistra(1300);
  movimentoDestra(1300);
  movimentoAlto(2000);
  movimentoSinistra(1300);
  movimentoBasso(1000);
  movimentoDestra(1300);

  digitalWrite(penna, LOW);
  movimentoSinistra(2300);
  movimentoBasso(1000);
}

void sette() {
  Serial.println("Hai chiamato la funzione sette()");
  digitalWrite(penna, HIGH);

  movimentoSinistra(1300);
  for (int i = 0; i < 135; i++) {
    movimentoDestra(10);
    movimentoAlto(15);
  }
  digitalWrite(penna, LOW);
  movimentoBasso(1100);
  movimentoSinistra(1000);
  digitalWrite(penna, HIGH);
  movimentoDestra(800);

  digitalWrite(penna, LOW);
  movimentoSinistra(1700);
  movimentoBasso(900);
}

void otto() {
  Serial.println("Hai chiamato la funzione otto()");
  digitalWrite(penna, HIGH);

  movimentoSinistra(1300);
  movimentoAlto(2000);
  movimentoDestra(1300);
  movimentoBasso(1000);
  movimentoSinistra(1300);
  movimentoDestra(1300);
  movimentoBasso(1000);

  digitalWrite(penna, LOW);
  movimentoSinistra(2000);
}

void nove() {
  Serial.println("Hai chiamato la funzione nove()");
  digitalWrite(penna, HIGH);

  movimentoSinistra(1300);
  movimentoAlto(1000);
  movimentoDestra(1300);
  movimentoBasso(1000);
  movimentoSinistra(1300);
  movimentoAlto(2000);
  movimentoDestra(1300);

  digitalWrite(penna, LOW);
  movimentoSinistra(2000);
  movimentoBasso(2000);
}