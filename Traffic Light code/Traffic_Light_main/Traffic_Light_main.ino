#include <Servo.h>
Servo servo;

//Shift register
const int CLOCK = 7;
const int DATASERIAL = 5;
const int STORAGEREGISTER = 6;

//Patterns
const int PATTERN_NUMBERS [] = {
  B11111100, //0
  B01100000, //1
  B11011010, //2
  B11110010, //3
  B01100110, //4
  B10110110, //5
  B10111110, //6
};

const int PATTERN_SWC [] = {
  B01101110, // Stop
  B01101100, // Walk
  B10011100, // Caution
};

bool ruststand;
int staat;

//Poort variabelen
const int POORTMIN = 0;
const int POORTMAX = 180;
const int beweegTijd = 3000;
int poortValue = POORTMIN;
const int POORTDELAY = beweegTijd / POORTMAX;
const int INTERVAL_POORT = 5000;

//Buzzer variabelen
const int BUZZERPIN = 3;


//Time
unsigned long currentTime;
unsigned long previousTime;

//Stoplicht variabelen
const int INTERVAL_SL_Geel_Rood = 2000;
const int INTERVAL_SL_Groen_Rood = 10000;
const int INTERVAL_DODE_TIJD = 5000;

//LDR
int LDRPin = A0;
int LDRWaarde;

void setup() {
  Serial.begin(9600);
  setupShiftRegister();
  setupServo();
  setupLED();
  setupBuzzer();
  staat = 0;
}

void loop() {
  currentTime = millis();
  LDRWaarde = analogRead(LDRPin);
  Serial.println(LDRWaarde);
  switch (staat) {
    case 0: //beginstand
      poortSluiten();
      LED_R_State(1);
      showPattern(PATTERN_SWC[0]);
      ruststand = true;
      if (LDRWaarde <= 200) {
        staat = 21;
      }
      else if (poortValue <= POORTMIN) {
        ruststand = false;
        previousTime = currentTime;
        staat = 1;
      }
      break;

    case 1: //Poort openen
      poortOpenen();
      if (poortValue >= POORTMAX) {
        previousTime = currentTime;
        staat = 2;
      }
      break;
    case 2:// Poort open
      showPattern(PATTERN_SWC[1]);
      buzzerLopen();

      if (currentTime - previousTime >= INTERVAL_POORT) {
        staat = 3;
      }
      break;

    case 3: //Poort laatste kans
      patternCountdown();
      buzzerCountdown();
      if (currentTime - previousTime >= INTERVAL_POORT + 6) {
        staat = 4;
      }
      break;

    case 4://Poort sluiten
      showPattern(PATTERN_SWC[0]);
      poortSluiten();
      buzzerSluiten();
      if (poortValue <= POORTMIN) {
        staat = 0;
        ruststand = true;
      }
      break;

    case 11: //Stoplicht Groen
      LED_R_State(0);
      LED_G_State(1);

      if (currentTime - previousTime >= INTERVAL_SL_Groen_Rood - INTERVAL_SL_Geel_Rood) {
        previousTime = currentTime;
        LED_G_State(0);
        staat = 6;
      }
      break;

    case 12: //Stoplicht Geel
      LED_Y_State(1);
      if (currentTime - previousTime >= INTERVAL_SL_Geel_Rood) {
        previousTime = currentTime;
        LED_Y_State(0);
        staat = 7;
      }
      break;

    case 13: //Stoplicht Rood
      LED_R_State(1);
      if (currentTime - previousTime >= INTERVAL_DODE_TIJD) {
        staat = 0;
      }
      break;

    case 21: //Poort openen nacht
      buzzerNacht();
      poortOpenen();
      if (poortValue >= POORTMAX) {
        staat = 22;
      }
      break;

    case 22:
      LED_R_State(0);
      showPattern(PATTERN_SWC[2]);
      LED_Y_Blink();
      if (LDRWaarde > 200) {
        staat = 23;
      }
      break;

    case 23:
      showPattern(PATTERN_SWC[0]);
      buzzerNacht();
      poortSluiten();
      LED_Y_State(1);
      if (poortValue == POORTMIN) {
        LED_Y_State(0);
        staat = 0;
      }



  }
}

