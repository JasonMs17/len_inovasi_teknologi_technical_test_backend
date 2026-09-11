#ifndef HE_PARSER_H
#define HE_PARSER_H

#include "ILeniotParser.h"
#include "model/LeniotSentence.h"
#include <optional>

namespace leniot {

class HeParser : public ILeniotParser {
public:
    JenisKalimat getType() const override { return JenisKalimat::HE; }
    std::optional<HeData> parse(const std::string& body);
};

}

#endif
