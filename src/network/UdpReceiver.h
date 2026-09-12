#ifndef UDP_RECEIVER_H
#define UDP_RECEIVER_H

#include <string>
#include <functional>
#include <thread>
#include <atomic>
#include <cstdint>

namespace leniot {

class UdpReceiver {
public:
    using MessageHandler = std::function<void(const std::string&)>;

    UdpReceiver(int port, MessageHandler handler);
    ~UdpReceiver();

    void start();
    void stop();

private:
    void receiveLoop();

    int port_;
    MessageHandler handler_;
    std::atomic<bool> running_;
    std::thread receiveThread_;
    
#ifdef _WIN32
    uint64_t socket_;
#else
    int socket_;
#endif
};

}

#endif
