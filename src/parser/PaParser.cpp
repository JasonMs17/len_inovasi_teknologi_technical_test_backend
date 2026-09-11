#include "PaParser.h"
#include <sstream>
#include <vector>

namespace leniot {

std::optional<PaData> PaParser::parse(const std::string& body) {
    std::vector<std::string> tokens;
    std::stringstream ss(body);
    std::string token;
    
    while (std::getline(ss, token, ',')) {
        tokens.push_back(token);
    }

    if (tokens.size() < 5) return std::nullopt;
    if (tokens[0] != "PA") return std::nullopt;

    try {
        PaData data;
        data.headingDegree = std::stod(tokens[1]);
        data.pitchDegree = std::stod(tokens[3]);
        data.rollDegree = std::stod(tokens[4]);
        data.timestamp = std::chrono::steady_clock::now();
        return data;
    } catch (...) {
        return std::nullopt;
    }
}

}
