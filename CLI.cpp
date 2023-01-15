#include "CLI.h"
#include <iostream>
#include <thread>


CLI::CLI(){
    commands.push_back(new Upload); 
    commands.push_back(new SettingsKnn); 
    //add more:
}

void CLI::start(int secondSock){
    while(1){
        sockIO.write("Welcome to the KNN classifier Server. Please choose an option:\n", secondSock);
        sockIO.read(secondSock); // message acknowledge
        for(int i=0;i<commands.size();i++){
            sockIO.write(commands[i]->description,secondSock); // print the menu
            sockIO.read(secondSock);//message acknowledge of Menu.
        }
        std::string input = sockIO.read(secondSock);//read option answer
        if(input=="8"){
            break;
        }
        int index = input[0]-'0'-1;
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