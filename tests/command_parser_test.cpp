#include <cassert>
#include <cstring>
#include <iostream>

#include "../src/CommandParser.h"

int main() {
    CommandParser parser;

    assert(parser.feed('a') == CommandParser::INCOMPLETE);
    assert(parser.feed('1') == CommandParser::INCOMPLETE);
    assert(parser.finish() == CommandParser::READY);
    assert(std::strcmp(parser.command(), "A1") == 0);
    parser.reset();

    const char* padded = "  all1 \t";
    for (const char* cursor = padded; *cursor; ++cursor) {
        parser.feed(*cursor);
    }
    assert(parser.finish() == CommandParser::READY);
    assert(std::strcmp(parser.command(), "ALL1") == 0);
    parser.reset();

    parser.feed('B');
    parser.feed('0');
    assert(parser.feed('\r') == CommandParser::READY);
    assert(std::strcmp(parser.command(), "B0") == 0);
    parser.reset();
    assert(parser.feed('\n') == CommandParser::INCOMPLETE);

    for (size_t index = 0; index < CommandParser::MAX_COMMAND_LENGTH; ++index) {
        parser.feed('X');
    }
    assert(parser.finish() == CommandParser::READY);
    assert(std::strlen(parser.command()) == CommandParser::MAX_COMMAND_LENGTH);
    parser.reset();

    for (size_t index = 0; index <= CommandParser::MAX_COMMAND_LENGTH; ++index) {
        parser.feed('X');
    }
    assert(parser.hasPending());
    assert(parser.finish() == CommandParser::TOO_LONG);
    assert(!parser.hasPending());
    assert(std::strcmp(parser.command(), "") == 0);

    assert(parser.feed('\n') == CommandParser::INCOMPLETE);
    std::cout << "CommandParser tests passed\n";
    return 0;
}
