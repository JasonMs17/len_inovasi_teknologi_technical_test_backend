#ifndef UDP_RECEIVER_H
#define UDP_RECEIVER_H

#include <string>
#include <functional>
#include <thread>
#include <atomic>

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
    unsigned int socket_;
#else
    int socket_;
#endif
};

}

#endif
