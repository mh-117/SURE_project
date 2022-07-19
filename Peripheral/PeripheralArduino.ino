/*********************************************************************
 
 The following code is built from the SerialPassThrough example from the
 HardwareBLESerial library: https://github.com/Uberi/Arduino-HardwareBLESerial
 File->Examples->HardwareBLESerial->SerialPassThrough
 
 
 This code initiates a bluetooth connection with the Adafruit Bluefruit
 hardware.
 
 - Define device name in the beginAndSetup function
 - Send data (data must be in a string form for the bluefruit to be able
 to receive it)


*********************************************************************/
#include <HardwareBLESerial.h>

HardwareBLESerial &bleSerial = HardwareBLESerial::getInstance();


// data in binary 
//uint8_t startData = 0b00000100;
uint16_t startData = 0b0000000000000000;
byte ONE = 0b00000001; 

void setup() {
  Serial.begin(9600);
  while (!Serial);
  
  if (!bleSerial.beginAndSetupBLE("Arduino (Peripheral)")) {
    while (true) {
      Serial.println("Failed to initialize HardwareBLESerial!");
      delay(1000);
    }
  }

  // wait for a central device to connect
  while (!bleSerial);

  Serial.println("HardwareBLESerial central device connected!");
}

void loop() {
  // this must be called regularly to perform BLE updates
  bleSerial.poll();


  
  // figure out how to stop sending data when it is not connected 

  
  Serial.println("Uploading through bleuart...");

  
  //bleSerial.write(startData);   // trying to write some data



  // ----------------DATA SENDING: ARDUINO NANO-> ADAFRUIT BLUEFRUIT----------------
  Serial.println("-------");  

  // series of data
  startData = startData + ONE;        //increment data
  Serial.println(startData,BIN);

  // Convert data to a string
  // move all bits into individual slots of the data buffer
  int dataLen = sizeof(startData) * 8;
  int buff[dataLen];  // data buffer
  String dataStr;
  int j = 0;
  for (int i = dataLen - 1; i >= 0; i--) {     // (note: bitRead() starts from LSB) (using bitRead() : https://www.arduino.cc/reference/en/language/functions/bits-and-bytes/bitread/)
    buff[j] = bitRead(startData,i);
    dataStr = dataStr + buff[j];
    j++;
  }

  char dataFinal[dataLen];
  for (int i = 0; i < dataLen; i++) {
    dataFinal[i] = dataStr[i];
  }
  Serial.println("Uploading through bleuart...");
  
  bleSerial.print(dataFinal);



  delay(500);
}
