#include <RFduinoBLE.h>

#define beepPin 2
#define buttonPin 6

void setup()
{
	
	Serial.begin(9600);
	
	pinMode(beepPin, OUTPUT);
	pinMode(buttonPin, INPUT);
  
  RFduinoBLE.advertisementData = "rfAd";
  RFduinoBLE.txPowerLevel = -20;
  RFduinoBLE.deviceName = "RFduino";
	RFduinoBLE.begin();
 
	tone(beepPin, 500, 200);
	Serial.println("RFduino BLE stack started");
}

void loop() {

}

void RFduinoBLE_onAdvertisement()
{
  Serial.println("RFduino is doing BLE advertising ..."); 
}

void RFduinoBLE_onConnect()
{
	Serial.println("RFduino BLE connection successful");
	tone(beepPin, 1000, 200);
}

void RFduinoBLE_onDisconnect()
{
	Serial.println("RFduino BLE disconnected");
}

void RFduinoBLE_onReceive(char *data, int len)
{
	// if the first byte is 0x01 / on / true
	Serial.println("Received data over BLE");
	if (data[0])
	{
		tone(beepPin, 1000);
		Serial.println("tone on");
	}
	else
	{
		noTone(beepPin);
		Serial.println("tone off");
	}
}
