# Peripheral: Arduino Nano 33 BLEs

All code in this section get uploaded to the Arduino Nano 33 BLEs for initiating their roles as peripherals.
Goal: these boards send data wirelessly to the Adafruit Bluefruit nRF52 Feather once reaceiving a start command from a phone. 

* SendingDataTestArduino: File for initiating a connection between the Arduino Nano and the LightBlue Bluetooth App on iPhone
* PeripheralArduino-PA: File for initiating a connection between the Arduino Nano and Adafruit Bluefruit (specifically for testing, this file establishes Peripheral A)
* PeripheralArduino-PB: File for initiating a connection between the Arduino Nano and Adafruit Bluefruit (specifically for testing, this file establishes Peripheral B)
* PeripheralArduino-PC: File for initiating a connection between the Arduino Nano and Adafruit Bluefruit (specifically for testing, this file establishes Peripheral C)
* PeripheralArduino-PX: This is a template code for new peripheral. See areas with a FIX ME for sections that need to be updated according to the new peripheral's name

Features of the Peripherals
----------
* Each peripheral device is named "PA", "PB", "PC", etc. The peripherals wait to hear a command that is labelled with their given name. This command is controlled by the user who will type the device name in the UART terminal. Upon hearing the command, the peripheral will indicate that they are ready to send their data to the central. The user can call to multiple peripherals to send data simultaneously. A master "start" command will then need to be sent for the devices to begin sending data. Once the peripherals have sent all their data to the central, they will stop sending data but will continue to stay connected to the central. 
* Given a "stop" command from the user, the peripherals can be manually told to stop sending data 
* The max data packet size that can be sent is: ---
* The lowest data packet rate that can be achieved without lots of packet loss is: ---
* Note: the code used for the SURE program project initializes the peripherals with data to send. In later works, the peripherals will be connected to a custom IC that will be sending it the data to be sent to the central
