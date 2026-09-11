#ifndef ILENIOT_PARSER_H
#define ILENIOT_PARSER_H

#include "common/Types.h"
#include <string>

namespace leniot {

class ILeniotParser {
public:
    virtual ~ILeniotParser() = default;
    virtual JenisKalimat getType() const = 0;
};

}

#endif
