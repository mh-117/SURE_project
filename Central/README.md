# Central/Peripheral: Adafruit Bluefruit nRF52 Feather

All code gets sent to the Adafruit Bluefruit nRF52 Feather. This board will also be responsible for connecting to multiple peripherals as well as receiving the start command from the phone. 

* SendingDataTestBluefruit: File initiates a connection between the Adafruit Bluefruit and the Bluefruit LE Connect App for iPhone and PC
* Central_PeripheralBluefruit: File initiates a dual role connection where the Bluefruit acts as a central to connect to a peripheral Arduino nano while also acts as a peripheral to connect to the Bluefruit LE Connect App for iPhone
* Central_Peripheral_multi: File initiates a connection to multiple peripherals. This file also contains pieces from Central_PeripheralBluefruit to be able to maintain its dual role mode as well

Features of the Central Node
----------
* The central node works simultaneously as a central (to connect to the Arduino Nano 33 BLE peripherals to receive data) and as a peripheral (to then relay the data recevied to a PC or phone). Therefore, it is considered to be in a dual mode state to satisfy both roles at the same time
* Uses the bluetooth UART (bleuart) service for receiving and sending data packets
