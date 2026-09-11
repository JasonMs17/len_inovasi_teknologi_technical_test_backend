#include <gtest/gtest.h>
#include "parser/ChecksumValidator.h"

using namespace leniot;

TEST(ChecksumValidatorTest, ValidChecksums) {
    EXPECT_TRUE(ChecksumValidator::validate("$GP,4807.038,N,01131.000,E*2E"));
    EXPECT_TRUE(ChecksumValidator::validate("$GS,01131.000,E,4807.038,N*2D"));
    EXPECT_TRUE(ChecksumValidator::validate("$HE,123.456,T*70"));
    EXPECT_TRUE(ChecksumValidator::validate("$VE,5.5,K,3.0,N,123.45,T*5E"));
    EXPECT_TRUE(ChecksumValidator::validate("$PA,123.456,T,-0.5,20.0*76"));
}

TEST(ChecksumValidatorTest, InvalidChecksum) {
    EXPECT_FALSE(ChecksumValidator::validate("$GP,4807.038,N,01131.000,E*FF"));
    EXPECT_FALSE(ChecksumValidator::validate("$HE,123.456,T*00"));
}

TEST(ChecksumValidatorTest, MalformedSentence) {
    EXPECT_FALSE(ChecksumValidator::validate("GP,4807.038,N,01131.000,E*2E")); // Missing $
    EXPECT_FALSE(ChecksumValidator::validate("$GP,4807.038,N,01131.000,E2E"));  // Missing *
    EXPECT_FALSE(ChecksumValidator::validate("$GP,4807.038,N,01131.000,E*"));   // Missing checksum value
    EXPECT_FALSE(ChecksumValidator::validate(""));                              // Empty
    EXPECT_FALSE(ChecksumValidator::validate("$*00"));                          // No body
}
