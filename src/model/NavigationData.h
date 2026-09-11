#ifndef NAVIGATION_DATA_H
#define NAVIGATION_DATA_H

#include "common/Types.h"

namespace leniot {

template<typename T>
struct NavField {
    T value;
    StatusData status;
    
    NavField() : value(T{}), status(StatusData::TidakTersedia) {}
    NavField(T val, StatusData stat) : value(val), status(stat) {}
};

struct NavigationData {
    NavField<double> latitude;
    NavField<double> longitude;
    NavField<double> heading;
    NavField<double> relativeSpeed;
    NavField<double> pitch;
    NavField<double> roll;
    NavField<double> driftSpeed;
    NavField<double> driftCourse;
    Waktu timestamp;
};

}

#endif
