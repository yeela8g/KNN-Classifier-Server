#include <stdexcept>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>
#include "SocketIO.h"
#include <fstream>
#include <sys/stat.h>
#include <list>
#include <sstream>
#include <vector>
#include <thread>
#include"InputValidation.h"
#include <iostream>
#include <chrono>
#include <mutex>

#define BUFFERSIZE 4096

class MyClient{
private:
    SocketIO sio;
public:
    MyClient();//constructor
    void communicate(std::string ip,int port);
    void uploadToServer(int socket,std::string path);
    bool checkPath(int socket, std::string &path);
    void manageUploadCommunication(int socket);
    void manageKnnParameters(int socket);
    void getClassifications(int socket);
    void downloadClassifications(int socket);

};