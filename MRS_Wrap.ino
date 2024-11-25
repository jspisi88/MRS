// ***************************************
// ESP32 Basic Template for Dasduino CONNECTPLUS with Detailed Tasks
// ***************************************

#include <Arduino.h>
#include <EEPROM.h>

// Pin Definitions (Adjust according to your setup)
#define LED_PIN 2        // Pin za LED (digitalni izlaz)
#define ANALOG_PIN 36    // Pin za analogni ulaz (ADC)
#define BUTTON_PIN 0     // Pin za gumb (digitalni ulaz)

// EEPROM Config
#define EEPROM_SIZE 64   // Postavljanje veličine EEPROM-a
#define EEPROM_INT_ADDR 0  // Adresa za spremanje integera
#define EEPROM_FLOAT_ADDR 4 // Adresa za spremanje floata

// Globalne Varijable
int ledState = LOW;       // Varijabla za praćenje stanja LED-a
unsigned long previousMillis = 0; // Za funkciju millis() scheduler
const long interval = 1000; // Interval za scheduler u milisekundama

// Static varijable i Flash memorija
static int staticCounter = 0; // Static varijabla zadržava vrijednost između iteracija

// Funkcije za EEPROM varijable
void saveIntToEEPROM(int value) {
  EEPROM.put(EEPROM_INT_ADDR, value);
  EEPROM.commit();
  Serial.print("Integer spremljen u EEPROM: ");
  Serial.println(value);
}

int readIntFromEEPROM() {
  int value;
  EEPROM.get(EEPROM_INT_ADDR, value);
  return value;
}

void saveFloatToEEPROM(float value) {
  EEPROM.put(EEPROM_FLOAT_ADDR, value);
  EEPROM.commit();
  Serial.print("Float spremljen u EEPROM: ");
  Serial.println(value);
}

float readFloatFromEEPROM() {
  float value;
  EEPROM.get(EEPROM_FLOAT_ADDR, value);
  return value;
}

void printEEPROMValues() {
  int intValue = readIntFromEEPROM();
  float floatValue = readFloatFromEEPROM();

  Serial.print("Integer iz EEPROM-a: ");
  Serial.println(intValue);
  Serial.print("Float iz EEPROM-a: ");
  Serial.println(floatValue);
}

// Funkcije za static vrijednosti
void staticMillisExample() {
  static unsigned long lastMillis = 0;
  unsigned long currentMillis = millis();

  if (currentMillis - lastMillis >= 1000) {
    lastMillis = lastMillis + 1;

    Serial.print("Static millis vrijednost ažurirana nakon 1 sekunde: ");
    Serial.println(lastMillis);
  }
}

void regularMillisExample() {
  unsigned long lastMillis = 0;
  unsigned long currentMillis = millis();

  if (currentMillis - lastMillis >= 1000) {
    lastMillis = lastMillis + 1;
    Serial.print("Obična millis vrijednost ažurirana nakon 1 sekunde: ");
    Serial.println(lastMillis);
  }
}

void setup() {
  // Postavljanje Serijske Komunikacije
  Serial.begin(115200); // Pokretanje serijske komunikacije na 115200 baud-a

  // Postavljanje Načina Pina
  pinMode(LED_PIN, OUTPUT); // Postavljanje LED pina kao izlaz
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Postavljanje pina gumba kao ulaz s pull-up otpornikom

    // Inicijalizacija EEPROM-a
  if (!EEPROM.begin(EEPROM_SIZE)) {
    Serial.println("Greška pri inicijalizaciji EEPROM-a!");
    while (1);
  }

  // Početne vrijednosti za EEPROM
  saveIntToEEPROM(42);
  saveFloatToEEPROM(3.14);

  // Ispis EEPROM vrijednosti
  printEEPROMValues();

  // Inicijalne Poruke
  Serial.println("ESP32 Inicijaliziran");

}

void loop() {
  // Čitanje Stanja Gumba
  int buttonState = digitalRead(BUTTON_PIN);

  // Ispis Stanja Gumba
  Serial.print("Stanje gumba: ");
  Serial.println(buttonState);

  // Primjer Uvjetne Izjave
  if (buttonState == LOW) {
    digitalWrite(LED_PIN, HIGH); // Uključivanje LED-a
    Serial.println("LED UKLJUČEN");
  } else {
    digitalWrite(LED_PIN, LOW); // Isključivanje LED-a
    Serial.println("LED ISKLJUČEN");
  }

  // Scheduler Primjer Korištenjem millis()
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Prebacivanje Stanja LED-a
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);

    Serial.println("Scheduler prebacuje stanje LED-a");

    // Ažuriranje i ispis static varijable
    staticCounter++;
    Serial.print("Static Counter: ");
    Serial.println(staticCounter);
  }

  // Primjer Switch-Case Izjave
  switch (buttonState) {
    case LOW:
      Serial.println("Gumb pritisnut");
      break;
    case HIGH:
      Serial.println("Gumb otpušten");
      break;
    default:
      Serial.println("Nepoznato stanje");
      break;
  }

  // Primjer funkcija za millis
  staticMillisExample();
  regularMillisExample();

  // Odgoda za Stabilnost
  delay(2000);
}

// Primjer Funkcije
void printAnalogValue() {
  int analogValue = analogRead(ANALOG_PIN); // Očitanje s analognog pina
  Serial.print("Analogna vrijednost: ");
  Serial.println(analogValue);
}

// ZADACI ZA STUDENTE:
// TODO 1: Postavite dodatni LED pin i napišite kod za uključivanje i isključivanje dvije LED-ice naizmjenično.
// TODO 2: Implementirajte očitanje analogne vrijednosti u funkciji loop() i ispisujte je na serijski monitor.
// TODO 3: Promijenite interval u scheduleru na 500 ms i promatrajte promjene.
// TODO 4: Dodajte još jednu uvjetnu izjavu za treći scenarij korištenjem digitalnog pina.
// TODO 5: Koristite funkciju printAnalogValue() unutar loop() i analizirajte rezultate.
// TODO 6: Dodajte dodatnu funkciju koja će treperiti LED-icu pet puta kad se gumb pritisne.
// TODO 7: Dodajte ispis trenutne vrijednosti iz Flash memorije koristeći pgm_read_word() i pgm_read_dword() funkcije.
// TODO 8: Kreirajte funkciju koja čita i mijenja vrijednosti u static varijabli.
