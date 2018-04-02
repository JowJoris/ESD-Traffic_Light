void buzzerLopen() {
  tone(BUZZERPIN, 1000);
  delay(1000);
  noTone(BUZZERPIN);
  delay(1000);
}

void buzzerCountdown() {
  for (int i = 0; i < 3; i++) {
    tone(BUZZERPIN, 4000);
    delay(50);
    noTone(BUZZERPIN);
    delay(50);
  }
  noTone(BUZZERPIN);
  delay(3000);

}

void buzzerSluiten() {

}

void buzzerNacht() {

}

