#ifndef UDP_SENDER_H
#define UDP_SENDER_H

#include <string>

namespace leniot {

class UdpSender {
public:
    UdpSender(const std::string& ipAddress, int port);
    ~UdpSender();

    bool send(const std::string& message);

private:
    std::string ipAddress_;
    int port_;
    
#ifdef _WIN32
    unsigned int socket_;
#else
    int socket_;
#endif
};

}

#endif
