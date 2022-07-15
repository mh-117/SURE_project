# Central/Peripheral: Adafruit Bluefruit nRF52 Feather

All code gets sent to the Adafruit Bluefruit nRF52 Feather. This board works simultaneously as a central (to connect to the Arduino Nano 33 BLE to receive data) 
and as a peripheral (to then relay the data received to a phone). All conenctions are made over bluetooth and aim to use the bluetooth UART (bleuart) service. This board
will also be responsible for connecting to multiple peripherals as well as receiving the start command from the phone. 
