void poortBewegen() {
  const int beweegTijd = 3000;
  switch (staat) {
    case 0:
      for (int i = 180; i > 0; i--) {
        servo.write(i);
        delay(beweegTijd / 180);
      }
      break;
    case 1:
      for (int i = 0; i < 180; i++) {
        servo.write(i);
        delay(beweegTijd / 180);
      }
      break;

  }
}


