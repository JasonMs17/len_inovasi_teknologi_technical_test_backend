#ifndef CHECKSUM_VALIDATOR_H
#define CHECKSUM_VALIDATOR_H

#include <string>
#include <cstdint>

namespace leniot {

class ChecksumValidator {
public:
    static bool validate(const std::string& sentence);
    static uint8_t calculate(const std::string& body);
};

}

#endif
