#ifndef Command_H_
#define Command_H_
#include "SocketIO.h"
#include <string>

class Command{
   
    public:
        SocketIO sio; //object to write and read over the socket
        std::string description; //description of the command
        virtual void excecute(int secondSock) = 0; //excecute the command
};
#endif