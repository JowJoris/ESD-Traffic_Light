void poortOpenen () {
  if (currentTime - previousTime >= POORTDELAY) {
    if(poortValue < POORTMAX){
  poortValue++;
  servo.write(poortValue);
  previousTime = currentTime;
    }
  }
}

void poortSluiten() {
  if (currentTime - previousTime >= POORTDELAY) {
    if(poortValue > POORTMIN){
  poortValue--;
  servo.write(poortValue);
  previousTime = currentTime;
    }
  }
}


