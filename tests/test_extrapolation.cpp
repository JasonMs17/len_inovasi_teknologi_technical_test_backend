#include <gtest/gtest.h>
#include "service/ExtrapolationService.h"
#include "converter/UnitConverter.h"

using namespace leniot;

TEST(ExtrapolationServiceTest, NoMovementWithoutSpeedOrHeading) {
    NavigationData data;
    data.latitude = NavField<double>(10.0, StatusData::Tersedia);
    data.longitude = NavField<double>(20.0, StatusData::Tersedia);
    
    // Kecepatan dan heading tidak tersedia
    auto pos = ExtrapolationService::calculate(data);
    EXPECT_DOUBLE_EQ(pos.latitude, 10.0);
    EXPECT_DOUBLE_EQ(pos.longitude, 20.0);
}

TEST(ExtrapolationServiceTest, MoveNorth) {
    NavigationData data;
    data.latitude = NavField<double>(0.0, StatusData::Tersedia);
    data.longitude = NavField<double>(0.0, StatusData::Tersedia);
    data.relativeSpeed = NavField<double>(10.0, StatusData::Tersedia); // 10 m/s
    data.heading = NavField<double>(0.0, StatusData::Tersedia); // 0 rad = North

    // Jarak = 50 meter ke utara
    auto pos = ExtrapolationService::calculate(data, 5);
    
    // Harus bertambah di latitude, longitude tetap
    EXPECT_GT(pos.latitude, 0.0);
    EXPECT_DOUBLE_EQ(pos.longitude, 0.0);
}

TEST(ExtrapolationServiceTest, MoveEast) {
    NavigationData data;
    data.latitude = NavField<double>(0.0, StatusData::Tersedia);
    data.longitude = NavField<double>(0.0, StatusData::Tersedia);
    data.relativeSpeed = NavField<double>(10.0, StatusData::Tersedia); // 10 m/s
    data.heading = NavField<double>(UnitConverter::degreeToRadian(90.0), StatusData::Tersedia); // 90 deg = East

    auto pos = ExtrapolationService::calculate(data, 5);
    
    // Harus bertambah di longitude, latitude hampir 0 (karena float precision)
    EXPECT_NEAR(pos.latitude, 0.0, 0.0001);
    EXPECT_GT(pos.longitude, 0.0);
}

TEST(ExtrapolationServiceTest, MoveSouth) {
    NavigationData data;
    data.latitude = NavField<double>(0.0, StatusData::Tersedia);
    data.longitude = NavField<double>(0.0, StatusData::Tersedia);
    data.relativeSpeed = NavField<double>(10.0, StatusData::Tersedia);
    data.heading = NavField<double>(UnitConverter::degreeToRadian(180.0), StatusData::Tersedia); // South

    auto pos = ExtrapolationService::calculate(data, 5);
    
    EXPECT_LT(pos.latitude, 0.0);
    EXPECT_NEAR(pos.longitude, 0.0, 0.0001);
}
