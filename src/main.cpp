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
  Serial.begin(9600);
  delay(3000);
  Serial.println("Starting....");
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

  digitalWrite(romChipEnable, LOW);
  digitalWrite(romOutEnable, HIGH);
  digitalWrite(romWriteEnable, HIGH);

  digitalWrite(romIO[0], LOW);
  digitalWrite(romIO[1], LOW);
  digitalWrite(romIO[2], LOW);
  digitalWrite(romIO[3], LOW);
  digitalWrite(romIO[4], LOW);
  digitalWrite(romIO[5], LOW);
  digitalWrite(romIO[6], LOW);
  digitalWrite(romIO[7], LOW);
  delay(100);
  digitalWrite(romWriteEnable, LOW);
  delay(100);
  digitalWrite(romWriteEnable, HIGH);
}

void loop()
{
  for (int i = 0; i < 8; i++)
  {
    pinMode(romIO[i], INPUT);
  }

  digitalWrite(romOutEnable, LOW);
  delay(10);
  for (int i = 0; i < 8; i++)
  {
    Serial.print(digitalRead(romIO[i]));
  }
  Serial.print("\n");
  delay(200);
}