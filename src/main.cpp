#include <Arduino.h>

uint8_t incrementAddress1 = 13;
uint8_t incrementAddress2 = A5;
uint8_t resetAddress = A2;
uint8_t romChipEnable = 2;
uint8_t romOutEnable = 3;
uint8_t romWriteEnable = 4;

uint8_t romIO[8] = { 5, 6, 7, 8, 9, 10, 11, 12 };

uint16_t currentAddress;


void writeToRom(uint8_t data) {

  digitalWrite(romOutEnable, HIGH);
  digitalWrite(romWriteEnable, LOW);

  for (uint8_t i = 0; i < 8; i++) {
    pinMode(romIO[i], OUTPUT);
  }
  delay(1);

  for (int8_t i = 8; i >= 0; i--) {
    if (data % 2 == 1) {
      digitalWrite(romIO[i], HIGH);
    } else {
      digitalWrite(romIO[i], LOW);
    }
    data = data >> 1;
    //delay(1000);
  }

  digitalWrite(romWriteEnable, LOW);
  delay(10);
  digitalWrite(romWriteEnable, HIGH);

  for (uint8_t i = 0; i < 8; i++) {
    digitalWrite(romIO[i], LOW);
  }

  digitalWrite(romWriteEnable, HIGH);
}

uint8_t readFromRom() {
  uint8_t reading;

  digitalWrite(romOutEnable, LOW);
  digitalWrite(romWriteEnable, HIGH);


  for (uint8_t i = 0; i < 8; i++) {
    pinMode(romIO[i], INPUT);
  }

  for (uint8_t i = 0; i < 8; i++) {
    //Serial.print(digitalRead(romIO[i]));
    if (digitalRead(romIO[i])) {
      reading++;
    }
    reading = reading << 1;
  }
  return reading;
}

void incrementAddress() {

  for (int i = 0; i < 4; i++) {
    digitalWrite(incrementAddress1, HIGH);
    delay(1);
    digitalWrite(incrementAddress1, LOW);
  }

  if ((0b1111111 & currentAddress) == 0b1111111) {
    for (int i = 0; i < 4; i++) {
      digitalWrite(incrementAddress2, HIGH);
      delay(1);
      digitalWrite(incrementAddress2, LOW);
    }
  }

  currentAddress++;
}

void clearAddress() {
  digitalWrite(resetAddress, HIGH);
  delay(10);
  digitalWrite(resetAddress, LOW);
  currentAddress = 0;
}

void setup() {
  delay(1000);
  Serial.begin(115200, SERIAL_8E1);

  Serial.println("Starting....");
  // put your setup code here, to run once:
  pinMode(incrementAddress1, OUTPUT);
  pinMode(incrementAddress2, OUTPUT);
  pinMode(resetAddress, OUTPUT);
  pinMode(romChipEnable, OUTPUT);
  pinMode(romOutEnable, OUTPUT);
  pinMode(romWriteEnable, OUTPUT);


  digitalWrite(incrementAddress1, LOW);
  digitalWrite(incrementAddress2, LOW);


  clearAddress();

  digitalWrite(romChipEnable, LOW);
  delay(10);

  Serial.println("r");
}

void loop() {

  if (Serial.available() > 0) {
    String command = Serial.readString();

    if (command.charAt(0) == 'w') {
      for (uint8_t i = 1; i < command.length();i++) {
        writeToRom(command.charAt(i));
        incrementAddress();
      }

      Serial.println("r");
    }

  }

  // writeToRom(0xaa);
  // delay(5000);
  // Serial.print(readFromRom(), BIN);
  // for (int i = 0; i < 4; i++) {
  //   digitalWrite(incrementAddress1, HIGH);
  //   delay(10);
  //   digitalWrite(incrementAddress1, LOW);
  // }
  // Serial.println("\n");
  // delay(100);
}