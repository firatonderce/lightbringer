
# lightbringer: Arduino Relay Control with Bluetooth and Switch

This project demonstrates how to control a relay using an Arduino, with inputs from both a physical switch and a Bluetooth module. The relay state can be toggled based on inputs received from either the switch or the Bluetooth module.

## Table of Contents
- [Introduction](#introduction)
- [Hardware Required](#hardware-required)
- [Circuit Diagram](#circuit-diagram)
- [Installation](#installation)
- [Usage](#usage)
- [Code Explanation](#code-explanation)
- [License](#license)

## Introduction

This Arduino project allows you to control a relay using a physical switch or a Bluetooth module. The relay can be turned on or off based on the input from the connected switch or Bluetooth commands.

## Hardware Required

- Arduino board (e.g., Arduino Uno)
- Relay module
- Bluetooth module (e.g., HC-05)
- Push-button switch
- Resistors
- Jumper wires
- Breadboard

## Circuit Diagram

Here's the circuit diagram to connect the components:

```
   +---+                   +-------------------+
   |   |                   |                   |
   |   |                   |                   |
   |   |                   |                   |
   |   +-------------------+ Relay Module      |
   |                       |                   |
   +---+-------------------+-------------------+
       |                   |
  (8) Switch Out Pin       |
                           |
  (12) Switch In Pin       |
                           |
  (A0) Relay Pin           |
```

### Bluetooth Module Connection

```
   +-----+                   +-------------------+
   |     |                   |                   |
   |     |                   |                   |
   | TX  +-------------------+ RX                |
   | RX  +-------------------+ TX                |
   | GND +-------------------+ GND               |
   | VCC +-------------------+ VCC               |
   +-----+                   +-------------------+
```

## Installation

1. **Connect the hardware:**
   - Connect the relay module to the Arduino.
   - Connect the Bluetooth module to the Arduino.
   - Connect the push-button switch to the Arduino.

2. **Upload the code:**
   - Open the Arduino IDE.
   - Copy the provided code into the IDE.
   - Select the correct board and port.
   - Upload the code to your Arduino.

## Usage

1. **Bluetooth Control:**
   - Connect to the Bluetooth module using a Bluetooth-enabled device.
   - Send \`1\` to turn the relay ON.
   - Send \`0\` to turn the relay OFF.

2. **Switch Control:**
   - Press the push-button switch to toggle the relay state.

## Code Explanation

Here's a brief explanation of the main parts of the code:

- **Pin Definitions:** Define the pins for the relay, switch, and Bluetooth module.
- **Initialization:** Set up the pins and initialize the relay state.
- **Main Loop:** Continuously check for inputs from the Bluetooth module and the switch, and update the relay state accordingly.

```cpp
const int switchOutPin = 8;
const int switchInPin = 12;
const int relayPin = A0;

bool isInitialized = false;
bool relayState = HIGH;

int bluetoothInput = -1;
int switchInput = 0;
int previousBluetoothInput = -1;
int previousSwitchInput = 0;

void initializeRelay() {
  digitalWrite(relayPin, LOW);
  isInitialized = true;
}

void setup() {
  Serial.begin(9600);
  pinMode(relayPin, OUTPUT);
  pinMode(switchOutPin, OUTPUT);
  pinMode(switchInPin, INPUT_PULLUP);
}

void loop() {
  if (!isInitialized) {
    initializeRelay();
  }

  bluetoothInput = Serial.read();
  switchInput = digitalRead(switchInPin);

  if (previousBluetoothInput != bluetoothInput && bluetoothInput != -1) {
    previousBluetoothInput = bluetoothInput;
    switch (bluetoothInput) {
      case 1:
        relayState = LOW;
        break;
      case 0:
        relayState = HIGH;
        break;
    }
  }

  if (previousSwitchInput != switchInput) {
    previousSwitchInput = switchInput;
    switch (switchInput) {
      case 1:
        relayState = LOW;
        break;
      case 0:
        relayState = HIGH;
        break;
    }
  }

  digitalWrite(relayPin, relayState);
  delay(100);
}
```

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
