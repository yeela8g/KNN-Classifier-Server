#ifndef Command_H_
#define Command_H_
#include "SocketIO.h"
#include <string>

class Command{
   
    public:
        SocketIO sio;
        std::string description;
        virtual void excecute(int secondSock) = 0;
};
#endif