#include <Servo.h>
Servo servo;

//Shift register
const int CLOCK = 7;
const int DATASERIAL = 5;
const int STORAGEREGISTER = 6;

//Patterns
const int PATTERN_NUMBERS [] = {
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

const int PATTERN_NUMBERS_LENGTH = sizeof(PATTERN_NUMBERS) / sizeof(PATTERN_NUMBERS[0]);

bool ruststand;
int staat;

//Poort variabelen
const int POORTMIN = 0;
const int POORTMAX = 180;
const int beweegTijd = 5000;
int poortValue;
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
int LDRPin = 0;
int LDRWaarde;

//Array knoppen ingedrukt
int knoppenIngedrukt [3];

const int BUTTON_INTERVAL = 10;

const int KNOPPEN [] = {5, 4, 3};

void setup() {
  Serial.begin(9600);
  setupShiftRegister();
  setupServo();
  setupLED();
  setupBuzzer();
  setupLDR();
  staat = 0;
}

void loop() {
  currentTime = millis();
  LDRWaarde = analogRead(LDRPin);
  checkInput();


  switch (staat) {

    case 0: //beginstand
      poortSluiten();
      LED_R_State(1);
      showPattern(PATTERN_SWC[0]);
      ruststand = true;
      if (LDRWaarde <= 200) {
        ruststand = false;
        staat = 21;
      }
      else if (poortValue <= POORTMIN && knoppenIngedrukt[0] == 4) { //Voetganger
        ruststand = false;
        previousTime = currentTime;
        staat = 1;
      }
      else if (poortValue <= POORTMIN && (knoppenIngedrukt[0] == 3 || knoppenIngedrukt[0] == 5)) { //Auto
        ruststand = false;
        previousTime = currentTime;
        staat = 11;
      }
      break;

    //Voetganger
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
      if (currentTime - previousTime >= INTERVAL_POORT + PATTERN_NUMBERS_LENGTH) {
        staat = 4;
      }
      break;

    case 4://Poort sluiten
      showPattern(PATTERN_SWC[0]);
      poortSluiten();
      buzzerSluiten();
      if (poortValue <= POORTMIN) {
        schuifArrayDoor();
        staat = 0;
      }
      break;

    //Auto
    case 11: //Stoplicht Groen
      LED_R_State(0);
      LED_G_State(1);

      if (currentTime - previousTime >= INTERVAL_SL_Groen_Rood - INTERVAL_SL_Geel_Rood) {
        previousTime = currentTime;
        LED_G_State(0);
        staat = 12;
      }
      break;

    case 12: //Stoplicht Geel
      LED_Y_State(1);
      if (currentTime - previousTime >= INTERVAL_SL_Geel_Rood) {
        previousTime = currentTime;
        LED_Y_State(0);
        staat = 13;
      }
      break;

    case 13: //Stoplicht Rood
      LED_R_State(1);
      if (currentTime - previousTime >= INTERVAL_DODE_TIJD) {
        schuifArrayDoor();
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
      if (poortValue <= POORTMIN) {
        LED_Y_State(0);
        staat = 0;
      }
  }
}

