#include <gtest/gtest.h>
#include "converter/UnitConverter.h"

using namespace leniot;

TEST(UnitConverterTest, LatDDMToDecimalDegree) {
    EXPECT_NEAR(UnitConverter::ddmToDecimalDegree(4807.038, 'N'), 48.1173, 0.0001);
    EXPECT_NEAR(UnitConverter::ddmToDecimalDegree(4807.038, 'S'), -48.1173, 0.0001);
}

TEST(UnitConverterTest, LonDDMToDecimalDegree) {
    EXPECT_NEAR(UnitConverter::ddmLonToDecimalDegree(1131.000, 'E'), 11.5167, 0.0001);
    EXPECT_NEAR(UnitConverter::ddmLonToDecimalDegree(1131.000, 'W'), -11.5167, 0.0001);
}

TEST(UnitConverterTest, DegreeToRadian) {
    EXPECT_NEAR(UnitConverter::degreeToRadian(180.0), 3.1415926535, 0.0001);
    EXPECT_NEAR(UnitConverter::degreeToRadian(-90.0), -1.5707963268, 0.0001);
}

TEST(UnitConverterTest, KmhToMs) {
    EXPECT_NEAR(UnitConverter::kmhToMs(3.6), 1.0, 0.0001);
    EXPECT_NEAR(UnitConverter::kmhToMs(18.0), 5.0, 0.0001);
}

TEST(UnitConverterTest, KnotsToMs) {
    EXPECT_NEAR(UnitConverter::knotsToMs(1.0), 0.514444, 0.0001);
    EXPECT_NEAR(UnitConverter::knotsToMs(10.0), 5.14444, 0.0001);
}
