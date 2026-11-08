/*
  WIZARD - Wireless Integration and Zone Automation for Remote Devices
  Initial Arduino Firmware (v1.0)
*/

#include <string.h>
#include "CommandParser.h"
#include "RelaySafety.h"

const int relay1 = 2;
const int relay2 = 3;
const int relay3 = 4;
const int relay4 = 5;
const int RELAY_ON = LOW;
const int RELAY_OFF = HIGH;
const unsigned long SERIAL_FRAME_TIMEOUT_MS = 50;

CommandParser commandParser;
unsigned long lastCommandByteAt = 0;

void handleCommand(const char* cmd);
void processSerialInput();

void setup() {
  Serial.begin(9600);

  // Active-low relays must be driven HIGH before becoming outputs. This
  // avoids a startup pulse that could briefly energize an attached load.
  initializeActiveLowRelay(relay1, RELAY_OFF, OUTPUT);
  initializeActiveLowRelay(relay2, RELAY_OFF, OUTPUT);
  initializeActiveLowRelay(relay3, RELAY_OFF, OUTPUT);
  initializeActiveLowRelay(relay4, RELAY_OFF, OUTPUT);

  printStartupMessage();
  Serial.println("Safety: all relays initialized OFF");
}

void printStartupMessage() {
  Serial.println("WIZARD System Ready");
  Serial.println("Send A1/A0, B1/B0, C1/C0, D1/D0");
}

void loop() {
  processSerialInput();
}

void setRelay(int relayPin, bool enabled) {
  digitalWrite(relayPin, enabled ? RELAY_ON : RELAY_OFF);
}

// Bluetooth protocol: A/B/C/D followed by 1 or 0 controls one relay.
// ALL1 and ALL0 control all relays. STATUS reports current states.
// Relays are active-low, so RELAY_ON is LOW and RELAY_OFF is HIGH.

void printStatus() {
  Serial.println("WIZARD Relay Status");
  Serial.print("A:"); Serial.println(digitalRead(relay1) == RELAY_ON ? "ON" : "OFF");
  Serial.print("B:"); Serial.println(digitalRead(relay2) == RELAY_ON ? "ON" : "OFF");
  Serial.print("C:"); Serial.println(digitalRead(relay3) == RELAY_ON ? "ON" : "OFF");
  Serial.print("D:"); Serial.println(digitalRead(relay4) == RELAY_ON ? "ON" : "OFF");
}

void printHelp() {
  Serial.println("Individual: A1/A0 B1/B0 C1/C0 D1/D0");
  Serial.println("Scenes: ALL1/ALL0");
  Serial.println("Diagnostics: STATUS | HELP");
}

void setAllRelays(bool enabled) {
  setRelay(relay1, enabled);
  setRelay(relay2, enabled);
  setRelay(relay3, enabled);
  setRelay(relay4, enabled);
}

bool isRelayCommand(const char* cmd) {
  return cmd != NULL && strlen(cmd) == 2
      && cmd[0] >= 'A' && cmd[0] <= 'D'
      && (cmd[1] == '0' || cmd[1] == '1');
}

int relayPinForCommand(const char* cmd) {
  switch (cmd[0]) {
    case 'A': return relay1;
    case 'B': return relay2;
    case 'C': return relay3;
    case 'D': return relay4;
    default: return -1;
  }
}

void applyRelayCommand(const char* cmd) {
  const int relayPin = relayPinForCommand(cmd);
  if (relayPin >= 0) {
    setRelay(relayPin, cmd[1] == '1');
  }
}

void handleCommand(const char* cmd) {
  if (cmd == NULL || cmd[0] == '\0') {
    Serial.println("Invalid Command: empty");
    return;
  }
  if (strlen(cmd) > CommandParser::MAX_COMMAND_LENGTH) {
    Serial.println("Invalid Command: too long");
    return;
  }
  if (strcmp(cmd, "STATUS") == 0) {
    printStatus();
    return;
  }
  if (!isRelayCommand(cmd)
      && strcmp(cmd, "HELP") != 0
      && strcmp(cmd, "ALL1") != 0
      && strcmp(cmd, "ALL0") != 0) {
    Serial.print("Invalid Command: ");
    Serial.println(cmd);
    return;
  }
  if (strcmp(cmd, "HELP") == 0) {
    printHelp();
    return;
  }
  if (strcmp(cmd, "ALL1") == 0) {
    setAllRelays(true);
    Serial.println("ALL ON");
    return;
  }
  if (strcmp(cmd, "ALL0") == 0) {
    setAllRelays(false);
    Serial.println("ALL OFF");
    return;
  }

  applyRelayCommand(cmd);
  Serial.print("State updated: ");
  Serial.print(cmd);
  Serial.println(" OK");
  Serial.print("Command OK: ");
  Serial.println(cmd);
}

void dispatchCommand(CommandParser::Result result) {
  if (result == CommandParser::TOO_LONG) {
    Serial.println("Invalid Command: too long");
    return;
  }
  if (result != CommandParser::READY) {
    return;
  }
  handleCommand(commandParser.command());
  commandParser.reset();
}

void processSerialInput() {
  while (Serial.available() > 0) {
    const char incoming = static_cast<char>(Serial.read());
    lastCommandByteAt = millis();
    dispatchCommand(commandParser.feed(incoming));
  }

  // Preserve HC-05 clients that send a command without a newline terminator.
  // A short idle interval completes the frame without blocking the control loop.
  if (commandParser.hasPending()
      && millis() - lastCommandByteAt >= SERIAL_FRAME_TIMEOUT_MS) {
    dispatchCommand(commandParser.finish());
  }
}
