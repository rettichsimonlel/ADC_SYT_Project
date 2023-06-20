#include <SPI.h>
#include <Arduino.h>

const int SSPIN = 5;  // Define the slave select pin (SS) on the slave Arduino

void setup() {
  SPI.begin();    // Initialize SPI communication
  pinMode(SSPIN, INPUT);    // Set SS pin as input
  Serial.begin(9600);   // Initialize the serial communication
}

void loop() {
  if (digitalRead(SSPIN) == LOW) {   // Check if the slave device is selected
    uint8_t receivedChar1 = SPI.transfer(0);   // Receive the first character

    // Print the received message
    Serial.print("Received message: ");
    Serial.println(receivedChar1);

    // Add any required processing or response logic here

  }
  else {
    uint8_t receivedChar1 = SPI.transfer(0);   // Receive the first character

    // Print the received message
    Serial.print("Received HIGH message: ");
    Serial.println(receivedChar1);
  }
  delay(100);   // Small delay to avoid reading the message multiple times
}

