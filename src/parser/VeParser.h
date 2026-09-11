#ifndef VE_PARSER_H
#define VE_PARSER_H

#include "ILeniotParser.h"
#include "model/LeniotSentence.h"
#include <optional>

namespace leniot {

class VeParser : public ILeniotParser {
public:
    JenisKalimat getType() const override { return JenisKalimat::VE; }
    std::optional<VeData> parse(const std::string& body);
};

}

#endif
