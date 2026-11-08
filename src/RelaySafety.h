#ifndef WIZARD_RELAY_SAFETY_H
#define WIZARD_RELAY_SAFETY_H

// Set the inactive output latch before enabling OUTPUT mode. On active-low
// relay boards this prevents the brief LOW pulse caused by Arduino's default
// output latch during pinMode(pin, OUTPUT).
inline void initializeActiveLowRelay(int relayPin, int inactiveLevel, int outputMode) {
    digitalWrite(relayPin, inactiveLevel);
    pinMode(relayPin, outputMode);
}

#endif
