const int CLOCK = 10;
const int DATASERIAL = 8;
const int STORAGEREGISTER = 9;

const int FONT [] = {
  B11111100, //0
  B01100000, //1
  B11011010, //2
  B11110010, //3
  B01100110, //4
  B10110110, //5
  B10111110, //6
  B11100000, //7
  B11111110, //8
  B11110110, //9
};

void setup() {
  setupShiftRegister();

}

void loop() {
  for (int i = 0; i < sizeof(FONT) / sizeof(FONT[0]); i++) {

    showPattern(FONT[i]);
    delay(1000);
  }




}

