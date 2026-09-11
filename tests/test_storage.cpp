#include <gtest/gtest.h>
#include "service/StorageService.h"

using namespace leniot;

TEST(StorageServiceTest, AddAndGetRecord) {
    StorageService storage;
    
    NavigationData data1;
    data1.latitude.value = 10.0;
    
    storage.addRecord(data1);
    
    auto records = storage.getRecords();
    ASSERT_EQ(records.size(), 1);
    EXPECT_DOUBLE_EQ(records[0].latitude.value, 10.0);
    
    auto latest = storage.getLatest();
    ASSERT_TRUE(latest.has_value());
    EXPECT_DOUBLE_EQ(latest->latitude.value, 10.0);
}

TEST(StorageServiceTest, MaxRecordsEnforced) {
    StorageService storage;
    
    for (int i = 0; i < 15; ++i) {
        NavigationData data;
        data.latitude.value = static_cast<double>(i);
        storage.addRecord(data);
    }
    
    auto records = storage.getRecords();
    ASSERT_EQ(records.size(), MAX_STORED_RECORDS); // 10
    
    // The oldest 5 should be dropped, so the first one should be 5.0
    EXPECT_DOUBLE_EQ(records.front().latitude.value, 5.0);
    
    // The latest one should be 14.0
    EXPECT_DOUBLE_EQ(records.back().latitude.value, 14.0);
}

TEST(StorageServiceTest, EmptyStorage) {
    StorageService storage;
    
    auto records = storage.getRecords();
    EXPECT_TRUE(records.empty());
    
    auto latest = storage.getLatest();
    EXPECT_FALSE(latest.has_value());
}
