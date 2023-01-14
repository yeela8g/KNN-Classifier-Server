#include <stdexcept>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>
#include "SocketIO.h"
#include <fstream>
#include <sys/stat.h>


#define BUFFERSIZE 4096

class MyClient{
private:
    SocketIO sio;
public:
    MyClient();//constructor
    void communicate(std::string ip,int port);
    void uploadToServer(int socket);
    void manageUploadCommunication(int socket);

};