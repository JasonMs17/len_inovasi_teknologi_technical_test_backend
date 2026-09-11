#include "LeniotParserFactory.h"

namespace leniot {

JenisKalimat LeniotParserFactory::identifyType(const std::string& sentence) {
    if (sentence.length() < 3 || sentence[0] != '$') {
        return JenisKalimat::TidakDikenal;
    }

    std::string typeStr = sentence.substr(1, 2);
    if (typeStr == "GP") return JenisKalimat::GP;
    if (typeStr == "GS") return JenisKalimat::GS;
    if (typeStr == "HE") return JenisKalimat::HE;
    if (typeStr == "VE") return JenisKalimat::VE;
    if (typeStr == "PA") return JenisKalimat::PA;

    return JenisKalimat::TidakDikenal;
}

}
