#ifndef LENIOT_PARSER_FACTORY_H
#define LENIOT_PARSER_FACTORY_H

#include "ILeniotParser.h"
#include "GpParser.h"
#include "GsParser.h"
#include "HeParser.h"
#include "VeParser.h"
#include "PaParser.h"
#include <memory>

namespace leniot {

class LeniotParserFactory {
public:
    static JenisKalimat identifyType(const std::string& sentence);
};

}

#endif
