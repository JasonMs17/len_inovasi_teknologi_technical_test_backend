#include <gtest/gtest.h>
#include "service/NavigationProcessor.h"
#include <thread>

using namespace leniot;

TEST(NavigationProcessorTest, GpPriorityOverGs) {
    NavigationProcessor processor;

    GpData gp;
    gp.latitudeDDM = 4807.038;
    gp.latDir = 'N';
    gp.longitudeDDM = 1131.000;
    gp.lonDir = 'E';
    gp.timestamp = std::chrono::steady_clock::now();

    GsData gs;
    gs.latitudeDDM = 1234.567;
    gs.latDir = 'S';
    gs.longitudeDDM = 9876.543;
    gs.lonDir = 'W';
    gs.timestamp = std::chrono::steady_clock::now();

    processor.process(gs);
    processor.process(gp);

    auto result = processor.getCombinedData();
    EXPECT_EQ(result.latitude.status, StatusData::Tersedia);
    EXPECT_NEAR(result.latitude.value, 48.1173, 0.0001); // From GP
}

TEST(NavigationProcessorTest, GpExpiredFallbackToGs) {
    NavigationProcessor processor;

    GpData gp;
    gp.latitudeDDM = 4807.038;
    gp.latDir = 'N';
    gp.longitudeDDM = 1131.000;
    gp.lonDir = 'E';
    // Set GP timestamp to 2 seconds ago (expired since GP period is 1)
    gp.timestamp = std::chrono::steady_clock::now() - std::chrono::seconds(2);

    GsData gs;
    gs.latitudeDDM = 1234.567;
    gs.latDir = 'S';
    gs.longitudeDDM = 9876.543;
    gs.lonDir = 'W';
    // GS is fresh
    gs.timestamp = std::chrono::steady_clock::now();

    processor.process(gs);
    processor.process(gp);

    auto result = processor.getCombinedData();
    EXPECT_EQ(result.latitude.status, StatusData::Tersedia);
    EXPECT_NEAR(result.latitude.value, -12.576116, 0.0001); // From GS
}

TEST(NavigationProcessorTest, HeadingPriority) {
    NavigationProcessor processor;

    HeData he;
    he.headingDegree = 90.0;
    he.timestamp = std::chrono::steady_clock::now();

    VeData ve;
    ve.headingDegree = 180.0;
    ve.timestamp = std::chrono::steady_clock::now();

    PaData pa;
    pa.headingDegree = 45.0;
    pa.timestamp = std::chrono::steady_clock::now();

    processor.process(ve);
    auto res1 = processor.getCombinedData();
    EXPECT_NEAR(res1.heading.value, 3.14159, 0.0001); // VE (180 deg)

    processor.process(he);
    auto res2 = processor.getCombinedData();
    EXPECT_NEAR(res2.heading.value, 1.57079, 0.0001); // HE > VE (90 deg)

    processor.process(pa);
    auto res3 = processor.getCombinedData();
    EXPECT_NEAR(res3.heading.value, 0.78539, 0.0001); // PA > HE > VE (45 deg)
}
