#include "CLI.h"
#include <iostream>
#include <thread>


CLI::CLI(){
    commands.push_back(new Upload); 
    //add more:
}

void CLI::start(int secondSock){
    while(1){
        sockIO.write("Welcome to the KNN classifier Server. Please choose an option:\n", secondSock);//print welcome message
        sockIO.read(secondSock);//message acknowledge-1
        for(int i=0;i < commands.size();i++){//go through all description and write them
            sockIO.write("1. upload an unclassified csv data file\n", secondSock);
            sockIO.read(secondSock);//message acknowledge-2
        }
        std::string input = sockIO.read(secondSock);//read option answer
        if(input=="8"){
            break;
        }
        int index = input[0]-'0'-1;//excecute the relevant command - sending the secondsock
        commands[index]->excecute(secondSock);
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