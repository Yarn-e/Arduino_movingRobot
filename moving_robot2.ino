// Including libraries
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <RH_ASK.h>
#include <SPI.h>
#include <Adafruit_LSM9DS1.h>
#include <Adafruit_Sensor.h>

// Distance sensor global
float distanceCm;

void setup() {
  Serial.begin(9600);
  setupDisplay();
  setupMotor();
  setupComm();
  
  setupDistance();
  distanceCm = calculateDistance();

  setupPosition();
}

void loop() {
  checkMessage();
  distanceCm = calculateDistance();
}

