#include <ArduinoBLE.h>

// modified from the rawDataAdvertising example from 
/**********************************************************

This code initiates a connection between the Arduino Nano and 
the LightBlue Bluetooth App

- Continuous flow of data (that increments every second) from 
the nano
- Sends a notification to the phone app that values are changing
- Nano can receive a command from the LightBlue app to indicate
when the device should start sending data over bluetooth

**********************************************************/

BLEService myService("fff0");
BLECharacteristic myCharacteristic("fff1", BLERead | BLEBroadcast | BLENotify, 2);  // must add notify for the cloud service to save the data
BLEByteCharacteristic myCharacteristic2("fff2", BLEWrite | BLERead);
// note: 2 = allocates 2 x 8 bits in the app

// Advertising parameters should have a global scope. Do NOT define them in 'setup' or in 'loop'
const uint8_t completeRawAdvertisingData[] = {0x02,0x01,0x06,0x09,0xff,0x01,0x01,0x00,0x01,0x02,0x03,0x04,0x05};   
const uint8_t testData[25] = {0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x20,0x21,0x22,0x23,0x24,0x25};
//data in hex (for example) ^^

//data in binary
byte ONE = 0b00000001; 
byte binaryData = 0b00011111;  //8 bits

uint16_t largeBinaryData2 = 0b0000000111001110;
uint16_t startData = 0b0000000000000000;

uint32_t largeBinaryData3 = 0b1111111111101110;

// Command to send
boolean newProgram = true;
boolean startCmd = false;
boolean stopCmd = false;
uint8_t commandValue = 0;


void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!BLE.begin()) {
    Serial.println("failed to initialize BLE!");
    while (1);
  }

  
  myService.addCharacteristic(myCharacteristic);
  myService.addCharacteristic(myCharacteristic2);
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
  // ----------------INITIALIZING CHARACTERISTICS----------------
  //myCharacteristic.writeValue(completeRawAdvertisingData, sizeof(completeRawAdvertisingData));
  //myCharacteristic.writeValue(testData,sizeof(testData));
  myCharacteristic.writeValue(startData,sizeof(startData));
  Serial.println(startData,BIN);

  // set the initial value for the characeristic:
  myCharacteristic2.writeValue((byte)0x00);
  
  BLE.advertise();

  Serial.println("Advertising ...");
}

// loop will continuously change the data being sent (here it is just adding 1 each loop) 
void loop() {
  BLE.poll();

  // listen for Bluetooth® Low Energy peripherals to connect:
  BLEDevice central = BLE.central();

  //first wait until board connects to phone (should only go through this set of code when the program has just begun)
  if(newProgram) {
    Serial.println("Waiting to connect to board...");
    newProgram = false;
  }
  
  while (!central) {
    BLE.poll();
    central = BLE.central();
    if(central) {
      Serial.println("Connected to central...");    
    }
  }
  
   // ----------------START COMMAND---------------- we want the code to pause before starting to send data 
  // if a central is connected to peripheral:
  if (central) {
    
    // only wait for start command if it is the start of a new data collection cycle (ie startCmd = false)
    while (!startCmd) {  
      BLE.poll();
      // continue looping until start command is sent
      if (myCharacteristic2.written()) {
        myCharacteristic2.readValue(commandValue);
        Serial.print("Command sent: " ); 
        Serial.println(commandValue);
        if (commandValue == 7) {   
          Serial.println("Command received");
          startCmd = true;
          commandValue = 0;
        }
      }
    }
  }


  // ----------------DATA SENDING: BOARD -> PHONE----------------
  Serial.println("-------");  

  // series of data
  //startData = startData + ONE;  
  startData = 0b0000000111001110;   //just repeatedly sending this one piece of data
  Serial.println(startData,BIN);

  myCharacteristic.writeValue(startData,sizeof(startData));
  
  //delay(500); // wait 0.5s 
  delay(1000); //wait 1s
  
}
