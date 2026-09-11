#ifndef STORAGE_SERVICE_H
#define STORAGE_SERVICE_H

#include "model/NavigationData.h"
#include <deque>
#include <vector>
#include <mutex>
#include <optional>

namespace leniot {

class StorageService {
public:
    void addRecord(const NavigationData& data);
    std::vector<NavigationData> getRecords() const;
    std::optional<NavigationData> getLatest() const;

private:
    std::deque<NavigationData> records_;
    mutable std::mutex mutex_;
};

}

#endif
