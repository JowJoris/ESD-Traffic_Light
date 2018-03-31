void LED_R_State (int staat) {
  if (staat == 1) {
    digitalWrite(13, HIGH);
    digitalWrite(10, HIGH);
  }
  else if (staat == 0) {
    digitalWrite(13, LOW);
    digitalWrite(10, LOW);
  }
}

void LED_Y_State (int staat) {
  if (staat == 1) {
    digitalWrite(12, HIGH);
    digitalWrite(9, HIGH);
  }
  else if (staat == 0) {
    digitalWrite(12, LOW);
    digitalWrite(9, LOW);
  }
}

void LED_G_State (int staat) {
  if (staat == 1) {
    digitalWrite(11, HIGH);
    digitalWrite(8, HIGH);
  }
  else if (staat == 0) {
    digitalWrite(11, LOW);
    digitalWrite(8, LOW);
  }
}

void LED_Y_Blink() {
  LED_Y_State(1);
  delay(500);
  LED_Y_State(0);
  delay(500);
}


