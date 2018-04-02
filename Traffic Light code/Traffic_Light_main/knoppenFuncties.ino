void checkInput() {
  int incommingRead;
  for (int i = 0; i < sizeof(KNOPPEN) / sizeof(KNOPPEN[0]); i++) {
    incommingRead = analogRead(KNOPPEN[i]);
    if (incommingRead == 1) {
      Serial.println(KNOPPEN[i]);
    }
  }
}

