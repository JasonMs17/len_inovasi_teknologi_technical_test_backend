#include "ChecksumValidator.h"
#include <sstream>
#include <iomanip>

namespace leniot {

bool ChecksumValidator::validate(const std::string& sentence) {
    if (sentence.empty() || sentence.front() != '$') {
        return false;
    }

    size_t asteriskPos = sentence.find_last_of('*');
    if (asteriskPos == std::string::npos || asteriskPos <= 1) {
        return false;
    }

    if (asteriskPos + 2 >= sentence.length()) {
        return false;
    }

    std::string checksumStr = sentence.substr(asteriskPos + 1);
    
    uint8_t expectedChecksum = 0;
    try {
        expectedChecksum = static_cast<uint8_t>(std::stoul(checksumStr, nullptr, 16));
    } catch (...) {
        return false;
    }

    std::string body = sentence.substr(1, asteriskPos - 1);
    uint8_t calculatedChecksum = calculate(body);

    return expectedChecksum == calculatedChecksum;
}

uint8_t ChecksumValidator::calculate(const std::string& body) {
    uint8_t checksum = 0;
    for (char c : body) {
        checksum ^= static_cast<uint8_t>(c);
    }
    return checksum;
}

}
