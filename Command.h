#ifndef Command_H_
#define Command_H_
#include "SocketIO.h"
#include <string>

class Command{
    protected:
        SocketIO sio;
    public:
        std::string description;
        virtual void excecute(int secondSock) = 0;
};
#endif