void showPattern (byte PATTERN) {
  for (int i = 0; i < 8; i++) {
    digitalWrite(CLOCK, LOW);
    if (PATTERN & (B00000001 << i)) {
      digitalWrite(DATASERIAL, HIGH);
    }
    else {
      digitalWrite (DATASERIAL, LOW);
    }
    digitalWrite(CLOCK, HIGH);
  }

  digitalWrite(STORAGEREGISTER, HIGH);
  digitalWrite(STORAGEREGISTER, LOW);


}

void patternCountdown() {
  if (currentTime -  previousTime >= 1000) {
    showPattern(PATTERN_NUMBERS[iCountdown-1]);
    iCountdown--;
    Serial.println(iCountdown);
    previousTime = currentTime;
  }
}

