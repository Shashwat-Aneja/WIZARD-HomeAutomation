/*
  WIZARD — Wireless Integration and Zone Automation for Remote Devices
  Initial Arduino Firmware (v1.0)

  Description:
  This sketch allows Bluetooth-based control of household appliances 
  using a 4-channel relay module. Commands received from HC-05/HC-06 
  trigger the respective relay ON/OFF.

  Designed for reliability, clarity, and safe startup behavior.
*/

// Relay pin assignment
const int relay1 = 2;   // Appliance A
const int relay2 = 3;   // Appliance B
const int relay3 = 4;   // Appliance C
const int relay4 = 5;   // Appliance D

String command = "";    // Store incoming Bluetooth commands

void setup() {
  Serial.begin(9600);          // Bluetooth default baud rate

  // Configure relays
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);

  // Safe startup — ensure all appliances start OFF
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);

  Serial.println("WIZARD System Ready");
  Serial.println("Send A1/A0, B1/B0, C1/C0, D1/D0");
}

void loop() {
  // Read Bluetooth data
  if (Serial.available()) {
    delay(5);  // Allow buffer fill
    command = Serial.readString();
    command.trim();            // Remove spaces/newlines

    handleCommand(command);    // Process command
  }
}

void handleCommand(String cmd) {
  // Appliance A
  if (cmd == "A1") digitalWrite(relay1, LOW);
  else if (cmd == "A0") digitalWrite(relay1, HIGH);

  // Appliance B
  else if (cmd == "B1") digitalWrite(relay2, LOW);
  else if (cmd == "B0") digitalWrite(relay2, HIGH);

  // Appliance C
  else if (cmd == "C1") digitalWrite(relay3, LOW);
  else if (cmd == "C0") digitalWrite(relay3, HIGH);

  // Appliance D
  else if (cmd == "D1") digitalWrite(relay4, LOW);
  else if (cmd == "D0") digitalWrite(relay4, HIGH);

  // Unknown command
  else {
    Serial.println("Invalid Command");
    return;
  }

  Serial.print("Command OK: ");
  Serial.println(cmd);
}
