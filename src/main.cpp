#include <Arduino.h>

uint8_t incrementAddress1 = A2;
uint8_t incrementAddress2 = A5;
uint8_t resetAddress = 13;
uint8_t romChipEnable = 2;
uint8_t romOutEnable = 3;
uint8_t romWriteEnable = 4;

uint8_t romIO[8] = {5, 6, 7, 8, 9, 10, 11, 12};

void writeToRam(uint8_t data)
{

  for (uint8_t i = 0; i < 8; i++)
  {
    pinMode(romIO[i], OUTPUT);
  }

  for (uint8_t i = 0; i < 8; i++)
  {
    Serial.println(data % 2);
    if (data % 2 == 0)
    {
      digitalWrite(romIO[i], HIGH);
    }
    else
    {
      digitalWrite(romIO[i], LOW);
    }
    data = data >> 1;
  }

  delay(5000);
  digitalWrite(romWriteEnable, LOW);
  delay(5000);
  digitalWrite(romWriteEnable, HIGH);

  for (uint8_t i = 0; i < 8; i++)
  {

    digitalWrite(romIO[i], LOW);
  }
}

void setup()
{
  Serial.begin(9600);
  delay(3000);
  uint8_t test = 8;
  test = test >> 2;
  Serial.println(test);
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
  delay(100);

  writeToRam(0b00000000);

  for (uint8_t i = 0; i < 8; i++)
  {
    pinMode(romIO[i], INPUT);
  }

  digitalWrite(romOutEnable, LOW);
}

void loop()
{

  delay(10);
  for (uint8_t i = 0; i < 8; i++)
  {
    Serial.print(digitalRead(romIO[i]));
  }
  Serial.println("\n");
  delay(200);
}