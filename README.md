# WIZARD-HomeAutomation
Smart home automation using Arduino, relay modules and Bluetooth.
## 🔌 Circuit Diagram

The complete circuit design for WIZARD is included in the repository.

## 💻 Firmware Scope

The current firmware supports individual relay control, all-relay scenes, relay status reporting, help output, command normalization, and invalid-input protection.

## 🛠 Hardware Used

| Component | Quantity | Purpose |
|----------|----------|----------|
| Arduino UNO/Nano | 1 | Main controller |
| HC-05 Bluetooth Module | 1 | Wireless communication |
| 4-Channel Relay Module | 1 | Switching appliances |
| Jumper Wires | — | System wiring |
| 230V AC Appliances | 4 | Loads (A, B, C, D) |
| Optional: Buzzer/LED | 1 | System status |

## 🔌 Relay Pin Mapping

| Appliance | Arduino Pin | Relay State |
|-----------|-------------|-------------|
| A | D2 | LOW = ON |
| B | D3 | LOW = ON |
| C | D4 | LOW = ON |
| D | D5 | LOW = ON |

The relay module is active-low, so the firmware drives a relay pin LOW to switch its appliance ON.

## ⚡ Relay Logic

The relay module is active-low: `LOW` switches an appliance ON and `HIGH` switches it OFF. The firmware initializes all four relays to OFF during startup.

## 📡 Bluetooth Command Table

| Command | Function |
|---------|----------|
| A1 | Turn ON Appliance A |
| A0 | Turn OFF Appliance A |
| B1 | Turn ON Appliance B |
| B0 | Turn OFF Appliance B |
| C1 | Turn ON Appliance C |
| C0 | Turn OFF Appliance C |
| D1 | Turn ON Appliance D |
| D0 | Turn OFF Appliance D |
| ALL1 | Turn ON all appliances |
| ALL0 | Turn OFF all appliances |
| STATUS | Report current relay states |
| HELP | Show supported commands |

## 🧪 Firmware Test Checklist

1. Upload `src/WIZARD.ino` with the Arduino IDE.
2. Open Serial Monitor at 9600 baud.
3. Send `HELP` and confirm the supported command list is returned.
4. Test each A/B/C/D ON and OFF command individually.
5. Test `ALL1`, `ALL0`, and `STATUS` before connecting mains-powered loads.
6. Verify invalid and oversized commands are rejected without changing relay state.

## 📶 Command Protocol

Commands are trimmed and converted to uppercase before processing. Individual appliance commands use a letter followed by `1` or `0`; scene commands use `ALL1` and `ALL0`. Successful commands return a state update followed by a `Command OK` acknowledgement. Unsupported commands return an `Invalid Command` response.

## 🧹 Command Handling

Incoming commands are trimmed and converted to uppercase, so commands such as `a1` and ` A1 ` are accepted. Empty, oversized, and unsupported commands are rejected without changing relay state.

## ✅ Pre-Connection Checklist

Before connecting mains-powered appliances, verify relay pin mapping, test every command with a low-voltage load, and confirm `ALL0` leaves every relay OFF.

## ⚠️ Safety Notes

- Appliances run on **high voltage AC**, handle carefully.  
- Double-check relay wiring before connecting AC.  
- Neutral wire must always go directly to the appliance.  
- Use proper insulation and avoid loose connections.  
- Test the system with a small 5V/12V load before using AC devices.

  ## 🖥️ Serial Monitor

Use **9600 baud** when testing the firmware through the Arduino Serial Monitor. Accepted appliance commands return a state update followed by a `Command OK` acknowledgement.

## 📸 Media
No images or videos are included in this repository. All functionality is demonstrated through code, circuit diagrams, and documentation.

