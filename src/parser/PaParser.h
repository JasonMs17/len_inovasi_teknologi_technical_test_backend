#ifndef PA_PARSER_H
#define PA_PARSER_H

#include "ILeniotParser.h"
#include "model/LeniotSentence.h"
#include <optional>

namespace leniot {

class PaParser : public ILeniotParser {
public:
    JenisKalimat getType() const override { return JenisKalimat::PA; }
    std::optional<PaData> parse(const std::string& body);
};

}

#endif
