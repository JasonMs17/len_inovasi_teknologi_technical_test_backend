#include "GsParser.h"
#include <sstream>
#include <vector>

namespace leniot {

std::optional<GsData> GsParser::parse(const std::string& body) {
    std::vector<std::string> tokens;
    std::stringstream ss(body);
    std::string token;
    
    while (std::getline(ss, token, ',')) {
        tokens.push_back(token);
    }

    if (tokens.size() < 5) return std::nullopt;
    if (tokens[0] != "GS") return std::nullopt;

    try {
        GsData data;
        data.longitudeDDM = std::stod(tokens[1]);
        data.lonDir = tokens[2].empty() ? 'E' : tokens[2][0];
        data.latitudeDDM = std::stod(tokens[3]);
        data.latDir = tokens[4].empty() ? 'N' : tokens[4][0];
        data.timestamp = std::chrono::steady_clock::now();
        return data;
    } catch (...) {
        return std::nullopt;
    }
}

}
