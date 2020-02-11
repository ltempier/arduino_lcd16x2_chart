
#include <LiquidCrystal.h>

LiquidCrystal lcd =  LiquidCrystal (8, 9, 4, 5, 6, 7);


void setup() {
  lcd.begin(16, 2);
}

int x = 0;

void loop() {
  float data[40];
  for (int i = 0; i < 40; i++) {
    data[i] = sin((x++) / 5.0) * 100;
  }
  drawGraph(data);
  delay(400);
}

void drawGraph(float data[40]) {

  float minValue = 0;
  float maxValue = data[0];

  for (byte i = 0; i < 40; i++) {
    if (data[i] > maxValue)
      maxValue = data[i];
    if (data[i] < minValue)
      minValue = data[i];
  }

  int mappedData[40];
  for (byte i = 0; i < 40; i++) {
    mappedData[i] = map(data[i], minValue, maxValue, 1, 7);
  }

  lcd.clear();
  for (int iLcd = 0; iLcd < 8; iLcd++) {

    byte customChar[8];
    for (byte j = 0; j < 8; j++) {
      int bufferInt = 0;
      for (byte i = 0 ; i < 5; i++) {
        int pixelValue = mappedData[iLcd * 5 + i];
        if (pixelValue >= 8 - j)
          bitWrite(bufferInt, 4 - i, 1);
        else
          bitWrite(bufferInt, 4 - i, 0);
      }
      customChar[j] = (byte) bufferInt;
    }
    lcd.createChar((byte)iLcd, customChar);
  }

  lcd.begin(16, 2);
  for (byte iLcd = 0; iLcd < 8; iLcd++) {
    lcd.write((byte)iLcd);
  }
}
