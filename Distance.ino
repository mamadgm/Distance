#include <TM1637Display.h>
#include <PinButton.h>
#include <NewPing.h>

// Define pins for TM1637 Display
#define CLK 12
#define DIO 11

// Define pins for IR sensor
#define IR_DIGITAL_PIN A2
#define IR_ANALOG_PIN A3

// Define pins for SR05 sensor
#define TRIGGER_PIN 4
#define ECHO_PIN 3

// Define pin for the push button
#define BUTTON_PIN 13

// Create display object
TM1637Display display(CLK, DIO);

// Create PinButton object
//PinButton button(BUTTON_PIN);

// Create NewPing object for SR05 sensor
NewPing sonar(TRIGGER_PIN, ECHO_PIN, 200); // Set maximum distance to 200 cm

// Variables to store distance values
int distanceSR05 = 0;
int distanceIR = 0;
bool useSR05 = false; // Start with SR05 sensor

void setup() {
  pinMode(13 , INPUT_PULLUP);
  display.setBrightness(0x0f); // Set brightness for TM1637 display
  Serial.begin(9600); // Initialize serial communication
//  butto n.setup(); // Initialize button
}

void loop() {
  if(digitalRead(13) == LOW){
    useSR05 = !useSR05;
    delay(200);
  }

  // Measure distance using SR05 sensor
  if (useSR05) {
    distanceSR05 = sonar.ping();
    display.showNumberDec(distanceSR05); // Display SR05 distance on TM1637
    Serial.println("SR05 Distance: " + String(distanceSR05) + " cm");
  } 
  // Measure distance using IR sensor
  else {
    distanceIR = analogRead(IR_ANALOG_PIN);
    display.showNumberDec(distanceIR); // Display IR distance on TM1637
    Serial.println("IR Distance: " + String(distanceIR) + " cm");
  }

  delay(100); // Small delay to avoid too frequent updates
}
