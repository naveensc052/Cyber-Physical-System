#include <Wire.h>
#include "SSD1306Wire.h"
#include <SPI.h>
#define BUZZER_PIN 2 //D4 PIN
#define ECHO_PIN 14 //D5 PIN
#define TRIGGER_PIN 12 //D6 PIN
#define SDA_PIN 4 //D1 PIN
#define SCL_PIN 5 //D2 PIN
#define DISTANCE_THRESHOLD 10

// OLED display and I2C address
SSD1306Wire display(0x3c,SCL_PIN , SDA_PIN);

void setup() {
  // Initialize OLED display
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);

  // Initialize ultrasonic sensor pins
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Initialize buzzer pin
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  // Send a pulse to the trigger pin
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  // Measure the duration of the pulse on the echo pin
  long duration = pulseIn(ECHO_PIN, HIGH);

  // Calculate the distance in centimeters using the speed of sound
  int distance = duration / 58.2;

  // Display the distance on the OLED display
  display.clear();
  display.drawString(0, 0, "Distance: " + String(distance) + " cm");
  display.display();

  // If the distance is below the threshold, turn on the buzzer
  if (distance < DISTANCE_THRESHOLD) {
    digitalWrite(BUZZER_PIN, HIGH);
  } else {
    digitalWrite(BUZZER_PIN, LOW);
  }

  // Wait a moment before measuring again
  delay(100);
}
