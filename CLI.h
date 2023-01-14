#include <unistd.h>
#include "SocketIO.h"
#include "Command.h"
#include "Upload.h"
#include <vector>



class CLI{
    private:
        std::vector<Command*> commands;
        SocketIO sockIO;
    public:
        CLI();
        ~CLI();
        void start(int secondSock);
};
