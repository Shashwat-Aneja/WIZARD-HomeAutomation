#include <cassert>
#include <iostream>
#include <vector>

#define LOW 0
#define HIGH 1
#define OUTPUT 1

struct PinEvent {
    char operation;
    int pin;
    int value;
};

static std::vector<PinEvent> pinEvents;

void pinMode(int pin, int mode) {
    pinEvents.push_back({'M', pin, mode});
}

void digitalWrite(int pin, int level) {
    pinEvents.push_back({'W', pin, level});
}

int digitalRead(int) {
    return HIGH;
}

unsigned long millis() {
    return 0;
}

class FakeSerial {
public:
    void begin(long) {}
    int available() { return 0; }
    int read() { return -1; }
    void print(const char*) {}
    void println(const char*) {}
};

FakeSerial Serial;

#include "../src/WIZARD.ino"

int main() {
    setup();

    for (int pin = relay1; pin <= relay4; ++pin) {
        size_t writeIndex = pinEvents.size();
        size_t modeIndex = pinEvents.size();

        for (size_t index = 0; index < pinEvents.size(); ++index) {
            const PinEvent& event = pinEvents[index];
            if (event.pin != pin) continue;
            if (event.operation == 'W' && writeIndex == pinEvents.size()) {
                writeIndex = index;
                assert(event.value == RELAY_OFF);
            }
            if (event.operation == 'M' && modeIndex == pinEvents.size()) {
                modeIndex = index;
                assert(event.value == OUTPUT);
            }
        }

        assert(writeIndex < modeIndex);
    }

    std::cout << "Relay startup safety tests passed\n";
    return 0;
}
