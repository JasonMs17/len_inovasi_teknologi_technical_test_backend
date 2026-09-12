#include "ExtrapolationService.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace leniot {

ExtrapolatedPosition ExtrapolationService::calculate(const NavigationData& currentData, int secondsAhead) {
    ExtrapolatedPosition pos = {0.0, 0.0};

    // If we don't have lat or lon, we can't extrapolate
    if (currentData.latitude.status != StatusData::Tersedia || 
        currentData.longitude.status != StatusData::Tersedia) {
        return pos;
    }

    pos.latitude = currentData.latitude.value;
    pos.longitude = currentData.longitude.value;

    // If speed or heading is not available, we assume no movement
    if (currentData.relativeSpeed.status != StatusData::Tersedia || 
        currentData.heading.status != StatusData::Tersedia) {
        return pos;
    }

    double speedMs = currentData.relativeSpeed.value;
    double headingRad = currentData.heading.value;

    // Distance = speed * time
    double distanceMeters = speedMs * secondsAhead;

    // Earth radius in meters
    const double R = 6371000.0;

    // Current latitude in radians for the longitude calculation
    double currentLatRad = pos.latitude * M_PI / 180.0;

    // Change in latitude and longitude in radians
    double deltaLatRad = (distanceMeters * std::cos(headingRad)) / R;
    double deltaLonRad = (distanceMeters * std::sin(headingRad)) / (R * std::cos(currentLatRad));

    // Convert back to degrees and add to current position
    pos.latitude += (deltaLatRad * 180.0 / M_PI);
    pos.longitude += (deltaLonRad * 180.0 / M_PI);

    return pos;
}

}
