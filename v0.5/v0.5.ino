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

//const float PI = 3.14159265;

int x;
int y;
int xobb;
int yobb;

float carattere;
bool haLettere = false;
int cm;
int i;
int alfa;

const int maxLunghezza = 50;   // Lunghezza massima della stringa
char caratteri[maxLunghezza];  // Vettore per i caratteri

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

  // curva(1000, 1);
  // diagonale(1000, 1000);
  //go_home();
  movimentox(1500);
  movimentoy(1500);

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

  Serial.println("Inserisci una parola con lettere A-->Z o numeri nel formato x;y:");
}
void loop() {
  /*
  if (analogRead(A5) > 1018) {
    go_home();
  }
  */

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
          case 'A': A(carattere); break;
          case 'B': B(carattere); break;
          case 'C': C(carattere); break;
          case 'D': D(carattere); break;
          case 'E': E(carattere); break;
          case 'F': EFFE(carattere); break;
          case 'G': G(carattere); break;
          case 'H': H(carattere); break;
          case 'I': I(carattere); break;
          case 'J': J(carattere); break;
          case 'K': K(carattere); break;
          case 'L': L(carattere); break;
          case 'M': M(carattere); break;
          case 'N': N(carattere); break;
          case 'O': O(carattere); break;
          case 'Q': Q(carattere); break;
          case 'R': R(carattere); break;
          case 'S': S(carattere); break;
          case 'T': T(carattere); break;
          case 'U': U(carattere); break;
          case 'V': V(carattere); break;
          case 'W': W(carattere); break;
          case 'X': X(carattere); break;
          case 'Y': Y(carattere); break;
          case 'Z': Z(carattere); break;
          default:
            Serial.print("Carattere non valido: ");
            Serial.println(c);
            break;
        }
      } else if (isdigit(c) || c == ';' || c == '-') {
        // Leggi l'intero numero
        String numeroStr = "";
        int startIndex = i;

        while (i < lunghezza && (isdigit(caratteri[i]) || caratteri[i] == ';' || caratteri[i] == '-')) {
          numeroStr += caratteri[i];
          i++;
        }
        i--;  // Corregge l'indice

        Serial.print("Stringa numerica completa: ");
        Serial.println(numeroStr);

        // Cerca il separatore
        int separatore = numeroStr.indexOf(';');
        if (separatore != -1) {
          String primoNumero = numeroStr.substring(0, separatore);
          String secondoNumero = numeroStr.substring(separatore + 1);

          // Rimuovi solo spazi, non altri caratteri
          while (primoNumero.length() > 0 && primoNumero.charAt(0) == ' ')
            primoNumero.remove(0, 1);
          while (primoNumero.length() > 0 && primoNumero.charAt(primoNumero.length() - 1) == ' ')
            primoNumero.remove(primoNumero.length() - 1, 1);

          while (secondoNumero.length() > 0 && secondoNumero.charAt(0) == ' ')
            secondoNumero.remove(0, 1);
          while (secondoNumero.length() > 0 && secondoNumero.charAt(secondoNumero.length() - 1) == ' ')
            secondoNumero.remove(secondoNumero.length() - 1, 1);

          Serial.print("Primo numero (stringa): '");
          Serial.print(primoNumero);
          Serial.println("'");

          Serial.print("Secondo numero (stringa): '");
          Serial.print(secondoNumero);
          Serial.println("'");

          // Conversione in int con controllo
          int n = primoNumero.toInt();
          int m = secondoNumero.toInt();

          Serial.print("Primo numero (int): ");
          Serial.println(n);
          Serial.print("Secondo numero (int): ");
          Serial.println(m);

          // Esegui il movimento
          Serial.println("Tentativo di movimento...");
          movimentox(n);
          movimentoy(m);
          Serial.println("Fine movimento.");
        } else {
          Serial.println("Formato numerico non valido. Usa il formato x;y");
        }
      }
    }else {
      Serial.print("Carattere non riconosciuto: \n");
      Serial.println(c);
    }
  }
  if (haLettere) {
    Serial.println("Fine frase.\n");
  }
  Serial.println("Inserisci una parola con lettere A-->Z o numeri nel formato x;y:");
}

void movimentox(int xobb) {  //movimento da (inserire valore) a (inserire valore)
  if (xobb > x) {
    digitalWrite(dirPin1, HIGH);  // motor direction ccw
    for (int x; x < xobb; x++) {
      //  Serial.println(x);
      digitalWrite(stepPin1, HIGH);
      delayMicroseconds(usDelay);
      digitalWrite(stepPin1, LOW);
      delayMicroseconds(usDelay);
      if (analogRead(fc1) < 1018) break;
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
      if (analogRead(fc1) < 1018) break;
    }
  } else {
    delay(100);
  }
}

void movimentoy(int yobb) {
  if (yobb > y) {
    digitalWrite(dirPin2, LOW);  // motor direction ccw
    for (int y; y <= yobb; y++) {
      //  Serial.println(y);
      digitalWrite(stepPin2, HIGH);
      delayMicroseconds(usDelay);
      digitalWrite(stepPin2, LOW);
      delayMicroseconds(usDelay);
      if (analogRead(fc2) < 1018)
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
      if (analogRead(fc1) < 1018) break;
    }
  } else {
    delay(100);
  }
}

void go_home() {
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

  Serial.println(analogRead(fc1));

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

void cerchio() {
  float r = 450;

  for (float i = 0; i <= 100.00; i++) {
    float theta = 2 * 3.1415 * i / 100.00;
    float xcerchio = r * cos(theta);
    Serial.println(xcerchio);
    float ycerchio = r * sin(theta);
    Serial.println(ycerchio);

    movimentox(xcerchio);
    movimentoy(ycerchio);
  }
}

// Funzione per disegnare una diagonale
void diagonale(int larghezza, int altezza) {
  // if (larghezza < altezza) {
  int movx = round(larghezza / 10);
  int movy = round(altezza / 10);
  for (int i = 0; i < 100; i++) {
    movimentox(movx * i);
    movimentoy(movy * i);
    Serial.println(movx * i);
    Serial.println(movy * i);
    delay(3000);
  }
}

// Funzione per disegnare una curva (quarto di cerchio)
void curva(int raggio, int quadrante) {
  // quadrante: 1=alto-destra, 2=alto-sinistra, 3=basso-sinistra, 4=basso-destra
  int passi = raggio * PI / 2 / 4;  // approssimazione per un quarto di cerchio
  float angolo_passo = PI / 2 / passi;
  float angolo_iniziale = 0;

  switch (quadrante) {
    case 1: angolo_iniziale = PI; break;
    case 2: angolo_iniziale = PI / 2; break;
    case 3: angolo_iniziale = 0; break;
    case 4: angolo_iniziale = 3 * PI / 2; break;
  }

  for (int i = 0; i < passi; i++) {
    float angolo = angolo_iniziale + i * angolo_passo;
    int dx = round(cos(angolo) * 4);
    int dy = round(sin(angolo) * 4);
    movimentox(dx);
    movimentoy(dy);
  }
}

void A(int dimensioni) {
  Serial.println("Hai chiamato la funzione A()");
  // Calcola l'altezza e la larghezza in step
  int altezza = 353 * dimensioni;
  int larghezza = 250 * dimensioni;

  // Diagonale da alto sinistra a metà destra
  diagonale(larghezza / 2, altezza);

  // Diagonale da metà destra a alto destra
  diagonale(larghezza / 2, -altezza);

  // Torna indietro per metà
  movimentoy(-altezza / 2);

  // Linea orizzontale per il tratto centrale
  movimentox(-larghezza);

  // Torna alla posizione finale (basso destra)
  movimentox(larghezza);
  movimentoy(altezza / 2);
}

void B(int dimensioni) {
  Serial.println("Hai chiamato la funzione B()");
  int altezza = 353 * dimensioni;
  int larghezza = 200 * dimensioni;

  // Linea verticale
  movimentoy(altezza);

  // Semicerchio superiore
  movimentox(larghezza / 2);
  curva(larghezza / 2, 1);
  movimentox(-larghezza / 2);

  // Torna alla metà
  movimentoy(-altezza / 2);

  // Semicerchio inferiore
  movimentox(larghezza / 2);
  curva(larghezza / 2, 4);
  movimentox(larghezza / 2);
}

void C(int dimensioni) {
  Serial.println("Hai chiamato la funzione C()");
  int altezza = 353 * dimensioni;
  int larghezza = 200 * dimensioni;

  // Posizione iniziale in alto a destra
  movimentox(larghezza);

  // Arco superiore
  curva(larghezza, 2);

  // Linea verticale
  movimentoy(altezza - 2 * larghezza);

  // Arco inferiore
  curva(larghezza, 3);

  // Vai alla posizione finale
  movimentox(larghezza);
}

void D(int dimensioni) {
  Serial.println("Hai chiamato la funzione D()");
  int altezza = 353 * dimensioni;
  int larghezza = 200 * dimensioni;

  // Linea verticale
  movimentoy(altezza);

  // Semicerchio
  movimentox(larghezza / 2);
  curva(larghezza / 2, 1);
  movimentoy(altezza - 2 * larghezza);
  curva(larghezza / 2, 4);
  movimentox(larghezza / 2);
}

void E(int dimensioni) {
  Serial.println("Hai chiamato la funzione E()");
  int altezza = 353 * dimensioni;
  int larghezza = 200 * dimensioni;

  // Linea verticale
  movimentoy(altezza);

  // Linea orizzontale superiore
  movimentox(larghezza);

  // Torna indietro
  movimentox(-larghezza);

  // Scendi a metà
  movimentoy(-altezza / 2);

  // Linea orizzontale di mezzo
  movimentox(larghezza * 3 / 4);

  // Torna indietro
  movimentox(-larghezza * 3 / 4);

  // Scendi in basso
  movimentoy(-altezza / 2);

  // Linea orizzontale inferiore
  movimentox(larghezza);
}

void EFFE(int dimensioni) {
  Serial.println("Hai chiamato la funzione F()");
  int altezza = 353 * dimensioni;
  int larghezza = 200 * dimensioni;

  // Linea verticale
  movimentoy(altezza);

  // Linea orizzontale superiore
  movimentox(larghezza);

  // Torna indietro
  movimentox(-larghezza);

  // Scendi a metà
  movimentoy(-altezza / 2);

  // Linea orizzontale di mezzo
  movimentox(larghezza * 3 / 4);

  // Torna indietro
  movimentox(-larghezza * 3 / 4);

  // Scendi in basso
  movimentoy(-altezza / 2);

  // Vai alla posizione finale
  movimentox(larghezza);
}

void G(int dimensioni) {
  Serial.println("Hai chiamato la funzione G()");
  int altezza = 353 * dimensioni;
  int larghezza = 200 * dimensioni;

  // Posizione iniziale in alto a destra
  movimentox(larghezza);

  // Arco superiore
  curva(larghezza, 2);

  // Linea verticale
  movimentoy(altezza - 2 * larghezza);

  // Arco inferiore parziale
  curva(larghezza, 3);

  // Linea orizzontale
  movimentox(larghezza);

  // Linea verticale
  movimentoy(-altezza / 3);

  // Linea orizzontale
  movimentox(-larghezza / 2);

  // Torna alla posizione finale
  movimentox(larghezza / 2);
  movimentoy(altezza / 3);
}

void H(int dimensioni) {
  Serial.println("Hai chiamato la funzione H()");
  int altezza = 353 * dimensioni;
  int larghezza = 200 * dimensioni;

  // Linea verticale sinistra
  movimentoy(altezza);

  // Torna a metà
  movimentoy(-altezza / 2);

  // Linea orizzontale
  movimentox(larghezza);

  // Linea verticale destra metà superiore
  movimentoy(altezza / 2);

  // Torna giù
  movimentoy(-altezza);

  // Vai alla posizione finale
  movimentox(0);
}

void I(int dimensioni) {
  Serial.println("Hai chiamato la funzione I()");
  int altezza = 353 * dimensioni;
  int larghezza = 100 * dimensioni;

  // Linea orizzontale superiore
  movimentox(larghezza);

  // Torna a metà
  movimentox(-larghezza / 2);

  // Linea verticale
  movimentoy(altezza);

  // Linea orizzontale inferiore
  movimentox(-larghezza / 2);
  movimentox(larghezza);
}

void J(int dimensioni) {
  Serial.println("Hai chiamato la funzione J()");
  int altezza = 353 * dimensioni;
  int larghezza = 150 * dimensioni;

  // Linea orizzontale superiore
  movimentox(larghezza);

  // Linea verticale
  movimentoy(altezza * 3 / 4);

  // Curva
  curva(larghezza / 2, 3);

  // Vai alla posizione finale
  movimentox(larghezza / 2);
}

void K(int dimensioni) {
  Serial.println("Hai chiamato la funzione K()");
  int altezza = 353 * dimensioni;
  int larghezza = 200 * dimensioni;

  // Linea verticale
  movimentoy(altezza);

  // Torna alla metà
  movimentoy(-altezza / 2);

  // Diagonale superiore
  diagonale(larghezza, -altezza / 2);

  // Torna alla metà
  movimentox(-larghezza);

  // Diagonale inferiore
  diagonale(larghezza, altezza / 2);
}

void L(int dimensioni) {
  Serial.println("Hai chiamato la funzione L()");
  movimentoy(353 * dimensioni);
  movimentox(353 * dimensioni / 2);
}

void M(int dimensioni) {
  Serial.println("Hai chiamato la funzione M()");
  int altezza = 353 * dimensioni;
  int larghezza = 300 * dimensioni;

  // Linea verticale sinistra
  movimentoy(altezza);

  // Diagonale discendente
  diagonale(larghezza / 2, -altezza / 2);

  // Diagonale ascendente
  diagonale(larghezza / 2, altezza / 2);

  // Linea verticale destra
  movimentoy(-altezza);

  // Vai alla posizione finale
  movimentox(0);
}

void N(int dimensioni) {
  Serial.println("Hai chiamato la funzione N()");
  int altezza = 353 * dimensioni;
  int larghezza = 200 * dimensioni;

  // Linea verticale sinistra
  movimentoy(altezza);

  // Diagonale
  diagonale(larghezza, -altezza);

  // Linea verticale destra
  movimentoy(altezza);

  // Vai alla posizione finale
  movimentoy(-altezza);
}

void O(int dimensioni) {
  Serial.println("Hai chiamato la funzione O()");
  int altezza = 353 * dimensioni;
  int larghezza = 200 * dimensioni;

  // Vai nella posizione di partenza
  movimentox(0);
  movimentoy(larghezza);

  // Curva in alto a sinistra
  curva(larghezza, 2);

  // Linea verticale destra
  movimentoy(altezza - 2 * larghezza);

  // Curva in basso a destra
  curva(larghezza, 4);

  // Linea orizzontale inferiore
  movimentox(-larghezza * 2);

  // Curva in basso a sinistra
  curva(larghezza, 3);

  // Linea verticale sinistra
  movimentoy(-(altezza - 2 * larghezza));

  // Curva in alto a sinistra
  curva(larghezza, 1);

  // Vai alla posizione finale
  movimentox(larghezza * 2);
  movimentoy(altezza - larghezza);
}

void P(int dimensioni) {
  Serial.println("Hai chiamato la funzione P()");
  int altezza = 353 * dimensioni;
  int larghezza = 200 * dimensioni;

  // Linea verticale
  movimentoy(altezza);

  // Semicerchio
  movimentox(larghezza);
  curva(larghezza, 1);
  movimentox(-larghezza);

  // Vai alla posizione finale
  movimentoy(-altezza / 2);
  movimentox(larghezza);
}

void Q(int dimensioni) {
  Serial.println("Hai chiamato la funzione Q()");
  int altezza = 353 * dimensioni;
  int larghezza = 200 * dimensioni;

  // Simile a O ma con una coda
  O(dimensioni);

  // Aggiungi la coda
  movimentox(-larghezza / 2);
  movimentoy(-larghezza / 2);
  diagonale(larghezza / 2, larghezza / 2);
}

void R(int dimensioni) {
  Serial.println("Hai chiamato la funzione R()");
  int altezza = 353 * dimensioni;
  int larghezza = 200 * dimensioni;

  // Linea verticale
  movimentoy(altezza);

  // Semicerchio
  movimentox(larghezza);
  curva(larghezza, 1);
  movimentox(-larghezza);

  // Diagonale
  movimentoy(-altezza / 2);
  diagonale(larghezza, -altezza / 2);
}

void S(int dimensioni) {
  Serial.println("Hai chiamato la funzione S()");
  int altezza = 353 * dimensioni;
  int larghezza = 200 * dimensioni;

  // Curva superiore
  movimentox(larghezza);
  curva(larghezza / 2, 2);

  // Linea verticale sinistra superiore
  movimentoy(altezza / 4);

  // Curva centrale
  curva(larghezza / 2, 4);
  movimentox(larghezza);
  curva(larghezza / 2, 1);

  // Linea verticale destra inferiore
  movimentoy(altezza / 4);

  // Curva inferiore
  curva(larghezza / 2, 3);
  movimentox(-larghezza);

  // Vai alla posizione finale
  movimentox(larghezza);
}

void T(int dimensioni) {
  Serial.println("Hai chiamato la funzione T()");
  int altezza = 353 * dimensioni;
  int larghezza = 200 * dimensioni;

  // Linea orizzontale superiore
  movimentox(larghezza);

  // Torna al centro
  movimentox(-larghezza / 2);

  // Linea verticale
  movimentoy(altezza);

  // Vai alla posizione finale
  movimentox(larghezza / 2);
}

void U(int dimensioni) {
  Serial.println("Hai chiamato la funzione U()");
  int altezza = 353 * dimensioni;
  int larghezza = 200 * dimensioni;

  // Linea verticale sinistra
  movimentoy(altezza);

  // Curva inferiore
  movimentoy(-altezza + larghezza);
  curva(larghezza, 3);

  // Linea verticale destra
  movimentoy(-altezza + larghezza);

  // Vai alla posizione finale
  movimentoy(altezza - larghezza);
}

void V(int dimensioni) {
  Serial.println("Hai chiamato la funzione V()");
  int altezza = 353 * dimensioni;
  int larghezza = 200 * dimensioni;

  // Diagonale discendente sinistra
  diagonale(larghezza, altezza);

  // Diagonale ascendente destra
  diagonale(larghezza, -altezza);

  // Vai alla posizione finale
  movimentoy(altezza);
}

void W(int dimensioni) {
  Serial.println("Hai chiamato la funzione W()");
  int altezza = 353 * dimensioni;
  int larghezza = 300 * dimensioni;

  // Diagonale discendente sinistra
  diagonale(larghezza / 2, altezza);

  // Diagonale ascendente centrale
  diagonale(larghezza / 2, -altezza / 2);

  // Diagonale discendente centrale
  diagonale(larghezza / 2, altezza / 2);

  // Diagonale ascendente destra
  diagonale(larghezza / 2, -altezza);

  // Vai alla posizione finale
  movimentoy(altezza);
}

void X(int dimensioni) {
  Serial.println("Hai chiamato la funzione X()");
  int altezza = 353 * dimensioni;
  int larghezza = 200 * dimensioni;

  // Diagonale discendente
  diagonale(larghezza, altezza);

  // Torna all'inizio
  movimentox(-larghezza);

  // Diagonale ascendente
  diagonale(larghezza, -altezza);

  // Vai alla posizione finale
  movimentoy(altezza);
}

void Y(int dimensioni) {
  Serial.println("Hai chiamato la funzione Y()");
  int altezza = 353 * dimensioni;
  int larghezza = 200 * dimensioni;

  // Diagonale superiore sinistra
  diagonale(larghezza / 2, altezza / 2);

  // Diagonale superiore destra
  diagonale(larghezza / 2, -altezza / 2);

  // Torna al centro
  movimentox(-larghezza / 2);

  // Linea verticale inferiore
  movimentoy(altezza / 2);

  // Vai alla posizione finale
  movimentox(larghezza);
}

void Z(int dimensioni) {
  Serial.println("Hai chiamato la funzione Z()");
  int altezza = 353 * dimensioni;
  int larghezza = 200 * dimensioni;

  // Linea orizzontale superiore
  movimentox(larghezza);

  // Diagonale
  diagonale(-larghezza, altezza);

  // Linea orizzontale inferiore
  movimentox(larghezza);

  // Vai alla posizione finale
  movimentoy(0);
}