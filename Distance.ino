#include <NewPing.h>
#include <PinButton.h>
#include <TM1637Display.h>
#include <VL6180X.h>
#include <Wire.h>

#define CLK 12
#define DIO 11
#define IR_DIGITAL_PIN A3
#define IR_ANALOG_PIN A2
#define TRIGGER_PIN 4
#define ECHO_PIN 3
#define BUTTON_PIN 13

// All Objects
TM1637Display display(CLK, DIO);
NewPing sonar(TRIGGER_PIN, ECHO_PIN);
VL6180X sensor;

// Variables to store distance values
int distanceSR05 = 0;
int distanceIR = 0;
int distanceVL = 0;
int WhichSensor = 0;  // Start with SR05 sensor

void setup() {
  Wire.begin();
  sensor.init();
  sensor.configureDefault();
  sensor.setTimeout(500);
  pinMode(13, INPUT_PULLUP);
  display.setBrightness(1);  // Set brightness for TM1637 display
  Serial.begin(115200);        // Initialize serial communication
}

void loop() {
  if (digitalRead(13) == LOW) {
    WhichSensor++;
    delay(200);
  }
  switch (WhichSensor) {
    case 0:
      distanceSR05 = sonar.ping_cm();
      display.showNumberDec(distanceSR05);  // Display SR05 distance on TM1637
      Serial.println("SR05 Distance: " + String(distanceSR05) + " cm");
      break;
    case 1:
      if (digitalRead(A3) == LOW) {
        display.showNumberDec(8888);
      } else {
        distanceIR = analogRead(IR_ANALOG_PIN);
        display.showNumberDec(distanceIR);  // Display IR distance on TM1637
        Serial.println("IR Distance: " + String(distanceIR));
      }
      break;
    case 2:
      distanceVL = sensor.readRangeSingleMillimeters();
      display.showNumberDec(distanceVL);
      Serial.println("VL" + String(distanceVL));
      break;

    default:
      WhichSensor = 0;
      break;
  }

  delay(100);
}
