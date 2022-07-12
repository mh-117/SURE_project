#include <ArduinoBLE.h>

// modified from the rawDataAdvertising example from 

BLEService myService("fff0");
BLECharacteristic myCharacteristic("fff1", BLERead | BLEBroadcast | BLENotify, 2);  // must add notify for the cloud service to save the data
// note: 2 = allocates 2 x 8 bits in the app

// Advertising parameters should have a global scope. Do NOT define them in 'setup' or in 'loop'
const uint8_t completeRawAdvertisingData[] = {0x02,0x01,0x06,0x09,0xff,0x01,0x01,0x00,0x01,0x02,0x03,0x04,0x05};   
const uint8_t testData[25] = {0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x20,0x21,0x22,0x23,0x24,0x25};
//data in hex (for example) ^^

//data in binary
byte ONE = 0b00000001; 
byte binaryData = 0b00011111;  //8 bits

uint16_t largeBinaryData2 = 0b0000000111001110;

uint32_t largeBinaryData3 = 0b1111111111101110;


void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!BLE.begin()) {
    Serial.println("failed to initialize BLE!");
    while (1);
  }

  
  myService.addCharacteristic(myCharacteristic);
  BLE.addService(myService);

  // Build advertising data packet
  BLEAdvertisingData advData;
  // If a packet has a raw data parameter, then all the other parameters of the packet will be ignored
  advData.setRawData(completeRawAdvertisingData, sizeof(completeRawAdvertisingData));  
  // Copy set parameters in the actual advertising packet
  BLE.setAdvertisingData(advData);

  // Build scan response data packet
  BLEAdvertisingData scanData;
  scanData.setLocalName("Sending Data Test");
  // Copy set parameters in the actual scan response packet
  BLE.setScanResponseData(scanData);

  // this section is important specifically for sending data from the Arduino to the phone
  //myCharacteristic.writeValue(completeRawAdvertisingData, sizeof(completeRawAdvertisingData));
  //myCharacteristic.writeValue(testData,sizeof(testData));
  myCharacteristic.writeValue(largeBinaryData2,sizeof(largeBinaryData2));
  Serial.println(largeBinaryData2,BIN);
  
  BLE.advertise();

  Serial.println("advertising ...");
}

// loop will continuously change the data being sent (here it is just adding 1 each loop) 
void loop() {
  BLE.poll();

  Serial.println("-------");  
  
  largeBinaryData2 = largeBinaryData2 + ONE;  
  Serial.println(largeBinaryData2,BIN);

  myCharacteristic.writeValue(largeBinaryData2,sizeof(largeBinaryData2));

  
  delay(500); // wait 0.5s 
}
