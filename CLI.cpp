#include "CLI.h"
#include <iostream>
#include <thread>


CLI::CLI(){
    commands.push_back(new Upload); 
    //add more:

}

void CLI::start(int secondSock){
    while(1){
        //print welcome message
        sockIO.write("Welcome to the KNN classifier Server. Please choose an option:\n", secondSock);
        sockIO.read(secondSock);
        //go thorough all description and write them
        for(int i=0;i < commands.size();i++){
            sockIO.write(commands[i]->description, secondSock);
        }
        sockIO.read(secondSock);
        //read answer
        std::string input = sockIO.read(secondSock);
        if(input=="8"){
            break;
        }
        //excecute the relevant command - sending the secondsock
        int index = input[0]-'0'-1;
        commands[index]->excecute(secondSock);
    }
    if (close(secondSock) < 0){ //close connection eith this client and connect to new client
            perror("ERROR - closing client-specific socket failed: ");
            exit(1);
        }
}

CLI::~CLI(){
    for(auto& command : commands)
        delete command;
}