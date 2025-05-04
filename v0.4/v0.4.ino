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
  
  movimentox(8000);  //limuite foglio 9000
  movimentoy(3000);  //limite foglio 5000

  Serial.println();
  Serial.println("Inserisci la dimensione del testo tra 8 e 70:");
  while (!Serial) { ; }
  // Rimani bloccato qui finché non ricevi un numero valido
  while (true) {
    if (Serial.available() > 0) {
      String input = Serial.readStringUntil('\n');
      input.trim();  // Rimuove spazi e \r\n

      carattere = input.toInt();

      if (carattere >= 8 && carattere <= 70) {
        Serial.print("Numero valido ricevuto: ");
        Serial.println(carattere, 0);
        break;  // Esci dal ciclo e continua il programma
      } else {
        Serial.println("Carattere non valido. Riprova:");
      }
    }
  }

  velocitamotori(3);
 /* movimentox(8900);
  movimentoy(4600);
 
  movimentox(7000);
  movimentoy(4500);
  movimentox(6900);
  movimentoy(4400);

  movimentox(5000);
  movimentoy(4300);
  movimentox(4900);
  movimentoy(4200);

  movimentox(3000);
  movimentoy(4100);
  movimentox(2900);
  movimentoy(4000);

  movimentox(1000);
  movimentoy(3900);
  movimentox(900);
  movimentoy(3800);*/

  Serial.println("Inserisci una parola con lettere A-->Z o numeri nel formato x;y:");
}

void loop() {
  if (Serial.available()) {
    haLettere = false;

    String input = Serial.readStringUntil('\n');
    input.trim();

    int lunghezza = input.length();
    if (lunghezza > maxLunghezza) lunghezza = maxLunghezza;

    // Copia nel vettore
    for (int i = 0; i < lunghezza; i++) {
      caratteri[i] = input.charAt(i);
    }

    // Cicla ogni carattere e chiama la funzione corrispondente
    for (int i = 0; i < lunghezza; i++) {
      char c = caratteri[i];

      // Se il carattere è una lettera
      if (isAlpha(c)) {
        haLettere = true;
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
      }  else if (isdigit(c)) {  // Solo se inizia con una cifra
        String numeroStr = "";

        // Estrai numeri e punto e virgola
        while (i < lunghezza && (isdigit(caratteri[i]) || caratteri[i] == ';')) {
          numeroStr += caratteri[i];
          i++;
        }
        i--;  // Riporta indietro l'indice per il for principale

        int separatore = numeroStr.indexOf(';');
        if (separatore != -1) {
          String primoNumero = numeroStr.substring(0, separatore);
          String secondoNumero = numeroStr.substring(separatore + 1);

          primoNumero.trim();
          secondoNumero.trim();

          // Verifica che siano numeri validi positivi
          if (primoNumero.length() > 0 && secondoNumero.length() > 0 &&
              primoNumero.toInt() >= 0 && secondoNumero.toInt() >= 0) {

            int n = primoNumero.toInt();
            int m = secondoNumero.toInt();

            Serial.print("Primo numero (x): ");
            Serial.println(n);
            Serial.print("Secondo numero (y): ");
            Serial.println(m);

            movimentox(n);
            movimentoy(m);
            Serial.println("Fine movimento.\n");
          } else {
            Serial.println("Numeri non validi o negativi. Usa solo numeri positivi nel formato x;y\n");
          }
        } else {
          Serial.println("Formato numerico non valido. Usa il formato x;y\n");
        }

      } else {
        Serial.print("Carattere non riconosciuto: ");
        Serial.println(c);
      }
    }

    if (haLettere) {
      Serial.println("Fine frase.\n");
    }

    Serial.println("Inserisci una parola con lettere A-->Z o numeri nel formato x;y:");
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


void movimentox(int xobb) {  //movimento da (inserire valore) a (inserire valore)
  led("azzurro");
  if (xobb > x) {
    digitalWrite(dirPin1, HIGH);  // motor direction ccw
    for (int xparziale=0; xparziale < xobb ; xparziale++) {
      digitalWrite(stepPin1, HIGH);
      delayMicroseconds(usDelay);
      digitalWrite(stepPin1, LOW);
      delayMicroseconds(usDelay);
      
      if (digitalRead(fc1) > 1010) {
        led("giallo");
        delay(3000);
        break;
      }
    }
  } else if (xobb < x) {
    digitalWrite(dirPin1, LOW);  // motor direction ccw
    for (int xobb; xobb > x; xobb--) { //a 3000 coefficente 4.5
      digitalWrite(stepPin1, HIGH);
      delayMicroseconds(usDelay);
      digitalWrite(stepPin1, LOW);
      delayMicroseconds(usDelay);
      if (digitalRead(fc1) > 1010) {
        led("giallo");
        delay(3000);
        break;
      }
    }
  } else {
    delay(50);
  }
  x = xobb;
  Serial.print("la x e a");
  Serial.println(x);
}

void movimentoy(int yobb) {
  led("verde");
  if (yobb > y) {
    digitalWrite(dirPin2, LOW);  // motor direction ccw
    for (int yparziale=0; yparziale <= yobb; yparziale++) {
      digitalWrite(stepPin2, HIGH);
      delayMicroseconds(usDelay);
      digitalWrite(stepPin2, LOW);
      delayMicroseconds(usDelay);
      if (digitalRead(fc1) > 1018) {
        led("giallo");
        delay(3000);
        break;
      }
    }
  } else if (yobb < y) {
    digitalWrite(dirPin2, HIGH);  // direzione indietro
    for (int yparziale = 0; yparziale < (y - yobb); yparziale++) {
      digitalWrite(stepPin2, HIGH);
      delayMicroseconds(usDelay);
      digitalWrite(stepPin2, LOW);
      delayMicroseconds(usDelay);
      /*if (analogRead(fc1) > 1018) {
        led("giallo");
        delay(3000);
        break;
      }*/
    }
  } else {
    delay(100);
  }
  y = yobb;
  Serial.println(y);
}

void go_home() {
  led("viola");
  // Serial.println(analogRead(fc2));

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

void cerchio(int raggio) {
  delay(3000);
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
}

void A() {
  Serial.println("Hai chiamato la funzione A()");
  digitalWrite(penna, HIGH);
  delay(2000);
  digitalWrite(penna, LOW);
}

void B() {
  Serial.println("Hai chiamato la funzione B()");
  digitalWrite(penna, HIGH);
  delay(2000);
  digitalWrite(penna, LOW);
}

void C() {
  Serial.println("Hai chiamato la funzione C()");
  digitalWrite(penna, HIGH);
  delay(2000);
  digitalWrite(penna, LOW);
}

void D() {
  Serial.println("Hai chiamato la funzione D()");
  digitalWrite(penna, HIGH);
  delay(2000);
  digitalWrite(penna, LOW);
}

void E() {
  Serial.println("Hai chiamato la funzione E()");
  digitalWrite(penna, HIGH);
  delay(2000);
  digitalWrite(penna, LOW);
}

void EFFE() {
  Serial.println("Hai chiamato la funzione F()");
  digitalWrite(penna, HIGH);
  delay(2000);
  digitalWrite(penna, LOW);
}

void G() {
  Serial.println("Hai chiamato la funzione G()");
  digitalWrite(penna, HIGH);
  delay(2000);
  digitalWrite(penna, LOW);
}

void H() {
  Serial.println("Hai chiamato la funzione H()");
  digitalWrite(penna, HIGH);
  delay(2000);
  digitalWrite(penna, LOW);
}

void I() {
  Serial.println("Hai chiamato la funzione I()");
  digitalWrite(penna, HIGH);
  delay(2000);
  digitalWrite(penna, LOW);
}

void J() {
  Serial.println("Hai chiamato la funzione J()");
  digitalWrite(penna, HIGH);
  delay(2000);
  digitalWrite(penna, LOW);
}

void K() {
  Serial.println("Hai chiamato la funzione K()");
  digitalWrite(penna, HIGH);
  delay(2000);
  digitalWrite(penna, LOW);
}

void L() {
  Serial.println("Hai chiamato la funzione L()");
  digitalWrite(penna, HIGH);
  int xl = x - 1000;
  int yl = y - 800; 
  movimentoy(yl);
  movimentox(xl);
  digitalWrite(penna, LOW);
}

void M() {
  Serial.println("Hai chiamato la funzione M()");
  digitalWrite(penna, HIGH);
  delay(2000);
  digitalWrite(penna, LOW);
}

void N() {
  Serial.println("Hai chiamato la funzione N()");
  digitalWrite(penna, HIGH);
  delay(2000);
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
}

void P() {
  Serial.println("Hai chiamato la funzione P()");
  digitalWrite(penna, HIGH);
  delay(2000);
  digitalWrite(penna, LOW);
}

void Q() {
  Serial.println("Hai chiamato la funzione Q()");
  digitalWrite(penna, HIGH);
  delay(2000);
  digitalWrite(penna, LOW);
}

void R() {
  Serial.println("Hai chiamato la funzione R()");
  digitalWrite(penna, HIGH);
  delay(2000);
  digitalWrite(penna, LOW);
}

void S() {
  Serial.println("Hai chiamato la funzione S()");
  digitalWrite(penna, HIGH);
  delay(2000);
  digitalWrite(penna, LOW);
}

void T() {
  Serial.println("Hai chiamato la funzione T()");
  digitalWrite(penna, HIGH);
  delay(2000);
  digitalWrite(penna, LOW);
}

void U() {
  Serial.println("Hai chiamato la funzione U()");
  digitalWrite(penna, HIGH);
  delay(2000);
  digitalWrite(penna, LOW);
}

void V() {
  Serial.println("Hai chiamato la funzione V()");
  digitalWrite(penna, HIGH);
  delay(2000);
  digitalWrite(penna, LOW);
}

void W() {
  Serial.println("Hai chiamato la funzione W()");
  digitalWrite(penna, HIGH);
  delay(2000);
  digitalWrite(penna, LOW);
}

void X() {
  Serial.println("Hai chiamato la funzione X()");
  digitalWrite(penna, HIGH);
  delay(2000);
  digitalWrite(penna, LOW);
}

void Y() {
  Serial.println("Hai chiamato la funzione Y()");
  digitalWrite(penna, HIGH);
  delay(2000);
  digitalWrite(penna, LOW);
}

void Z() {
  Serial.println("Hai chiamato la funzione Z()");
  digitalWrite(penna, HIGH);
  int xzup = x + 20;
  int yzup = y + 20;
  int xzdown = x - 20;  //non va
  int yzdown = y - 20;

  movimentoy(yzdown);
  movimentox(xzup);
  movimentoy(yzup);
  movimentox(xzdown);


  digitalWrite(penna, LOW);
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