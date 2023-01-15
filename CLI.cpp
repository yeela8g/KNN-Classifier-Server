#include "CLI.h"
#include <iostream>
#include <thread>


CLI::CLI(){
    commands.push_back(new Upload); 
    //add more:
}

void CLI::start(int secondSock){
    while(1){
        //add more
        sockIO.write("Welcome to the KNN classifier Server. Please choose an option:\n1. upload an unclassified csv data file\n", secondSock);
        sockIO.read(secondSock);//message acknowledge of Menu.
        std::string input = sockIO.read(secondSock);//read option answer
        //add more
        if(input == "1"){
            Upload upload;
            upload.excecute(secondSock);
        }else if(input=="8"){
            break;
        }
    }
    if (close(secondSock) < 0){ //close connection eith this client and connect to new client
            perror("ERROR - closing client-specific socket failed: ");
            exit(1);
    }
    std::string trainFile = "out1" + std::to_string(secondSock)+"train"; //delete the files after client disconnected.
    std::string testFile = "out1" + std::to_string(secondSock)+"test";
    remove(trainFile.c_str());
    remove(testFile.c_str());
}


CLI::~CLI(){
    for(auto& command : commands)
        delete command;
}