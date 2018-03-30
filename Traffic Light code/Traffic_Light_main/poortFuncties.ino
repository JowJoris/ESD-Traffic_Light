void poortOpenen () {
  if (currentTime - previousTime >= POORTDELAY) {
  poortValue++;
  servo.write(poortValue);
  previousTime = currentTime;
  }
}

void poortSluiten() {
  if (currentTime - previousTime >= POORTDELAY) {
  poortValue--;
  servo.write(poortValue);
  previousTime = currentTime;
  }
}


