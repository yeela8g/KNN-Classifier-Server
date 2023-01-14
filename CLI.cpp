#include "CLI.h"

CLI::CLI(){
    commands[0] = new Upload; 
    //add more:

}

void CLI::start(int secondSock){
    //print welcome message
    sockIO.write("Welcome to the KNN classifier Server. Please choose an option:\n", secondSock);
    //go thorough all description and write them
    for(auto& command : commands)
    sockIO.write(command->getDescription(), secondSock);
    //read answer
    std::string input = sockIO.read(secondSock);
    //excecute the relevant command - sending the secondsock
    int index = input[0]-'0'-1;
    commands[index]->excecute(secondSock);
}

CLI::~CLI(){
    for(auto& command : commands)
        delete command;
}