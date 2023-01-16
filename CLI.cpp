#include "CLI.h"
#include <iostream>
#include <thread>


CLI::CLI(){
    commands.push_back(new Upload); 
    commands.push_back(new SettingsKnn); 
    commands.push_back(new Classify);
    //add more:
}

void CLI::start(int secondSock){
    Classify* classify = static_cast<Classify*>(commands[2]); //casting to Classify 
    SettingsKnn* setting = static_cast<SettingsKnn*>(commands[1]); //casting to SettingsKnn 
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
        if(index == 1){
            classify->setMatric(setting->getMatric()); // update the matric for knn
            classify->setK(setting->getK());// update the k for knn
        }
    }
    if (close(secondSock) < 0){ //close connection eith this client and connect to new client
            perror("ERROR - closing client-specific socket failed: ");
            exit(1);
    }
    std::string trainFile = "out1" + std::to_string(secondSock)+"train"; //delete the files after client disconnected.
    std::string testFile = "out1" + std::to_string(secondSock)+"test";
    std::string classifyFile = "out1" + std::to_string(secondSock) + "testClassified";
    remove(trainFile.c_str());
    remove(testFile.c_str());
    remove(classifyFile.c_str());
}


CLI::~CLI(){
    for(auto& command : commands)
        delete command;
}