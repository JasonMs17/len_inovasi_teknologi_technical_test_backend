#ifndef NAVIGATION_PROCESSOR_H
#define NAVIGATION_PROCESSOR_H

#include "model/LeniotSentence.h"
#include "model/NavigationData.h"
#include <mutex>
#include <optional>

namespace leniot {

class NavigationProcessor {
public:
    void process(const GpData& data);
    void process(const GsData& data);
    void process(const HeData& data);
    void process(const VeData& data);
    void process(const PaData& data);

    NavigationData getCombinedData() const;

private:
    bool isExpired(Waktu timestamp, int periodSeconds) const;

    std::optional<GpData> lastGp;
    std::optional<GsData> lastGs;
    std::optional<HeData> lastHe;
    std::optional<VeData> lastVe;
    std::optional<PaData> lastPa;

    mutable std::mutex mtx;
};

}

#endif
