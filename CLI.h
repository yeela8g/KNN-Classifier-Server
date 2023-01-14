#include "SocketIO.h"
#include "Command.h"
#include "Upload.h"


class CLI{
    private:
        Command* commands[1]; //change to five!!!!!
        SocketIO sockIO;
    public:
        CLI();
        ~CLI();
        void start(int secondSock);
};
