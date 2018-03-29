#include <Servo.h>
Servo servo;

const int CLOCK = 10;
const int DATASERIAL = 8;
const int STORAGEREGISTER = 9;

const int PATTERN_NUMBERS [] = {
  B11111100, //0
  B01100000, //1
  B11011010, //2
  B11110010, //3
  B01100110, //4
  B10110110, //5
  B10111110, //6
  B11100000, //7
  B11111110, //8
  B11110110,  //9
};

const int PATTERN_WALK_STOP [] = {
  B01101110, // Stop
  B01101100, // Walk
};

bool ruststand;
int staat;
int huidigeStaat;
const int POORTMIN = 0;
const int POORTMAX = 180;
int poortValue = POORTMIN;
const int INTERVAL_POORT = 5000;
const int BUZZERPIN = 7;

unsigned long currentTime;

void setup() {
  Serial.begin(9600);
  setupShiftRegister();
  setupServo();
  setupLED();
  setupBuzzer();
  showPattern(PATTERN_WALK_STOP[0]);
//  staat = 0;
}

void loop() {
  unsigned long currentTime = millis();
//  Serial.println(staat);
  switch (staat) {
    case 0: //beginstand
//      poortBewegen();
      showPattern(PATTERN_WALK_STOP[0]);
//      ruststand = true;
//      if (ruststand == true) {
//        ruststand = false;
//        staat = 1;
//      }
      break;

    case 1: //Poort openen
      poortBewegen();
      if (poortValue = POORTMAX) {
        staat = 2;
      }
      break;
    case 2:// Poort open
    showPattern(PATTERN_WALK_STOP[1]);
    buzzerLopen();
  }
}

