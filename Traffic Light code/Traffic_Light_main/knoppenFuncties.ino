void checkInput() {
  int incommingRead;
  for (int i = 0; i < sizeof(KNOPPEN) / sizeof(KNOPPEN[0]); i++) {
    incommingRead = analogRead(KNOPPEN[i]);
    if (incommingRead == 1) {
      //      Serial.println(KNOPPEN[i]);
      checkArray(KNOPPEN[i]);
    }
  }
}

void checkArray(int knop) {
  for (int i = 0; i < sizeof(KNOPPEN) / sizeof(KNOPPEN[0]); i++) {
    if (knoppenIngedrukt[i] == knop) {
      break;
    }
    else if (knoppenIngedrukt[i] == 0) {
      knoppenIngedrukt[i] = knop;
      Serial.println(i);
      Serial.println(knop);
      break;
    }
  }
}

void schuifArrayDoor() {
  for (int i = 1; i < sizeof(KNOPPEN) / sizeof(KNOPPEN[0]); i++) {
    knoppenIngedrukt[i - 1] = knoppenIngedrukt[i];
  }
  knoppenIngedrukt[(sizeof(KNOPPEN) / sizeof(KNOPPEN[0])) - 1] = 0;
  for (int i = 0; i < sizeof(knoppenIngedrukt) / sizeof(knoppenIngedrukt[0]); i++) {
    Serial.println(knoppenIngedrukt[i]);
  }
}

