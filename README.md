# WIZARD-HomeAutomation
Smart home automation using Arduino, relay modules and Bluetooth.
## 🔌 Circuit Diagram

The complete circuit design for WIZARD is included in the repository.

### ASCII Circuit (Quick View)

## 🛠 Hardware Used

| Component | Quantity | Purpose |
|----------|----------|----------|
| Arduino UNO/Nano | 1 | Main controller |
| HC-05 Bluetooth Module | 1 | Wireless communication |
| 4-Channel Relay Module | 1 | Switching appliances |
| Jumper Wires | — | System wiring |
| 230V AC Appliances | 4 | Loads (A, B, C, D) |
| Optional: Buzzer/LED | 1 | System status |

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

## ⚠️ Safety Notes

- Appliances run on **high voltage AC**, handle carefully.  
- Double-check relay wiring before connecting AC.  
- Neutral wire must always go directly to the appliance.  
- Use proper insulation and avoid loose connections.  
- Test the system with a small 5V/12V load before using AC devices.
