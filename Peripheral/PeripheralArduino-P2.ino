/*********************************************************************
 
 The following code is built from the SerialPassThrough example from the
 HardwareBLESerial library: https://github.com/Uberi/Arduino-HardwareBLESerial
 File->Examples->HardwareBLESerial->SerialPassThrough


*********************************************************************/
#include <HardwareBLESerial.h>
#include <ArduinoBLE.h>

HardwareBLESerial &bleSerial = HardwareBLESerial::getInstance();


// data in binary 
//uint8_t startData = 0b00000100;
uint16_t startData = 0b1111000000000000;
byte ONE = 0b00000001; 

boolean startCmdRec = false;
boolean masterStart = false;
String command = "";
String masterCommand = "";

void setup() {
  Serial.begin(9600);
  while (!Serial);
  
  if (!bleSerial.beginAndSetupBLE("P2")) {
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

  // ----------------START COMMAND: ARDUINO NANO <- ADAFRUIT BLUEFRUIT----------------
  // wait to send data until the Bluefruit requests it
  Serial.println("Waiting to be told to send data...");


  while (!startCmdRec) {
    bleSerial.poll();

    // read command written to BLE UART 
    while (bleSerial.available() > 0) {
      int asciiNum = bleSerial.read();
      if (asciiNum != 10) {
        command = command + (char)asciiNum;
      }     
    }
    
    // need to change P# according to what I'm coding 
    if (command == "P2") {
      startCmdRec = true;
      /*
      bleSerial.println("P2 is ready...");
      while (!masterStart) {
        bleSerial.poll();

        // read command written to BLE UART 
        while (bleSerial.available() > 0) {
          int asciiNum = bleSerial.read();
          if (asciiNum != 10) {
            masterCommand = masterCommand + (char)asciiNum;
          }     
        }
        if (masterCommand == "start") {
          startCmdRec = true;
        }
        masterCommand = "";
      }
      */
    }

    command = "";
    masterCommand = "";
  }
  // empty the command variable to make room for a new value
  command = "";
  masterCommand = "";
  Serial.println("P2: Sending data...");
 

  // ----------------DATA SENDING: ARDUINO NANO-> ADAFRUIT BLUEFRUIT----------------
  Serial.println("-------");  

  // series of data
  //startData = startData + ONE;        //increment data
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

  char dataFinal[dataLen+1];
  for (int i = 0; i < dataLen; i++) {
    dataFinal[i] = dataStr[i];
  }
  dataFinal[dataLen] = ' ';
  dataFinal[dataLen+1] = '\0';
  Serial.println("Uploading through bleuart...");
  
  bleSerial.print(dataFinal);
  bleSerial.println((double)BLE.rssi());

  checkRSSI();
  
  // ----------------START COMMAND: ARDUINO NANO <- ADAFRUIT BLUEFRUIT----------------
  // read command written to BLE UART 
  while (bleSerial.available() > 0) {
    int asciiNum = bleSerial.read();
    if (asciiNum != 10) {
      command = command + (char)asciiNum;
    } 
  }
  if (command == "stop") {
    startCmdRec = false;
    masterStart = false;
    Serial.println("Stopping data transmission...");
  }
  
  // empty the command variable to make room for a new value
  command = "";
  delay(1000);
}


void checkRSSI() {
  int rssiVal = BLE.rssi();
  if (rssiVal == 0) {
    Serial.println("RSSI = 0");
  }
  return;
}
