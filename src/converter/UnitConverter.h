#ifndef UNIT_CONVERTER_H
#define UNIT_CONVERTER_H

namespace leniot {

class UnitConverter {
public:
    static double ddmToDecimalDegree(double ddm, char direction);
    static double ddmLonToDecimalDegree(double ddm, char direction);
    static double degreeToRadian(double degree);
    static double kmhToMs(double kmh);
    static double knotsToMs(double knots);
};

}

#endif
