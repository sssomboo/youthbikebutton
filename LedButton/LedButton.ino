#include <RFduinoBLE.h>

int led = 2;
int button = 6;
int debounce_time = 10;
int debounce_timeout = 100;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(button, INPUT);
  RFduinoBLE.advertisementData = "ledbtn";
  RFduinoBLE.begin();
}

int debounce(int state)
{
  int start = millis();
  int debounce_start = start;
  while (millis() - start < debounce_timeout)
    if (digitalRead(button) == state)
    {
      if (millis() - debounce_start >= debounce_time)
        return 1;
    }
    else
      debounce_start = millis();
  return 0;
}

int delay_until_button(int state)
{
  if (state)
    RFduino_pinWake(button, HIGH);
  else
    RFduino_pinWake(button, LOW);
    
  do
    RFduino_ULPDelay(INFINITE);
  while (! debounce(state));
  if (RFduino_pinWoke(button))
  {
    // execute code here
    RFduino_resetPinWake(button);
  }
}

void loop() {
  delay_until_button(HIGH);
  RFduinoBLE.send(1);
  
  delay_until_button(LOW);
  RFduinoBLE.send(0);
}

void RFduinoBLE_onDisconnect()
{
  noTone(led);
}
  
void RFduinoBLE_onReceive(char *data, int len)
{
  // if the first byte is 0x01 / on / true
  if (data[0])
    tone(led, 1000, 200);
  else
    noTone(led);
}
