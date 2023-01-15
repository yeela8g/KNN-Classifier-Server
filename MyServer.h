#include <string>
#include <thread>
#include <vector>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include "CLI.h"
#include <iostream>
#include <pthread.h>

#define MAX_CLIENT 5

class MyServer{
    private:
        int port;
    public:
        MyServer(int prt);
        void communicate();

};