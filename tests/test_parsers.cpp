#include <gtest/gtest.h>
#include "parser/GpParser.h"
#include "parser/GsParser.h"
#include "parser/HeParser.h"
#include "parser/VeParser.h"
#include "parser/PaParser.h"
#include "parser/LeniotParserFactory.h"

using namespace leniot;

TEST(ParserTest, GpParserTest) {
    GpParser parser;
    auto result = parser.parse("GP,4807.038,N,01131.000,E");
    ASSERT_TRUE(result.has_value());
    EXPECT_DOUBLE_EQ(result->latitudeDDM, 4807.038);
    EXPECT_EQ(result->latDir, 'N');
    EXPECT_DOUBLE_EQ(result->longitudeDDM, 01131.000);
    EXPECT_EQ(result->lonDir, 'E');
}

TEST(ParserTest, GsParserTest) {
    GsParser parser;
    auto result = parser.parse("GS,01131.000,E,4807.038,N");
    ASSERT_TRUE(result.has_value());
    EXPECT_DOUBLE_EQ(result->longitudeDDM, 01131.000);
    EXPECT_EQ(result->lonDir, 'E');
    EXPECT_DOUBLE_EQ(result->latitudeDDM, 4807.038);
    EXPECT_EQ(result->latDir, 'N');
}

TEST(ParserTest, HeParserTest) {
    HeParser parser;
    auto result = parser.parse("HE,123.456,T");
    ASSERT_TRUE(result.has_value());
    EXPECT_DOUBLE_EQ(result->headingDegree, 123.456);
}

TEST(ParserTest, VeParserTest) {
    VeParser parser;
    auto result = parser.parse("VE,5.5,K,3.0,N,123.45,T");
    ASSERT_TRUE(result.has_value());
    EXPECT_DOUBLE_EQ(result->speedKmh, 5.5);
    EXPECT_DOUBLE_EQ(result->speedKnots, 3.0);
    EXPECT_DOUBLE_EQ(result->headingDegree, 123.45);
}

TEST(ParserTest, PaParserTest) {
    PaParser parser;
    auto result = parser.parse("PA,123.456,T,-0.5,20.0");
    ASSERT_TRUE(result.has_value());
    EXPECT_DOUBLE_EQ(result->headingDegree, 123.456);
    EXPECT_DOUBLE_EQ(result->pitchDegree, -0.5);
    EXPECT_DOUBLE_EQ(result->rollDegree, 20.0);
}

TEST(ParserTest, ParserFactoryTest) {
    EXPECT_EQ(LeniotParserFactory::identifyType("$GP,4807.038,N,01131.000,E*2E"), JenisKalimat::GP);
    EXPECT_EQ(LeniotParserFactory::identifyType("$GS,01131.000,E,4807.038,N*2D"), JenisKalimat::GS);
    EXPECT_EQ(LeniotParserFactory::identifyType("$HE,123.456,T*70"), JenisKalimat::HE);
    EXPECT_EQ(LeniotParserFactory::identifyType("$VE,5.5,K,3.0,N,123.45,T*5E"), JenisKalimat::VE);
    EXPECT_EQ(LeniotParserFactory::identifyType("$PA,123.456,T,-0.5,20.0*76"), JenisKalimat::PA);
    EXPECT_EQ(LeniotParserFactory::identifyType("$XX,123"), JenisKalimat::TidakDikenal);
    EXPECT_EQ(LeniotParserFactory::identifyType("INVALID"), JenisKalimat::TidakDikenal);
}
