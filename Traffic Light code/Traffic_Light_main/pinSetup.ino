//ShiftRegister

void setupShiftRegister () {
  pinMode(CLOCK, OUTPUT);
  pinMode(DATASERIAL, OUTPUT);
  pinMode(STORAGEREGISTER, OUTPUT);
}

//Servo

void setupServo() {
  const int SERVOPIN = 4;
  servo.attach(SERVOPIN);
}

//LEDs
void setupLED() {
  const int LEDS [] = {13, 12, 11, 10, 9, 8};
  for (int i = 0; i < sizeof(LEDS) / sizeof(LEDS[0]); i++) {
    pinMode(LEDS[i], OUTPUT);
  }
}

//Buzzer
void setupBuzzer() {
  pinMode(BUZZERPIN, OUTPUT);
}

//LDR
void setupLDR() {
  pinMode(LDRPin + 14, INPUT);
}



