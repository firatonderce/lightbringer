const int relayPin = A0;
const int switchOutPin = 8;
const int switchInPin = 12;

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
