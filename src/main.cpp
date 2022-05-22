#include <Arduino.h>

int incrementAddress1 = 0;
int incrementAddress2 = 1;
int resetAddress = 13;
int romChipEnable = 2;
int romOutEnable = 3;
int romWriteEnable = 4;

int romIO[8] = {5, 6, 7, 8, 9, 10, 11};

void setup()
{
  // put your setup code here, to run once:
  pinMode(incrementAddress1, OUTPUT);
  pinMode(incrementAddress2, OUTPUT);
  pinMode(resetAddress, OUTPUT);
  pinMode(romChipEnable, OUTPUT);
  pinMode(romOutEnable, OUTPUT);
  pinMode(romWriteEnable, OUTPUT);

  for (int i = 0; i < 8; i++)
  {
    pinMode(romIO[i], OUTPUT);
  }

  Serial.begin(9600);
}

void loop()
{
}