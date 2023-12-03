#include <Wire.h>
#include <OneWire.h>
#include <BLEDevice.h> 
#include <BLEUtils.h>
#include <BLEServer.h>

#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "bbb5483e-36e1-4688-b7f5-ea07361b26a8" 
BLEService *pService;
BLECharacteristic *tempCharacteristic;
 BLECharacteristic *pressureCharacteristic; 
 BLECharacteristic *luminosityCharacteristic;

void setup()
{
Serial.begin(115200);
BLEDevice::init("Esp32 test BLE");
BLEServer *pServer = BLEDevice::createServer();
pService = pServer->createService("181A");
luminosityCharacteristic = pService->createCharacteristic( CHARACTERISTIC_UUID, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE );
pService->start();
BLEAdvertising *pAdvertising = BLEDevice::getAdvertising(); 
pAdvertising->addServiceUUID("181A"); 
pAdvertising->setScanResponse(true); 
pAdvertising->setMinPreferred(0x06); 
pAdvertising->setMinPreferred(0x12); 
BLEDevice::startAdvertising();
Serial.println("Characteristic defined!");
}

void loop()
{
int luminosity = analogRead(33); 
Serial.print(luminosity); 
Serial.println("");
char luminosityString [5];
dtostrf (luminosity, 1, 2, luminosityString); 
luminosityString[4] = '\0';
luminosityCharacteristic-> setValue (luminosityString);
Serial.println(luminosityString);
Serial.println(); 
delay(5000);
}
