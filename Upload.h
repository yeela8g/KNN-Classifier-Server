#include "Command.h"
#define BUFFERSIZE 4096

class Upload: public Command{
    public:
        Upload();
        void excecute(int secondSock) override;
        std::string getDescription() override;
        void readFileDownload(int secondSock);
};