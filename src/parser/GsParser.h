#ifndef GS_PARSER_H
#define GS_PARSER_H

#include "ILeniotParser.h"
#include "model/LeniotSentence.h"
#include <optional>

namespace leniot {

class GsParser : public ILeniotParser {
public:
    JenisKalimat getType() const override { return JenisKalimat::GS; }
    std::optional<GsData> parse(const std::string& body);
};

}

#endif
