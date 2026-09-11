#include "StorageService.h"

namespace leniot {

void StorageService::addRecord(const NavigationData& data) {
    std::lock_guard<std::mutex> lock(mutex_);
    
    if (records_.size() >= MAX_STORED_RECORDS) {
        records_.pop_front();
    }
    
    records_.push_back(data);
}

std::vector<NavigationData> StorageService::getRecords() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return std::vector<NavigationData>(records_.begin(), records_.end());
}

std::optional<NavigationData> StorageService::getLatest() const {
    std::lock_guard<std::mutex> lock(mutex_);
    if (records_.empty()) {
        return std::nullopt;
    }
    return records_.back();
}

}
