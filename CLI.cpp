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
        std::cout << std::this_thread::get_id() << std::endl;
        sockIO.write("Welcome to the KNN classifier Server. Please choose an option:\n", secondSock);
         std::cout << "after the write funtion"<<std::endl;
        //go thorough all description and write them
        for(int i=0;i < commands.size();i++){
            std::cout << "in the for loop"<< std::endl;
            std::cout<< commands[i]->description;
            sockIO.write(commands[i]->description, secondSock);
        }
        std::cout << "after manu"<< std::endl;
        //read answer
        std::string input = sockIO.read(secondSock);
        std::cout << "input : "<< input<< std::endl;
        if(input=="8"){
            break;
        }
        //excecute the relevant command - sending the secondsock
        int index = input[0]-'0'-1;
        std::cout << "index : "<< index<< std::endl;
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