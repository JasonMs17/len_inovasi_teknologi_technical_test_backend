#ifndef GP_PARSER_H
#define GP_PARSER_H

#include "ILeniotParser.h"
#include "model/LeniotSentence.h"
#include <optional>

namespace leniot {

class GpParser : public ILeniotParser {
public:
    JenisKalimat getType() const override { return JenisKalimat::GP; }
    std::optional<GpData> parse(const std::string& body);
};

}

#endif
