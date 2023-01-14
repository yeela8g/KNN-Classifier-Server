#include <string>
#include <thread>
#include <vector>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include "CLI.h"
#include <iostream>

#define MAX_CLIENT 5

class MyServer{
    private:
        std::vector<std::thread> threads;
        int port;
        CLI cli;
    public:
        MyServer(int prt);
        void communicate();

};