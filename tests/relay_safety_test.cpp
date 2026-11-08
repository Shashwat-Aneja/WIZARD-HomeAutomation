#include <cassert>
#include <vector>

struct PinEvent {
    char operation;
    int pin;
    int value;
};

static std::vector<PinEvent> events;

void digitalWrite(int pin, int value);
void pinMode(int pin, int mode);

#include "../src/RelaySafety.h"

void digitalWrite(int pin, int value) {
    events.push_back({'W', pin, value});
}

void pinMode(int pin, int mode) {
    events.push_back({'M', pin, mode});
}

int main() {
    const int HIGH_LEVEL = 1;
    const int OUTPUT_MODE = 1;

    initializeActiveLowRelay(2, HIGH_LEVEL, OUTPUT_MODE);
    initializeActiveLowRelay(5, HIGH_LEVEL, OUTPUT_MODE);

    assert(events.size() == 4);
    assert(events[0].operation == 'W');
    assert(events[0].pin == 2 && events[0].value == HIGH_LEVEL);
    assert(events[1].operation == 'M');
    assert(events[1].pin == 2 && events[1].value == OUTPUT_MODE);
    assert(events[2].operation == 'W');
    assert(events[2].pin == 5 && events[2].value == HIGH_LEVEL);
    assert(events[3].operation == 'M');
    assert(events[3].pin == 5 && events[3].value == OUTPUT_MODE);
    return 0;
}
