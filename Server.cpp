#include "MyServer.h"
#include <stdexcept>

int main(int argc, char* argv[]){ //port
    if(argc == 2){
        int port;
        try {
            port = std::stoi(argv[1]); //check port is integer
        } catch(...){
            throw std::runtime_error("invalid port1"); //not digit
        }
        if (port <= 0 || port >= 65536){ //check port is in the right range
            throw std::runtime_error("invalid port2");
        }else{
            MyServer myServer(port);//cli;
            myServer.communicate();
        }
    } else {
        throw std::runtime_error("invalid input"); //unvalid number of arguments
    }
}

    