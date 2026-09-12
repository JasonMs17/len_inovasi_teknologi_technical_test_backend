#ifndef EXTRAPOLATION_SERVICE_H
#define EXTRAPOLATION_SERVICE_H

#include "model/NavigationData.h"

namespace leniot {

struct ExtrapolatedPosition {
    double latitude;
    double longitude;
};

class ExtrapolationService {
public:
    static ExtrapolatedPosition calculate(const NavigationData& currentData, int secondsAhead = EXTRAP_LOOKAHEAD);
};

}

#endif
