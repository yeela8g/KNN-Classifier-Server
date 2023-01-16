#include "Command.h"
#include <fstream>
#include <iostream>
#include <thread>
#include <sstream>
#include <unistd.h>

#define BUFFERSIZE 4096

class Upload: public Command{
    public:
        Upload();
        void excecute(int secondSock) override;
        void readFileDownload(int secondSock, std::string fileType);
};