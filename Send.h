# include "Command.h"
#include <unistd.h>
#include <fstream>

class Send :public Command{
    public:
        Send();
        void excecute(int secondSock) override; 
};