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

const String CMD_HELP = "HELP";
const String CMD_STATUS = "STATUS";
const String CMD_ALL_ON = "ALL1";
const String CMD_ALL_OFF = "ALL0";
String command = "";

void setup() {
  Serial.begin(9600);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);

  setAllRelays(false);

  printStartupMessage();
}

void printStartupMessage() {
  Serial.println("WIZARD System Ready");
  Serial.println("Send A1/A0, B1/B0, C1/C0, D1/D0");
}

void loop() {
  if (Serial.available()) {
    delay(5);
    command = Serial.readString();
    command.trim();
    command.toUpperCase();
    handleCommand(command);
  }
}

void setRelay(int relayPin, bool enabled) {
  digitalWrite(relayPin, enabled ? RELAY_ON : RELAY_OFF);
}

// Bluetooth protocol: A/B/C/D followed by 1 or 0 controls one relay.
// ALL1 and ALL0 control all relays. STATUS reports current states.
// Relays are active-low, so RELAY_ON is LOW and RELAY_OFF is HIGH.

void printStatus() {
  Serial.print("A:"); Serial.println(digitalRead(relay1) == RELAY_ON ? "ON" : "OFF");
  Serial.print("B:"); Serial.println(digitalRead(relay2) == RELAY_ON ? "ON" : "OFF");
  Serial.print("C:"); Serial.println(digitalRead(relay3) == RELAY_ON ? "ON" : "OFF");
  Serial.print("D:"); Serial.println(digitalRead(relay4) == RELAY_ON ? "ON" : "OFF");
}

void printHelp() {
  Serial.println("A1/A0 B1/B0 C1/C0 D1/D0 ALL1 ALL0 STATUS HELP");
  Serial.println("A-D control individual relays; ALL1/ALL0 control every relay.");
}

void setAllRelays(bool enabled) {
  setRelay(relay1, enabled);
  setRelay(relay2, enabled);
  setRelay(relay3, enabled);
  setRelay(relay4, enabled);
}

bool isRelayCommand(const String &cmd) {
  return cmd.length() == 2 && cmd.charAt(0) >= 'A' && cmd.charAt(0) <= 'D' && (cmd.charAt(1) == '0' || cmd.charAt(1) == '1');
}

void handleCommand(String cmd) {
  if (cmd.length() > 16) {
    Serial.println("Invalid Command: too long");
    return;
  }
  if (cmd == CMD_STATUS) { printStatus(); return; }
  if (!isRelayCommand(cmd) && cmd != CMD_HELP && cmd != CMD_ALL_ON && cmd != CMD_ALL_OFF) {
    Serial.print("Invalid Command: ");
    Serial.println(cmd);
    return;
  }
  if (cmd == CMD_HELP) { printHelp(); return; }
  if (cmd == CMD_ALL_ON) { setAllRelays(true); Serial.println("ALL ON"); return; }
  if (cmd == CMD_ALL_OFF) { setAllRelays(false); Serial.println("ALL OFF"); return; }
  if (cmd == "A1") setRelay(relay1, true);
  else if (cmd == "A0") setRelay(relay1, false);
  else if (cmd == "B1") setRelay(relay2, true);
  else if (cmd == "B0") setRelay(relay2, false);
  else if (cmd == "C1") setRelay(relay3, true);
  else if (cmd == "C0") setRelay(relay3, false);
  else if (cmd == "D1") setRelay(relay4, true);
  else if (cmd == "D0") setRelay(relay4, false);
  else {
    Serial.print("Invalid Command: ");
    Serial.println(cmd);
    return;
  }

  Serial.print("State updated: ");
  Serial.print(cmd);
  Serial.println(" OK");
  // Successful appliance commands return both state and acknowledgement lines.
  Serial.print("Command OK: ");
  Serial.println(cmd);
}
