#include <Servo.h>
Servo servo;

//Shift register
const int CLOCK = 7;
const int DATASERIAL = 5;
const int STORAGEREGISTER = 6;
//

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

const int PATTERN_WALK_STOP [] = {
  B01101110, // Stop
  B01101100, // Walk
};

const int PATTERN_NUMBERS_LENGTH = sizeof(PATTERN_NUMBERS) / sizeof(PATTERN_NUMBERS[0]);
//

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
int T;

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
  Serial.println(staat);
  switch (staat) {
    case 0: //beginstand
      T = 0;
      poortSluiten();
      LED_R_State(1);
      showPattern(PATTERN_WALK_STOP[0]);
      ruststand = true;
      if (ruststand == true && poortValue <= POORTMIN) {
        ruststand = false;
        staat = 1;
        previousTime = currentTime;
      }
      break;

    case 1: //Poort openen
      poortOpenen();
      if (poortValue >= POORTMAX) {
        staat = 2;
        previousTime = currentTime;
      }
      break;
    case 2:// Poort open
      showPattern(PATTERN_WALK_STOP[1]);
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

      case 4://Poort sluiten
      showPattern(PATTERN_WALK_STOP[0]);
      poortSluiten();
      buzzerSluiten();
      if(poortValue <= POORTMIN){
        staat = 0;
        ruststand = true;
      }
  }
}

