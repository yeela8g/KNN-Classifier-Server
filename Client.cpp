#include <stdexcept>
#include "MyClient.h"

int main(int argc, char *argv[]){
    if (argc != 3) { //validation ro argument number.
        throw std::runtime_error("invalid input");
    } 
    int port; //validation to port value.
    try {
        port = std::stoi(argv[2]);//port is integer
    } catch(...){
        throw std::runtime_error("invalid port");
    }
    if (port <= 0 || port >= 65536){//port is in range
        throw std::runtime_error("invalid port");
    } 
    MyClient client;
    client.communicate(argv[1],port);
}