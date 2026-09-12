#include "UdpReceiver.h"
#include "common/Logger.h"

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif

namespace leniot {

UdpReceiver::UdpReceiver(int port, MessageHandler handler)
    : port_(port), handler_(handler), running_(false) {
#ifdef _WIN32
    socket_ = INVALID_SOCKET;
#else
    socket_ = -1;
#endif
}

UdpReceiver::~UdpReceiver() {
    stop();
}

void UdpReceiver::start() {
    if (running_) return;

#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        logger::log(logger::LogLevel::ERROR, "WSAStartup failed for Receiver");
        return;
    }
    socket_ = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (socket_ == INVALID_SOCKET) {
        logger::log(logger::LogLevel::ERROR, "Socket creation failed for Receiver");
        return;
    }
#else
    socket_ = socket(AF_INET, SOCK_DGRAM, 0);
    if (socket_ < 0) {
        logger::log(logger::LogLevel::ERROR, "Socket creation failed for Receiver");
        return;
    }
#endif

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port_);

    if (bind(socket_, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        logger::log(logger::LogLevel::ERROR, "Bind failed for Receiver");
#ifdef _WIN32
        closesocket(socket_);
        socket_ = INVALID_SOCKET;
#else
        close(socket_);
        socket_ = -1;
#endif
        return;
    }

    running_ = true;
    receiveThread_ = std::thread(&UdpReceiver::receiveLoop, this);
}

void UdpReceiver::stop() {
    if (running_) {
        running_ = false;
        
#ifdef _WIN32
        if (socket_ != INVALID_SOCKET) {
            closesocket(socket_);
            socket_ = INVALID_SOCKET;
        }
        WSACleanup();
#else
        if (socket_ >= 0) {
            close(socket_);
            socket_ = -1;
        }
#endif
        
        if (receiveThread_.joinable()) {
            receiveThread_.join();
        }
    }
}

void UdpReceiver::receiveLoop() {
    char buffer[1024];
    while (running_) {
        sockaddr_in clientAddr;
#ifdef _WIN32
        int clientAddrLen = sizeof(clientAddr);
#else
        socklen_t clientAddrLen = sizeof(clientAddr);
#endif

        int bytesReceived = recvfrom(socket_, buffer, sizeof(buffer) - 1, 0,
                                     (sockaddr*)&clientAddr, &clientAddrLen);

        if (bytesReceived > 0) {
            buffer[bytesReceived] = '\0';
            std::string message(buffer);
            if (handler_) {
                handler_(message);
            }
        }
    }
}

}
