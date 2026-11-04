#ifndef WIZARD_COMMAND_PARSER_H
#define WIZARD_COMMAND_PARSER_H

#include <stddef.h>

class CommandParser {
public:
    static const size_t MAX_COMMAND_LENGTH = 16;

    enum Result {
        INCOMPLETE,
        READY,
        TOO_LONG
    };

    CommandParser() : length_(0), overflow_(false) {
        buffer_[0] = '\0';
    }

    Result feed(char value) {
        if (value == '\r' || value == '\n') {
            return finish();
        }
        if (overflow_) {
            return INCOMPLETE;
        }
        if (length_ >= MAX_COMMAND_LENGTH) {
            overflow_ = true;
            return INCOMPLETE;
        }
        buffer_[length_++] = value;
        buffer_[length_] = '\0';
        return INCOMPLETE;
    }

    Result finish() {
        if (overflow_) {
            reset();
            return TOO_LONG;
        }
        if (length_ == 0) {
            return INCOMPLETE;
        }
        normalize();
        return READY;
    }

    bool hasPending() const {
        return length_ > 0 || overflow_;
    }

    const char* command() const {
        return buffer_;
    }

    void reset() {
        length_ = 0;
        overflow_ = false;
        buffer_[0] = '\0';
    }

private:
    static bool isWhitespace(char value) {
        return value == ' ' || value == '\t' || value == '\r' || value == '\n';
    }

    static char toUpperAscii(char value) {
        if (value >= 'a' && value <= 'z') {
            return static_cast<char>(value - ('a' - 'A'));
        }
        return value;
    }

    void normalize() {
        size_t start = 0;
        while (start < length_ && isWhitespace(buffer_[start])) {
            ++start;
        }
        size_t end = length_;
        while (end > start && isWhitespace(buffer_[end - 1])) {
            --end;
        }
        const size_t normalizedLength = end - start;
        for (size_t index = 0; index < normalizedLength; ++index) {
            buffer_[index] = toUpperAscii(buffer_[start + index]);
        }
        length_ = normalizedLength;
        buffer_[length_] = '\0';
    }

    char buffer_[MAX_COMMAND_LENGTH + 1];
    size_t length_;
    bool overflow_;
};

#endif
