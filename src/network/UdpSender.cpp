#include "UdpSender.h"
#include "common/Logger.h"
#include <iostream>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#undef ERROR
#pragma comment(lib, "ws2_32.lib")
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif

namespace leniot {

UdpSender::UdpSender(const std::string& ipAddress, int port) 
    : ipAddress_(ipAddress), port_(port) {
    
#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        logger::log(logger::LogLevel::ERROR, "WSAStartup failed");
        socket_ = (uint64_t)INVALID_SOCKET;
        return;
    }
    socket_ = (uint64_t)socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if ((SOCKET)socket_ == INVALID_SOCKET) {
        logger::log(logger::LogLevel::ERROR, "Socket creation failed");
    }
#else
    socket_ = socket(AF_INET, SOCK_DGRAM, 0);
    if (socket_ < 0) {
        logger::log(logger::LogLevel::ERROR, "Socket creation failed");
    }
#endif
}

UdpSender::~UdpSender() {
#ifdef _WIN32
    if ((SOCKET)socket_ != INVALID_SOCKET) {
        closesocket((SOCKET)socket_);
    }
    WSACleanup();
#else
    if (socket_ >= 0) {
        close(socket_);
    }
#endif
}

bool UdpSender::send(const std::string& message) {
#ifdef _WIN32
    if ((SOCKET)socket_ == INVALID_SOCKET) return false;
#else
    if (socket_ < 0) return false;
#endif

    sockaddr_in destAddr;
    destAddr.sin_family = AF_INET;
    destAddr.sin_port = htons(port_);
    
#ifdef _WIN32
    destAddr.sin_addr.s_addr = inet_addr(ipAddress_.c_str());
#else
    inet_pton(AF_INET, ipAddress_.c_str(), &destAddr.sin_addr);
#endif

    int result = sendto((SOCKET)socket_, message.c_str(), message.length(), 0,
                        (sockaddr*)&destAddr, sizeof(destAddr));
                        
    if (result < 0) {
        logger::log(logger::LogLevel::ERROR, "Failed to send UDP message");
        return false;
    }
    
    return true;
}

}
