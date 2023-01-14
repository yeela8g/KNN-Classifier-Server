#include "Command.h"
#include <fstream>
#include <iostream>
#define BUFFERSIZE 4096

class Upload: public Command{
    public:
        Upload();
        void excecute(int secondSock) override;
        void readFileDownload(int secondSock);
};