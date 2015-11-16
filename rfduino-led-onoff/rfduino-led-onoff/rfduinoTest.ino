#include <RFduinoBLE.h>

//#define BEEP_PIN   2
#define LED_PIN 6
#define BUTTON_PIN 2

int ledState = HIGH;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() {
  //  pinMode(BEEP_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);

  Serial.begin(9600);

  //  tone(BEEP_PIN, 200, 100);

}

void loop() {
  int reading = digitalRead(BUTTON_PIN);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == HIGH) {
        //        tone(BEEP_PIN, 262);
        digitalWrite(LED_PIN, HIGH);
        Serial.println("button pressed");
      } else {
        //        noTone(BEEP_PIN);
        digitalWrite(LED_PIN, LOW);
      }
    }
  }
  lastButtonState = reading;
}

