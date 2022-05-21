#include <Arduino.h>

int incermentAddr1 = 0;
int incermentAddr2 = 1;
int reset = 13;
int chipEnable = 2;
int outEnable = 3;
int writeEnable = 4;

int dataIO[8] = {5, 6, 7, 8, 9, 10, 11};

void setup()
{
  // put your setup code here, to run once:
  pinMode(incermentAddr1, OUTPUT);
  pinMode(reset, OUTPUT);
  digitalWrite(reset, LOW);
}

void loop()
{
  // put your main code here, to run repeatedly:
  digitalWrite(incermentAddr1, HIGH);
  delay(1);
  digitalWrite(incermentAddr1, LOW);
  delay(1);
}