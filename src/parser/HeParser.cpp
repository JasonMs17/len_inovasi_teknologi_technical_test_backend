#include "HeParser.h"
#include <sstream>
#include <vector>

namespace leniot {

std::optional<HeData> HeParser::parse(const std::string& body) {
    std::vector<std::string> tokens;
    std::stringstream ss(body);
    std::string token;
    
    while (std::getline(ss, token, ',')) {
        tokens.push_back(token);
    }

    if (tokens.size() < 3) return std::nullopt;
    if (tokens[0] != "HE") return std::nullopt;

    try {
        HeData data;
        data.headingDegree = std::stod(tokens[1]);
        data.timestamp = std::chrono::steady_clock::now();
        return data;
    } catch (...) {
        return std::nullopt;
    }
}

}
