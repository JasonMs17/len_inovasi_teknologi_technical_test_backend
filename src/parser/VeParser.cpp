#include "VeParser.h"
#include <sstream>
#include <vector>

namespace leniot {

std::optional<VeData> VeParser::parse(const std::string& body) {
    std::vector<std::string> tokens;
    std::stringstream ss(body);
    std::string token;
    
    while (std::getline(ss, token, ',')) {
        tokens.push_back(token);
    }

    if (tokens.size() < 7) return std::nullopt;
    if (tokens[0] != "VE") return std::nullopt;

    try {
        VeData data;
        data.speedKmh = std::stod(tokens[1]);
        data.speedKnots = std::stod(tokens[3]);
        data.headingDegree = std::stod(tokens[5]);
        data.timestamp = std::chrono::steady_clock::now();
        return data;
    } catch (...) {
        return std::nullopt;
    }
}

}
