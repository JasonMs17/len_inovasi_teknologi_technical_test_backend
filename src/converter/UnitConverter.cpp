#include "UnitConverter.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace leniot {

double UnitConverter::ddmToDecimalDegree(double ddm, char direction) {
    int degrees = static_cast<int>(ddm / 100.0);
    double minutes = ddm - (degrees * 100.0);
    double decimalDegree = degrees + (minutes / 60.0);

    if (direction == 'S' || direction == 'W') {
        decimalDegree = -decimalDegree;
    }
    return decimalDegree;
}

double UnitConverter::ddmLonToDecimalDegree(double ddm, char direction) {
    return ddmToDecimalDegree(ddm, direction);
}

double UnitConverter::degreeToRadian(double degree) {
    return degree * M_PI / 180.0;
}

double UnitConverter::kmhToMs(double kmh) {
    return kmh / 3.6;
}

double UnitConverter::knotsToMs(double knots) {
    return knots * 0.514444;
}

}
