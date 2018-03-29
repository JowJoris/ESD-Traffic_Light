//ShiftRegister

void setupShiftRegister () {
  pinMode(CLOCK, OUTPUT);
  pinMode(DATASERIAL, OUTPUT);
  pinMode(STORAGEREGISTER, OUTPUT);
  Serial.println("ShiftRegister setup:  SUCCES");
}

//Servo

void setupServo() {
  const int SERVOPIN = 4;
  servo.attach(SERVOPIN);
  Serial.println("Servo setup:          SUCCES");
}

void setupLED() {
  const int LEDS []= {13, 12, 11, 10, 9, 8, 7};
  for (int i = 0; i < sizeof(LEDS) / sizeof(LEDS[0]); i++) {
    pinMode(i, OUTPUT);
  }
  Serial.println("LED setup:            SUCCES");
}

void setupBuzzer() {
  pinMode(BUZZERPIN, OUTPUT);
  Serial.println("Buzzer setup:         SUCCES");
}

