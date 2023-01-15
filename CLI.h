#include <unistd.h>
#include <cstdio>
#include "SocketIO.h"
#include "Command.h"
#include "Upload.h"
#include <vector>
#include "SettingsKnn.h"



class CLI{
    private:
        std::vector<Command*> commands;
        SocketIO sockIO;
    public:
        CLI();
        ~CLI();
        void start(int secondSock);
};
