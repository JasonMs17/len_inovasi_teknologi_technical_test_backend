#include "NavigationProcessor.h"
#include "converter/UnitConverter.h"

namespace leniot {

void NavigationProcessor::process(const GpData& data) {
    std::lock_guard<std::mutex> lock(mtx);
    lastGp = data;
}

void NavigationProcessor::process(const GsData& data) {
    std::lock_guard<std::mutex> lock(mtx);
    lastGs = data;
}

void NavigationProcessor::process(const HeData& data) {
    std::lock_guard<std::mutex> lock(mtx);
    lastHe = data;
}

void NavigationProcessor::process(const VeData& data) {
    std::lock_guard<std::mutex> lock(mtx);
    lastVe = data;
}

void NavigationProcessor::process(const PaData& data) {
    std::lock_guard<std::mutex> lock(mtx);
    lastPa = data;
}

bool NavigationProcessor::isExpired(Waktu timestamp, int periodSeconds) const {
    auto now = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - timestamp).count();
    return duration > periodSeconds;
}

NavigationData NavigationProcessor::getCombinedData() const {
    std::lock_guard<std::mutex> lock(mtx);
    NavigationData nav;
    nav.timestamp = std::chrono::steady_clock::now();

    // Lintang & Bujur (Latitude & Longitude)
    if (lastGp && !isExpired(lastGp->timestamp, GP_PERIOD)) {
        nav.latitude = NavField<double>(UnitConverter::ddmToDecimalDegree(lastGp->latitudeDDM, lastGp->latDir), StatusData::Tersedia);
        nav.longitude = NavField<double>(UnitConverter::ddmLonToDecimalDegree(lastGp->longitudeDDM, lastGp->lonDir), StatusData::Tersedia);
    } else if (lastGs && !isExpired(lastGs->timestamp, GS_PERIOD)) {
        nav.latitude = NavField<double>(UnitConverter::ddmToDecimalDegree(lastGs->latitudeDDM, lastGs->latDir), StatusData::Tersedia);
        nav.longitude = NavField<double>(UnitConverter::ddmLonToDecimalDegree(lastGs->longitudeDDM, lastGs->lonDir), StatusData::Tersedia);
    }

    // Arah hadap (Heading)
    if (lastPa && !isExpired(lastPa->timestamp, PA_PERIOD)) {
        nav.heading = NavField<double>(UnitConverter::degreeToRadian(lastPa->headingDegree), StatusData::Tersedia);
    } else if (lastHe && !isExpired(lastHe->timestamp, HE_PERIOD)) {
        nav.heading = NavField<double>(UnitConverter::degreeToRadian(lastHe->headingDegree), StatusData::Tersedia);
    } else if (lastVe && !isExpired(lastVe->timestamp, VE_PERIOD)) {
        nav.heading = NavField<double>(UnitConverter::degreeToRadian(lastVe->headingDegree), StatusData::Tersedia);
    }

    // Kecepatan Relatif (Relative Speed)
    if (lastVe && !isExpired(lastVe->timestamp, VE_PERIOD)) {
        nav.relativeSpeed = NavField<double>(UnitConverter::kmhToMs(lastVe->speedKmh), StatusData::Tersedia);
    }

    // Pitch & Roll
    if (lastPa && !isExpired(lastPa->timestamp, PA_PERIOD)) {
        nav.pitch = NavField<double>(UnitConverter::degreeToRadian(lastPa->pitchDegree), StatusData::Tersedia);
        nav.roll = NavField<double>(UnitConverter::degreeToRadian(lastPa->rollDegree), StatusData::Tersedia);
    }

    // Drift Speed & Course (asumsi tidak tersedia dari kalimat standar)
    nav.driftSpeed = NavField<double>(0.0, StatusData::TidakTersedia);
    nav.driftCourse = NavField<double>(0.0, StatusData::TidakTersedia);

    return nav;
}

}
