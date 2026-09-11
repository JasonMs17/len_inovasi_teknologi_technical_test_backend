#ifndef LENIOT_SENTENCE_H
#define LENIOT_SENTENCE_H

#include "common/Types.h"

namespace leniot {

struct GpData {
    double latitudeDDM;
    char latDir;
    double longitudeDDM;
    char lonDir;
    Waktu timestamp;
};

struct GsData {
    double longitudeDDM;
    char lonDir;
    double latitudeDDM;
    char latDir;
    Waktu timestamp;
};

struct HeData {
    double headingDegree;
    Waktu timestamp;
};

struct VeData {
    double speedKmh;
    double speedKnots;
    double headingDegree;
    Waktu timestamp;
};

struct PaData {
    double headingDegree;
    double pitchDegree;
    double rollDegree;
    Waktu timestamp;
};

}

#endif
