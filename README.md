# 🖊️ Pen Plotter - Plotter XY a Controllo Diretto Arduino

Plotter a penna controllato direttamente da **Arduino** con motori stepper per scrittura automatica di testo e numeri su carta formato A3.

![Arduino](https://img.shields.io/badge/Arduino-00979D?logo=arduino&logoColor=white)
![Stepper Motors](https://img.shields.io/badge/Stepper-NEMA17-orange)
![Status](https://img.shields.io/badge/Status-Functional-success)
![License](https://img.shields.io/badge/License-MIT-blue)

---

## 📋 Indice

**Getting Started**
- [Caratteristiche](#-caratteristiche)
- [Hardware Richiesto](#-hardware-richiesto)
- [Schema Collegamenti](#-schema-collegamenti)
- [Installazione](#-installazione)

**Configurazione e Uso**
- [Configurazione](#-configurazione)
- [Utilizzo](#-utilizzo)
- [Comandi Disponibili](#-comandi-disponibili)
- [Alfabeto e Numeri](#-alfabeto-e-numeri)

**Manutenzione e Personalizzazione**
- [Calibrazione](#-calibrazione)
- [Troubleshooting](#-troubleshooting)
- [Personalizzazione](#-personalizzazione)
- [Specifiche Tecniche](#-specifiche-tecniche)

**Progetto e Community**
- [Roadmap](#-roadmap)
- [Contribuire](#-contribuire)
- [Licenza](#-licenza)
- [Autore](#-autore)
- [Collaboratori](#-collaboratori)
- [Ringraziamenti](#-ringraziamenti)

**Risorse**
- [Risorse Utili](#-risorse-utili)
- [Video e Media](#-video-e-media)
- [FAQ](#-faq)

## ✨ Caratteristiche

- ✍️ **Scrittura automatica** di testo alfanumerico (A-Z, 0-9)
- 📏 **Area di lavoro**: 270x210mm (A4 landscape / quasi A3)
- 🎯 **Precisione**: 1mm = 100 step (microstepping 1/4)
- 🏠 **Homing automatico** con finecorsa ottici
- 🎨 **LED RGB** per feedback visivo dello stato
- ⚡ **Velocità variabile** (5 modalità microstepping)
- 📱 **Controllo seriale** via USB (9600 baud)
- 🔘 **Pulsanti hardware** per funzioni rapide (home, alfabeto, a capo)
- 🖊️ **Sollevamento penna** automatico con servo/solenoide
- 💾 **Gestione automatica a capo** quando si raggiunge il margine destro

---

## 🔧 Hardware Richiesto

### Componenti Elettronici

| Componente | Quantità | Pin Arduino | Note |
|-----------|----------|-------------|------|
| **Arduino Uno/Mega** | 1 | - | ATmega328P o superiore |
| **Driver A4988** | 2 | - | Per motori stepper |
| **NEMA 17 Stepper** | 2 | - | 200 step/rev, Asse X e Y |
| **Servo/Solenoide** | 1 | Pin 6 | Sollevamento penna |
| **Finecorsa Ottici** | 2 | A0, A1 | Homing X e Y |
| **LED RGB** | 1 | 4, 5, 7 | Feedback visivo |
| **Pulsanti** | 3 | A2, A3, A5 | Funzioni rapide |
| **Alimentatore 12V** | 1 | - | Minimo 3A |

### Pinout Dettagliato

```cpp
// MOTORI STEPPER
const int stepPin1 = 3;    // Step Motore X (Orizzontale)
const int dirPin1 = 2;     // Direzione Motore X
const int stepPin2 = 11;   // Step Motore Y (Verticale)
const int dirPin2 = 13;    // Direzione Motore Y

// MICROSTEPPING A4988
const int ms1 = 8;         // Microstepping bit 1
const int ms2 = 9;         // Microstepping bit 2
const int ms3 = 10;        // Microstepping bit 3

// FINECORSA
const int fc1 = A0;        // Finecorsa X (sinistra)
const int fc2 = A1;        // Finecorsa Y (alto)

// ATTUATORI
const int penna = 6;       // Servo/Solenoide penna

// LED RGB (catodo comune)
const int RED_PIN = 4;     // Rosso
const int GREEN_PIN = 7;   // Verde
const int BLUE_PIN = 5;    // Blu

// PULSANTI (pull-up attivo)
const int BTN_ALFABETO = A5;  // Pulsante BLU - Stampa alfabeto
const int BTN_HOME = A2;      // Pulsante ROSSO - Vai a home
const int BTN_ACAPO = A3;     // Pulsante BIANCO - A capo
```

### Componenti Meccanici

| Componente | Quantità | Dimensione | Note |
|-----------|----------|-----------|------|
| **Barre lineari** | 2 | Ø8mm, 400-500mm | Assi X e Y |
| **Cuscinetti lineari LM8UU** | 4 | Per Ø8mm | - |
| **Cinghie GT2** | 2m | 6mm larghezza | - |
| **Pulegge GT2** | 2 | 20 denti | Per motori |
| **Viti M3/M4** | Set | Varie | Assemblaggio |
| **Base in legno/alluminio** | 1 | 500x400mm | Struttura |
| **Supporto penna** | 1 | Stampato 3D | Con servo |

---

## 🔌 Schema Collegamenti

### Driver A4988 → Arduino

```
Driver Motore X:
├─ STEP → Pin 3
├─ DIR  → Pin 2
├─ MS1  → Pin 8
├─ MS2  → Pin 9
├─ MS3  → Pin 10
├─ VDD  → 5V Arduino
├─ GND  → GND Arduino
└─ VMOT → 12V Alimentatore

Driver Motore Y:
├─ STEP → Pin 11
├─ DIR  → Pin 13
├─ MS1  → Pin 8 (condiviso)
├─ MS2  → Pin 9 (condiviso)
├─ MS3  → Pin 10 (condiviso)
├─ VDD  → 5V Arduino
├─ GND  → GND Arduino
└─ VMOT → 12V Alimentatore
```

### Schema Finecorsa

```
Finecorsa Ottico:
- Tipo: fotocellula o sensore IR
- Logica: HIGH quando NON premuto (>1018 analogRead)
         LOW quando premuto (<1018 analogRead)
- Alimentazione: 5V
- Output: Analogico (A0, A1)
```

### LED RGB

```
LED RGB (catodo comune):
├─ R → Pin 4 (PWM)
├─ G → Pin 7 (PWM)
├─ B → Pin 5 (PWM)
└─ Catodo → GND
```

---

## 📥 Installazione

### 1. Download Repository

```bash
git clone https://github.com/Marr111/pen_plotter.git
cd pen_plotter
```

### 2. Arduino IDE Setup

1. Apri `pen_plotter.ino` con Arduino IDE
2. Seleziona **Board**: Arduino Uno
3. Seleziona **Porta**: COM3 (Windows) o /dev/ttyUSB0 (Linux)
4. Verifica e carica il codice

### 3. Test Connessione Seriale

```bash
1. Apri Serial Monitor (Ctrl+Shift+M)
2. Imposta baud rate: 9600
3. Dovresti vedere: "pronto"
```

---

## ⚙️ Configurazione

### Parametri Principali

```cpp
// Area di lavoro (in step, 1mm = 100 step)
// Foglio: 270mm x 210mm = 27.000 step x 21.000 step
int usDelay = 700;  // Velocità motori (microsecondi tra step)

// Dimensioni carattere
// Altezza lettera: ~2000 step = ~20mm
// Larghezza lettera: ~1300 step = ~13mm
// Spaziatura tra lettere: ~2300 step = ~23mm
```

### Modalità Microstepping

Il sistema supporta 5 modalità di microstepping (A4988):

| Modalità | MS1 | MS2 | MS3 | Step/rev | Precisione | Uso |
|----------|-----|-----|-----|----------|------------|-----|
| **1 - Full** | LOW | LOW | LOW | 200 | Bassa | Homing veloce |
| **2 - Half** | HIGH | LOW | LOW | 400 | Media | - |
| **3 - Quarter** | HIGH | HIGH | LOW | 800 | Alta | **Scrittura** ⭐ |
| **4 - Eighth** | HIGH | HIGH | LOW | 1600 | Molto alta | - |
| **5 - Sixteenth** | HIGH | HIGH | HIGH | 3200 | Massima | Precisione max |

**Default**: Modalità 3 (Quarter Step) per scrittura

---

## 🎮 Utilizzo

### Controllo via Seriale

#### 1. Aprire Serial Monitor

```
Arduino IDE → Tools → Serial Monitor
Baud Rate: 9600
```

#### 2. Inviare Testo

```
Inserisci testo e premi INVIO:

Esempi:
> CIAO              → Scrive "CIAO"
> ARDUINO 2024      → Scrive "ARDUINO 2024"
> PLOTTER V1        → Scrive "PLOTTER V1"
> |                 → Va a capo manualmente
```

#### 3. Caratteri Supportati

- **Lettere**: A-Z (automaticamente convertite in maiuscolo)
- **Numeri**: 0-9
- **Spazio**: ` ` (spazia di 1000 step)
- **A capo**: `|` (ritorna a inizio riga successiva)

### Pulsanti Hardware

| Pulsante | Pin | Colore | Funzione |
|----------|-----|--------|----------|
| **Alfabeto** | A5 | BLU | Stampa alfabeto completo A-Z + 0-9 |
| **Home** | A2 | ROSSO | Ritorna a posizione home (0,0) |
| **A capo** | A3 | BIANCO | Va a capo riga successiva |

### LED di Stato

| Colore | Significato |
|--------|-------------|
| 🟢 **Verde** | Pronto - in attesa di comandi |
| 🟠 **Arancione** | Homing in corso |
| 🔴 **Rosso** | Errore - finecorsa attivato |
| 🟣 **Viola** | Esecuzione comando pulsante |

---

## 📝 Comandi Disponibili

### Funzioni Lettere

```cpp
A-Z  → Disegna lettera maiuscola
```

**Esempio output seriale:**
```
> HELLO
Hai chiamato la funzione H()
Hai chiamato la funzione E()
Hai chiamato la funzione L()
Hai chiamato la funzione L()
Hai chiamato la funzione O()
Fine scrittura.
```

### Funzioni Numeri

```cpp
0-9  → Disegna numero
```

**Esempio:**
```
> 2024
Hai chiamato la funzione due()
Hai chiamato la funzione zero()
Hai chiamato la funzione due()
Hai chiamato la funzione quattro()
```

### Comandi Speciali

| Comando | Codice | Funzione |
|---------|--------|----------|
| **Spazio** | ` ` | Sposta di 10mm a destra senza scrivere |
| **A capo** | `\|` | Va alla riga successiva |
| **Home** | Pulsante A2 | Ritorna a (0,0) con finecorsa |
| **Alfabeto** | Pulsante A5 | Stampa tutto l'alfabeto + numeri |

---

## 🔤 Alfabeto e Numeri

### Lettere Implementate

✅ **Completamente funzionanti:**
- A, C, E, F, G, H, I, L, O, S, T, U, V

⚠️ **Da implementare:**
- B, D, J, K, M, N, P, Q, R, W, X, Y, Z

### Numeri Implementati

✅ **Tutti i numeri:**
- 0, 1, 2, 3, 4, 5, 6, 7, 8, 9

### Esempi di Tracciati

**Lettera A:**
```
    /\
   /  \
  /----\
 /      \
```

**Numero 8:**
```
  ___
 /   \
 \___/
 /   \
 \___/
```

**Lettera S:**
```
  ____
 /
 \___
     \
 ____/
```

---

## 🎯 Calibrazione

### 1. Calibrazione Origine (Homing)

Il sistema usa finecorsa ottici per trovare l'origine:

```cpp
// Sequenza automatica all'avvio
1. LED arancione
2. Motore Y si muove VERSO L'ALTO fino a fc2 attivo
3. Motore X si muove VERSO SINISTRA fino a fc1 attivo
4. Posizione (0,0) raggiunta
5. Spostamento di sicurezza +100 step
```

**Test manuale homing:**
- Premi pulsante ROSSO (A2)
- Attendi LED viola
- Plotter torna a home

### 2. Calibrazione Step/mm

**Valore attuale:** `1mm = 100 step`

**Formula:**
```
step/mm = (microstepping × step_motore) / (passo_cinghia × denti_puleggia)

Esempio con setup attuale:
= (4 × 200) / (2mm × 20 denti)
= 800 / 40
= 20 step/mm base

Con Quarter step (1/4):
= 20 × 4 = 80 step/mm ≈ 100 step/mm (con correzione)
```

**Per ricalibrare:**

1. Disegna una linea di 100mm:
```cpp
// Nel codice
digitalWrite(penna, HIGH);
movimentoDestra(10000);  // 10000 step = 100mm
digitalWrite(penna, LOW);
```

2. Misura la linea reale con righello
3. Calcola nuovo valore:
```
nuovo_step/mm = (10000 × 100) / lunghezza_misurata
```

4. Aggiorna il codice nelle funzioni carattere

### 3. Calibrazione Penna

**Servo/Solenoide:**

```cpp
// Pin 6 - Segnale digitale ON/OFF
digitalWrite(penna, HIGH);  // Penna GIÙ (scrive)
digitalWrite(penna, LOW);   // Penna SU (non scrive)
```

**Se usi un servo:**

Sostituisci con libreria Servo:
```cpp
#include <Servo.h>
Servo servoPenna;

void setup() {
  servoPenna.attach(6);
  servoPenna.write(90);  // Penna su
}

void pennaSu() {
  servoPenna.write(90);  // Regola angolo
}

void pennaGiu() {
  servoPenna.write(60);  // Regola angolo
}
```

### 4. Test Pattern

Esegui test completo:

```
Serial Monitor:
> ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789

Verifica:
- Spaziatura uniforme
- Altezza costante
- Linee dritte
- Ritorno a capo corretto
```

---

## 🔍 Troubleshooting

### Problemi Comuni

| Problema | Causa Probabile | Soluzione |
|----------|-----------------|-----------|
| **LED rosso fisso** | Finecorsa attivato | Muovi manualmente carrello, riavvia Arduino |
| **Nessun movimento** | Driver non alimentati | Verifica 12V, connessioni driver |
| **Movimenti a scatti** | Velocità troppo alta | Aumenta `usDelay` (es. 700 → 1000) |
| **Caratteri storti** | Cinghie lente | Tendi le cinghie GT2 |
| **Penna non scrive** | Altezza errata | Regola altezza supporto penna |
| **A capo non funziona** | Variabile `nparole` errata | Reset con pulsante HOME |
| **Scrittura oltre margine** | Limite non gestito | Sistema va a capo automatico a 39000 step |

### Debug Step-by-Step

#### 1. Test Motori Singoli

```cpp
// Aggiungi nel loop() per test
void loop() {
  // Test Motore X
  movimentoDestra(1000);
  delay(1000);
  movimentoSinistra(1000);
  delay(1000);
  
  // Test Motore Y
  movimentoAlto(1000);
  delay(1000);
  movimentoBasso(1000);
  delay(1000);
}
```

#### 2. Test Finecorsa

```cpp
void loop() {
  Serial.print("FC1 (X): ");
  Serial.print(analogRead(fc1));
  Serial.print(" | FC2 (Y): ");
  Serial.println(analogRead(fc2));
  delay(500);
}
```

**Valori attesi:**
- Non premuto: >1018
- Premuto: <1018

#### 3. Test LED RGB

```cpp
void loop() {
  led("rosso"); delay(1000);
  led("verde"); delay(1000);
  led("blu"); delay(1000);
  led("giallo"); delay(1000);
  led("viola"); delay(1000);
}
```

#### 4. Test Penna

```cpp
void loop() {
  digitalWrite(penna, HIGH);
  delay(2000);
  digitalWrite(penna, LOW);
  delay(2000);
}
```

### Messaggi Seriale

| Messaggio | Significato | Azione |
|-----------|-------------|--------|
| `"pronto"` | Setup completato | Tutto OK |
| `"Finecorsa attivato errore"` | Finecorsa premuto durante movimento | Riposiziona manualmente |
| `"Carattere non valido"` | Lettera non implementata | Usa solo lettere disponibili |
| `"Fine scrittura"` | Frase completata | Pronto per nuovo input |

---

## 🛠️ Personalizzazione

### Aggiungere Nuove Lettere

Template per creare lettere mancanti:

```cpp
void LETTERA() {
  Serial.println("Hai chiamato la funzione LETTERA()");
  
  digitalWrite(penna, HIGH);  // Penna GIÙ - inizia disegno
  
  // Esempio: disegna una L
  movimentoAlto(2000);        // Linea verticale 20mm
  movimentoSinistra(1300);    // Linea orizzontale 13mm
  
  digitalWrite(penna, LOW);   // Penna SU - finisce disegno
  
  // Spaziatura per prossima lettera
  movimentoSinistra(1000);    // 10mm di spazio
  movimentoBasso(2000);       // Torna a baseline
}
```

**Movimenti disponibili:**
```cpp
movimentoAlto(step);       // Muove verso ALTO
movimentoBasso(step);      // Muove verso BASSO
movimentoDestra(step);     // Muove verso DESTRA
movimentoSinistra(step);   // Muove verso SINISTRA
```

### Aggiungere Simboli Speciali

```cpp
void puntoEsclamativo() {
  digitalWrite(penna, HIGH);
  movimentoAlto(1500);
  digitalWrite(penna, LOW);
  movimentoBasso(1800);
  digitalWrite(penna, HIGH);
  movimentoAlto(200);
  digitalWrite(penna, LOW);
  movimentoSinistra(800);
}

void puntoInterrogativo() {
  digitalWrite(penna, HIGH);
  // ... tracciato ?
  digitalWrite(penna, LOW);
}
```

Aggiungi al parser in `letturaseriale()`:

```cpp
else if (c == '!') {
  puntoEsclamativo();
} else if (c == '?') {
  puntoInterrogativo();
}
```

### Modificare Dimensioni Caratteri

**Parametri attuali:**
```cpp
Altezza lettera:    2000 step = 20mm
Larghezza lettera:  1300 step = 13mm
Spaziatura:         2300 step = 23mm
```

**Per caratteri più grandi (es. 30mm):**

```cpp
// Moltiplica tutti i valori per 1.5
Altezza:    2000 × 1.5 = 3000 step
Larghezza:  1300 × 1.5 = 1950 step
Spaziatura: 2300 × 1.5 = 3450 step
```

### Aggiungere Font Corsivo

```cpp
void A_corsivo() {
  digitalWrite(penna, HIGH);
  
  // Linea inclinata sinistra
  for(int i=0; i<100; i++) {
    movimentoSinistra(10);
    movimentoAlto(20);
  }
  
  // Linea inclinata destra
  for(int i=0; i<100; i++) {
    movimentoSinistra(10);
    movimentoBasso(20);
  }
  
  digitalWrite(penna, LOW);
}
```

### Velocità Personalizzate

```cpp
// Variabile globale
int usDelay = 700;  // Default

// Per scrittura veloce
usDelay = 400;

// Per precisione massima
usDelay = 1200;

// Cambio dinamico
void velocitaScrittura(String tipo) {
  if(tipo == "veloce") usDelay = 400;
  else if(tipo == "normale") usDelay = 700;
  else if(tipo == "precisa") usDelay = 1200;
}
```

---

## 📊 Specifiche Tecniche

### Performance

| Parametro | Valore |
|-----------|--------|
| **Area massima** | 270 × 210 mm |
| **Risoluzione** | 0.01 mm (100 step/mm) |
| **Velocità scrittura** | ~5 caratteri/minuto |
| **Caratteri per riga** | ~12-15 (in base a dimensione) |
| **Righe per foglio** | ~8-10 |
| **Precisione ripetibilità** | ±0.5 mm |

### Limiti Sistema

```cpp
// Gestione automatica a capo
if (nparole > 39000) {  // ~390mm dalla sinistra
  acapo();              // Va a riga successiva
}

// Area sicura (con margini)
// X: 0 → 25000 step (250mm)
// Y: 0 → 19000 step (190mm)
```

---

## 🗺️ Roadmap

### ✅ Versione 1.0 (Attuale)

- [x] Alfabeto base (13/26 lettere)
- [x] Numeri completi (0-9)
- [x] Homing automatico
- [x] Gestione a capo
- [x] LED feedback
- [x] Pulsanti hardware

### 🔨 Versione 1.5 (Prossima)

- [ ] Lettere mancanti (B, D, J, K, M, N, P, Q, R, W, X, Y, Z)
- [ ] Simboli (., !, ?, -, +, ecc.)
- [ ] Font minuscolo
- [ ] Regolazione velocità via seriale
- [ ] Salvataggio preferenze EEPROM

### 🚀 Versione 2.0 (Futuro)

- [ ] Font multipli (corsivo, grassetto)
- [ ] Disegno forme geometriche
- [ ] Import file di testo (.txt)
- [ ] Interfaccia grafica PC (Processing/Python)
- [ ] Cambio penna automatico (multi-colore)
- [ ] Logo e grafiche semplici

---

## 🤝 Contribuire

### Come Contribuire

1. **Fork** del repository
2. Crea branch feature (`git checkout -b feature/NuovaLettera`)
3. Implementa modifiche
4. Test accurato
5. Commit (`git commit -m 'Aggiunta lettera B'`)
6. Push (`git push origin feature/NuovaLettera`)
7. Pull Request

### Aree Prioritarie

🔤 **Lettere mancanti**
- Implementa tracciati lettere B, D, J, K, M, N, P, Q, R, W, X, Y, Z

⚡ **Ottimizzazioni**
- Riduci movimenti inutili
- Ottimizza percorsi tracciati

📚 **Documentazione**
- Video tutorial assemblaggio
- Guide calibrazione
- Esempi progetti

🐛 **Bug fixing**
- Testa edge cases
- Migliora gestione errori

---

## 📄 Licenza

Questo progetto è distribuito sotto **licenza MIT**.

```
MIT License - Copyright (c) 2024

Permesso concesso a chiunque di usare, copiare, modificare e distribuire
questo software per qualsiasi scopo, con o senza fini di lucro.
```

---

## 👤 Autore

**Marr111**

- 🌐 GitHub: [@Marr111](https://github.com/Marr111)
- 📧 Email: [contattami su GitHub]

---

## 👥 Collaboratori

Questo progetto è stato sviluppato con il contributo di: Alberto Parisi e [Simone Baldassare@](https://github.com/B4ldino)

Un ringraziamento speciale a tutti i collaboratori per il loro impegno e dedizione al progetto! 🎉

## 🙏 Ringraziamenti

- **Arduino Community** - Per librerie e supporto
- **Maker italiani** - Per ispirazione e consigli
- **Tutti i contributori** - Che migliorano il progetto

---

## 📚 Risorse Utili

### Guide e Tutorial

- [Guida Stepper Motors](https://lastminuteengineers.com/a4988-stepper-motor-driver-arduino-tutorial/)
- [Microstepping Explained](https://www.pololu.com/product/1182)
- [Servo Library Arduino](https://www.arduino.cc/reference/en/libraries/servo/)

### Community

- [Arduino Forum](https://forum.arduino.cc/)
- [Reddit r/Arduino](https://reddit.com/r/arduino)
- [Instructables CNC](https://www.instructables.com/circuits/arduino/projects/)

### Software Utili

- [Arduino IDE](https://www.arduino.cc/en/software)
- [Fritzing](https://fritzing.org/) - Schemi circuiti
- [Tinkercad](https://www.tinkercad.com/) - Simulazione online

---

## 🎥 Video e Media

### Screenshots Funzionamento

```
// Aggiungere in futuro:
- Foto assemblaggio completo
- Video homing sequence
- Esempio scrittura "HELLO WORLD"
- Time-lapse alfabeto completo
```

---

## ❓ FAQ

**Q: Come cambio la velocità?**  
A: Modifica la variabile `usDelay` nel codice (valore più alto = più lento)

**Q: Posso usare GRBL?**  
A: No, questo progetto usa controllo diretto Arduino senza G-Code

**Q: Come aggiungo lettere minuscole?**  
A: Duplica le funzioni lettere maiuscole, riduci le dimensioni (~50%) e adatta il parser

**Q: Supporta altri formati carta?**  
A: Sì, modifica le costanti nell'area di lavoro e calibra finecorsa di conseguenza

---

<div align="center">

### ⭐ Se questo progetto ti è utile, lascia una stella! ⭐
![Build Status](https://img.shields.io/badge/build-passing-brightgreen)
![Made in Italy](https://img.shields.io/badge/Made%20in-Italy-green?style=flat&logo=italy)

**Made with ❤️ and stepper motors**

</div>
