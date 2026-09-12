#include "common/Logger.h"
#include "common/Types.h"
#include "parser/ChecksumValidator.h"
#include "parser/LeniotParserFactory.h"
#include "parser/GpParser.h"
#include "parser/GsParser.h"
#include "parser/HeParser.h"
#include "parser/VeParser.h"
#include "parser/PaParser.h"
#include "service/NavigationProcessor.h"
#include "service/StorageService.h"
#include "service/ExtrapolationService.h"
#include "network/UdpReceiver.h"
#include "network/UdpSender.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <sstream>

using namespace leniot;

std::atomic<bool> running{true};

std::string formatNavigationData(const NavigationData& data) {
    std::stringstream ss;
    ss << "{";
    ss << "\"latitude\": " << data.latitude.value << ",";
    ss << "\"longitude\": " << data.longitude.value << ",";
    ss << "\"heading\": " << data.heading.value << ",";
    ss << "\"relativeSpeed\": " << data.relativeSpeed.value << ",";
    ss << "\"pitch\": " << data.pitch.value << ",";
    ss << "\"roll\": " << data.roll.value << ",";
    ss << "\"driftSpeed\": " << data.driftSpeed.value << ",";
    ss << "\"driftCourse\": " << data.driftCourse.value;
    ss << "}";
    return ss.str();
}

std::string formatExtrapolation(const ExtrapolatedPosition& pos) {
    std::stringstream ss;
    ss << "{";
    ss << "\"extrapolated_latitude\": " << pos.latitude << ",";
    ss << "\"extrapolated_longitude\": " << pos.longitude;
    ss << "}";
    return ss.str();
}

int main() {
    logger::log(logger::LogLevel::INFO, "Memulai LENIOT Backend...");

    NavigationProcessor navProcessor;
    StorageService storage;
    
    UdpSender navSender("127.0.0.1", 9001);
    UdpSender extrapSender("127.0.0.1", 9002);

    GpParser gpParser;
    GsParser gsParser;
    HeParser heParser;
    VeParser veParser;
    PaParser paParser;

    auto handleMessage = [&](const std::string& msg) {
        if (!ChecksumValidator::validate(msg)) {
            logger::log(logger::LogLevel::WARNING, "Checksum tidak valid: " + msg);
            return;
        }

        JenisKalimat type = LeniotParserFactory::identifyType(msg);
        
        // Asumsi body dari karakter ke-1 sampai sebelum '*'
        size_t asteriskPos = msg.find_last_of('*');
        if (asteriskPos == std::string::npos || asteriskPos <= 1) return;
        std::string body = msg.substr(1, asteriskPos - 1);

        switch (type) {
            case JenisKalimat::GP: {
                auto data = gpParser.parse(body);
                if (data) navProcessor.process(*data);
                break;
            }
            case JenisKalimat::GS: {
                auto data = gsParser.parse(body);
                if (data) navProcessor.process(*data);
                break;
            }
            case JenisKalimat::HE: {
                auto data = heParser.parse(body);
                if (data) navProcessor.process(*data);
                break;
            }
            case JenisKalimat::VE: {
                auto data = veParser.parse(body);
                if (data) navProcessor.process(*data);
                break;
            }
            case JenisKalimat::PA: {
                auto data = paParser.parse(body);
                if (data) navProcessor.process(*data);
                break;
            }
            default:
                logger::log(logger::LogLevel::WARNING, "Tipe tidak dikenal: " + msg);
                break;
        }
        
        storage.addRecord(navProcessor.getCombinedData());
    };

    UdpReceiver receiver(8080, handleMessage);
    receiver.start();
    logger::log(logger::LogLevel::INFO, "UDP Receiver berjalan di port 8080...");

    std::thread navSenderThread([&]() {
        while (running) {
            std::this_thread::sleep_for(std::chrono::seconds(NAV_SEND_INTERVAL));
            auto latest = storage.getLatest();
            if (latest) {
                std::string payload = formatNavigationData(*latest);
                navSender.send(payload);
                logger::log(logger::LogLevel::INFO, "Mengirim data navigasi");
            }
        }
    });

    std::thread extrapSenderThread([&]() {
        while (running) {
            std::this_thread::sleep_for(std::chrono::seconds(EXTRAP_SEND_INTERVAL));
            auto latest = storage.getLatest();
            if (latest) {
                auto pos = ExtrapolationService::calculate(*latest, EXTRAP_LOOKAHEAD);
                std::string payload = formatExtrapolation(pos);
                extrapSender.send(payload);
                logger::log(logger::LogLevel::INFO, "Mengirim data ekstrapolasi");
            }
        }
    });

    std::cout << "Tekan Enter untuk menghentikan program...\n";
    std::cin.get();

    running = false;
    receiver.stop();
    
    if (navSenderThread.joinable()) navSenderThread.join();
    if (extrapSenderThread.joinable()) extrapSenderThread.join();

    logger::log(logger::LogLevel::INFO, "LENIOT Backend berhenti.");
    return 0;
}
