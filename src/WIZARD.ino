/*
  WIZARD - Wireless Integration and Zone Automation for Remote Devices
  Initial Arduino Firmware (v1.0)
*/

const int relay1 = 2;
const int relay2 = 3;
const int relay3 = 4;
const int relay4 = 5;
const int RELAY_ON = LOW;
const int RELAY_OFF = HIGH;

const String CMD_HELP = "HELP";\nconst String CMD_STATUS = "STATUS";\nconst String CMD_ALL_ON = "ALL1";\nconst String CMD_ALL_OFF = "ALL0";\nString command = "";

void setup() {
  Serial.begin(9600);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);

  setRelay(relay1, false);
  setRelay(relay2, false);
  setRelay(relay3, false);
  setRelay(relay4, false);

  Serial.println("WIZARD System Ready");
  Serial.println("Send A1/A0, B1/B0, C1/C0, D1/D0");
}

void printStartupMessage() {\n  Serial.println("WIZARD System Ready");\n  Serial.println("Send A1/A0, B1/B0, C1/C0, D1/D0");\n}\n\nvoid loop() {
  if (Serial.available()) {
    delay(5);
    command = Serial.readString();
    command.trim();
    handleCommand(command);
  }
}

void setRelay(int relayPin, bool enabled) {\n  digitalWrite(relayPin, enabled ? RELAY_ON : RELAY_OFF);\n}\n\n// Bluetooth protocol: A/B/C/D followed by 1 or 0 controls one relay.\n// ALL1 and ALL0 control all relays. STATUS reports current states.\n// Relays are active-low, so RELAY_ON is LOW and RELAY_OFF is HIGH.\n\nvoid printStatus() {\n  Serial.print("A:"); Serial.println(digitalRead(relay1) == RELAY_ON ? "ON" : "OFF");\n  Serial.print("B:"); Serial.println(digitalRead(relay2) == RELAY_ON ? "ON" : "OFF");\n  Serial.print("C:"); Serial.println(digitalRead(relay3) == RELAY_ON ? "ON" : "OFF");\n  Serial.print("D:"); Serial.println(digitalRead(relay4) == RELAY_ON ? "ON" : "OFF");\n}\n\nvoid printHelp() {\n  Serial.println("A1/A0 B1/B0 C1/C0 D1/D0 ALL1 ALL0 STATUS");\n}\n\nvoid handleCommand(String cmd) {
  if (cmd == CMD_STATUS) { printStatus(); return; }\n  if (cmd == CMD_HELP) { printHelp(); return; }\n  if (cmd == CMD_ALL_ON) { setRelay(relay1, true); setRelay(relay2, true); setRelay(relay3, true); setRelay(relay4, true); Serial.println("ALL ON"); return; }\n  if (cmd == CMD_ALL_OFF) { setRelay(relay1, false); setRelay(relay2, false); setRelay(relay3, false); setRelay(relay4, false); Serial.println("ALL OFF"); return; }\n  if (cmd == "A1") setRelay(relay1, true);
  else if (cmd == "A0") digitalWrite(relay1, RELAY_OFF);
  else if (cmd == "B1") setRelay(relay2, true);
  else if (cmd == "B0") digitalWrite(relay2, RELAY_OFF);
  else if (cmd == "C1") setRelay(relay3, true);
  else if (cmd == "C0") digitalWrite(relay3, RELAY_OFF);
  else if (cmd == "D1") setRelay(relay4, true);
  else if (cmd == "D0") digitalWrite(relay4, RELAY_OFF);
  else {
    Serial.print("Invalid Command: ");\n    Serial.println(cmd);
    return;
  }

  Serial.print("State updated: ");\n  Serial.print(cmd);\n  Serial.println(" OK");\n  Serial.print("Command OK: ");
  Serial.println(cmd);
}
