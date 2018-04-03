void LED_R_State (int staat) {
  if (staat == 1) {
    if (knoppenIngedrukt[0] == 3) {
      digitalWrite(13, HIGH);
    }
    else if (knoppenIngedrukt[0] == 5) {
      digitalWrite(10, HIGH);
    }
    else {
      digitalWrite(13, HIGH);
      digitalWrite(10, HIGH);
    }
  }
  else if (staat == 0) {
    if (knoppenIngedrukt[0] == 3) {
      digitalWrite(13, LOW);
    }
    else if (knoppenIngedrukt[0] == 5) {
      digitalWrite(10, LOW);
    }
    else {
      digitalWrite(13, LOW);
      digitalWrite(10, LOW);
    }
  }
}

void LED_Y_State (int staat) {
  if (staat == 1) {
    if (knoppenIngedrukt[0] == 3) {
      digitalWrite(12, HIGH);
    }
    else if (knoppenIngedrukt[0] == 5) {
      digitalWrite(9, HIGH);
    }
    else {
      digitalWrite(12, HIGH);
      digitalWrite(9, HIGH);
    }
  }
  else if (staat == 0) {
    if (knoppenIngedrukt[0] == 3) {
      digitalWrite(12, LOW);
    }
    else if (knoppenIngedrukt[0] == 5) {
      digitalWrite(9, LOW);
    }
    else {
      digitalWrite(12, LOW);
      digitalWrite(9, LOW);
    }
  }
}

void LED_G_State (int staat) {
  if (staat == 1) {
    if (knoppenIngedrukt[0] == 3) {
      digitalWrite(11, HIGH);
    }
    else if (knoppenIngedrukt[0] == 5) {
      digitalWrite(8, HIGH);
    }
  }
  else if (staat == 0) {
    if (knoppenIngedrukt[0] == 3) {
      digitalWrite(11, LOW);
    }
    else if (knoppenIngedrukt[0] == 5) {
      digitalWrite(8, LOW);
    }
  }
}

void LED_Y_Blink() {
  LED_Y_State(1);
  delay(500);
  LED_Y_State(0);
  delay(500);
}


