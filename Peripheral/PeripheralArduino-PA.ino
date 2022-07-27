/*********************************************************************
 
 The following code is built from the SerialPassThrough example from the
 HardwareBLESerial library: https://github.com/Uberi/Arduino-HardwareBLESerial
 File->Examples->HardwareBLESerial->SerialPassThrough


*********************************************************************/
#include <HardwareBLESerial.h>
#include <ArduinoBLE.h>

HardwareBLESerial &bleSerial = HardwareBLESerial::getInstance();


// data in binary 
//uint8_t startData = 0b00000000;
//uint16_t startData = 0b0000000000000000;
uint32_t startData = 0b00000000000000000000000000000000;
//uint64_t startData = 0b000000000000000000000000000000000000000000000000;

byte ONE = 0b00000001; 

boolean startCmdRec = false;
boolean masterStart = false;
String command = "";
String masterCommand = "";
int dataCounter = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial);
  
  if (!bleSerial.beginAndSetupBLE("PA")) {
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
    if (command == "PA") {
      //startCmdRec = true;
      
      // trying to create the master start command
      bleSerial.println("PA is ready...");
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
          masterStart = true;
        }
        masterCommand = "";
      }
      
    }

    command = "";
    masterCommand = "";
  }
  // empty the command variable to make room for a new value
  command = "";
  masterCommand = "";
  Serial.println("PA: Sending data...");
 

  // ----------------DATA SENDING: ARDUINO NANO-> ADAFRUIT BLUEFRUIT----------------
  if (dataCounter != 500) {
    dataCounter++;
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

    char dataFinal[dataLen+1];
    for (int i = 0; i < dataLen; i++) {
      dataFinal[i] = dataStr[i];
    }
    dataFinal[dataLen] = ' ';
    dataFinal[dataLen+1] = '\0';
    Serial.println("Uploading through bleuart...");

    bleSerial.print("A ");
    bleSerial.println(dataFinal);
    //bleSerial.println((double)BLE.rssi());

    } else {
      bleSerial.println("PA done");
      startCmdRec = false;
      masterStart = false;
      dataCounter = 0;
      //startData = 0b0000000000000000;
      startData = 0b00000000000000000000000000000000;
      //startData = 0b000000000000000000000000000000000000000000000000;
    }

  // ----------------MANUAL STOP COMMAND: ARDUINO NANO <- ADAFRUIT BLUEFRUIT----------------
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
    //startData = 0b0000000000000000;
    startData = 0b00000000000000000000000000000000;
    //startData = 0b000000000000000000000000000000000000000000000000;
  }
  
  // empty the command variable to make room for a new value
  command = "";
  delay(200);     //#peripherals * 100
}
