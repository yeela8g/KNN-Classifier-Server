#ifndef SocketIO_H_
#define SocketIO_H_
#include "DefaultIO.h"
#include <sys/socket.h>
#include <cstring>

#define BUFFERSIZE 4096


class SocketIO : public DefaultIO {
    public :
        SocketIO();
        std::string read(int secondSock) override;
        void write(std::string text, int secondSock) override;
};
#endif