#ifndef TYPES_H
#define TYPES_H

#include <chrono>

namespace leniot {

enum class StatusData { 
    Tersedia, 
    TidakTersedia 
};

enum class JenisKalimat { 
    GP, 
    GS, 
    HE, 
    VE, 
    PA, 
    TidakDikenal 
};

constexpr int GP_PERIOD = 1;
constexpr int GS_PERIOD = 2;
constexpr int HE_PERIOD = 2;
constexpr int VE_PERIOD = 2;
constexpr int PA_PERIOD = 1;

constexpr int NAV_SEND_INTERVAL = 3;
constexpr int EXTRAP_SEND_INTERVAL = 5;
constexpr int EXTRAP_LOOKAHEAD = 5;
constexpr int MAX_STORED_RECORDS = 10;

using Waktu = std::chrono::steady_clock::time_point;

}

#endif
