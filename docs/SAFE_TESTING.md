# WIZARD Safe Hardware Bring-Up

This checklist is for the first firmware and relay-module tests. Keep mains-powered appliances disconnected until low-voltage behavior has been verified.

## Before powering the board

- Disconnect all mains wiring and appliances from the relay contacts.
- Inspect the board, relay module, jumper wires, and power supply for shorts or exposed conductors.
- Confirm that the relay module's logic voltage and the Arduino board's I/O voltage are compatible.
- Verify relay pins: A on D2, B on D3, C on D4, and D on D5.
- Confirm the relay module is active-low. In this firmware, LOW means ON and HIGH means OFF.

## Serial test sequence

1. Upload `src/WIZARD.ino` and open Serial Monitor at 9600 baud.
2. Reset the board and confirm the startup message reports that all relays initialize OFF.
3. Send `HELP`; verify the supported commands are listed.
4. Send `STATUS`; verify A, B, C, and D are all OFF.
5. Send `A1`, then `STATUS`; only A should report ON.
6. Send `A0`; verify A reports OFF. Repeat for B, C, and D.
7. Send `ALL1`, verify all four states are ON, then send `ALL0` and verify all are OFF.
8. Send an unsupported command, an empty line, and a command longer than 16 characters. Invalid input must not change relay states.

## Acceptance criteria

- Power-up initializes all relay outputs to OFF.
- Valid commands change only the intended relay or scene.
- `STATUS` reflects the actual output-pin states.
- Invalid commands are rejected without changing outputs.
- The board remains stable during repeated commands.

## Mains safety gate

Do not connect mains wiring as part of this checklist. Mains voltage can cause fatal electric shock and fire. Any later mains integration should be designed and inspected by a qualified person, with appropriate enclosure, isolation, strain relief, overcurrent protection, and local electrical-code compliance. Passing serial tests does not certify hardware as safe for household mains use.
