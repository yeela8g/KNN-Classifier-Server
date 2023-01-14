#ifndef Command_H_
#define Command_H_
#include "SocketIO.h"
#include <string>

class Command{
    protected:
        std::string description;
        SocketIO sio;
    public:
        virtual void excecute(int secondSock) = 0;
        virtual std::string getDescription() = 0;
};
#endif