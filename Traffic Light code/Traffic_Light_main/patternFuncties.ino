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
  for (int i = PATTERN_NUMBERS_LENGTH-1; i >= 0; i--) {
    showPattern(PATTERN_NUMBERS[i]);
    delay(1000);
  }
}

