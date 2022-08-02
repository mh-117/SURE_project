/*********************************************************************

 ! Code for Peripheral X ! This is a template file for a new peripheral !
 During testing, it is similar to the code used for Peripheral A 
 
 The following code is built from the SerialPassThrough example from the
 HardwareBLESerial library: https://github.com/Uberi/Arduino-HardwareBLESerial
 File->Examples->HardwareBLESerial->SerialPassThrough


*********************************************************************/
#include <HardwareBLESerial.h>
#include <ArduinoBLE.h>

HardwareBLESerial &bleSerial = HardwareBLESerial::getInstance();


// data in binary 
//uint8_t startData = 0b10000000;
uint16_t startData = 0b0000000000000000;
//uint32_t startData = 0b00000000000000000000000000000000;

byte ONE = 0b00000001; 

boolean startCmdRec = false;
boolean masterStart = false;
String command = "";
String masterCommand = "";    
int dataCounter = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial);

// FIX ME: This is where we name the peripheral 
  if (!bleSerial.beginAndSetupBLE("PX")) {      
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
    
// FIX ME: need to change PX according to which peripheral is being flashed
    if (command == "PX") {
      //startCmdRec = true;

// FIX ME: this statement appears in the app UART. Change so that the right peripheral name will 
// be printed
      bleSerial.println("PX is ready...");
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
 

  // ----------------DATA SENDING: ARDUINO NANO-> ADAFRUIT BLUEFRUIT----------------
// FIX ME: change the value the dataCounter will count to since this controls how many data packets will be sent
  if (dataCounter != 500) {
    dataCounter++;
    Serial.println("-------");  

    // series of data
    startData = startData + ONE;        //for testing, just incremented the data every loop before sending
    Serial.println(startData,BIN);

    // Convert data to a string so it can be sent through bleuart
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

// FIX ME: this is where the data packet gets labeled with the peripheral's letter name
    bleSerial.print("X ");
    bleSerial.println(dataFinal);
    
  } else {
    // when the desired number of packets have been sent, stop sending
// FIX ME: signals that Peripheral X is done sending data packets
    bleSerial.println("PX done");
    startCmdRec = false;
    masterStart = false;
    dataCounter = 0;
    startData = 0b0000000000000000;                       // 16 bits
    //startData = 0b00000000000000000000000000000000;     // 32 bits
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
    startData = 0b0000000000000000;                        // 16 bits
    //startData = 0b00000000000000000000000000000000;      // 32 bits
  }
  
  // empty the command variable to make room for a new value
  command = "";
  delay(200);     
}
