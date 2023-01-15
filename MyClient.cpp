# include "MyClient.h"



MyClient::MyClient(){} //constructor

void MyClient::communicate(std::string ip,int port){

    int sock= socket(AF_INET, SOCK_STREAM, 0); //create a TCP socket 
    if(sock < 0){
        perror("couldn't create socket");
        exit(1);
    }
    std::cout<<"created socket"<<std::endl;
    struct sockaddr_in clientAdress; //create client address details struct
    memset(&clientAdress,0, sizeof(clientAdress));
    clientAdress.sin_family = AF_INET;
    clientAdress.sin_port = htons(port);
    if (inet_aton(ip.c_str(), &clientAdress.sin_addr) == 0){
        throw std::invalid_argument("IP Address is not valid");
    }
    if (connect(sock, (struct sockaddr *)&clientAdress, sizeof(clientAdress)) < 0){//connect to server
        perror("Could not connect to server");
        exit(1);
    }
    std::cout<<"connect to server"<<std::endl;
    while (1){
        std::cout<<sio.read(sock); // print welcome
        sio.write("got one", sock);
        for (int i=0 ;i<3;i++){ // change to 5!!!!!!!!!!!!!!!!!
            std::cout<<sio.read(sock); // print menu
            sio.write("got one", sock);
        }
        std::string data;
        std::getline(std::cin,data);
        while (data != "1" && data != "2" && data != "3" && data != "4" && data != "5" && data != "8"){
            std::cout <<"invalid input"<<std::endl;
            std::getline(std::cin,data);
        }
        if(send(sock,data.c_str(),strlen(data.c_str()),0) < 0) {//send input to server
            perror("error sending message to client");
        }
        switch (std::stoi(data)){
            case 1:
                manageUploadCommunication(sock);
                break;
            case 2:
                manageKnnParameters(sock);
                break;
            case 3:
                std::cout<<sio.read(sock)<<std::endl;
                break;
            case 4:
                break;
            case 5:
                break;
            case 8:
                close(sock);
                exit(0);
            break;
        }
    }
}


void MyClient::manageUploadCommunication(int socket){
    std::cout<<sio.read(socket)<<std::endl; // server ask to upload 
    uploadToServer(socket); // upload to server
    std::cout<<sio.read(socket)<<std::endl; // upload complet
    sio.write("got msg complet download file1",socket);
    std::cout<<sio.read(socket)<<std::endl;// server ask to upload test CSV 
    uploadToServer(socket);
}

void MyClient::uploadToServer(int socket){
    std::string path;
    std::getline(std::cin,path);
    struct stat st;
    int status = 0;
    status = stat(path.c_str(), &st);
    while(status == -1){
        std::cout << "The path is not legal" << std::endl;
        std::getline(std::cin,path);
        status = stat(path.c_str(), &st);
    }
    std::string file_name = path;
    std::ifstream in_file(file_name,std::ios::binary);
    char buffer[BUFFERSIZE];
    while(in_file){
        memset(buffer,0,BUFFERSIZE);
        in_file.read(buffer,BUFFERSIZE);
        sio.write(buffer,socket);
        std::cout << "client sent buffer.." << std::endl;
    }
    in_file.close();
}

void MyClient::manageKnnParameters(int socket){
    std::cout<<sio.read(socket); // print The current KNN parameters
    std::string input; //get input for changing+for what or not changing the parameters
    std::getline(std::cin,input);
    if(input.empty()){ // if the client press enter return to menu
        sio.write("0",socket);
        sio.read(socket);
        return;
    }
    // separet the string to K and matric
    std::vector<std::string> separatedStr;
    std::stringstream ss(input);  //wrapping line for the getline function
    std::string word;
    while(std::getline(ss, word, ' ')){  //separetad each line by space into the container
        separatedStr.push_back(word);
    }
    if (separatedStr.size() < 2){//less arguments entered
        std::cout<<"invalid input"<<std::endl;
        sio.write("0",socket);
        sio.read(socket);
        return;
    }
    bool kFlag = 1; //check k is number,integer and 1+
    InputValidation in;
    in.isNumber(separatedStr[0]);//valid k
    if (in.getValid()== false){
        kFlag = 0;
    } else {
        if(std::stoi(separatedStr[0])!= std::stod(separatedStr[0])){//check k is integer
            kFlag = 0;
        }
        if (std::stoi(separatedStr[0])<1){ //check k is 1+
            kFlag = 0;
        }
    }
    if (!kFlag){
        std::cout<<"invalid value for k"<<std::endl;
    }
    bool matricFlag = 1; //check valid metric
     if(separatedStr[1]!="AUC" && separatedStr[1]!="CHB" && separatedStr[1]!="CAN" && separatedStr[1]!="MIN" && separatedStr[1]!="MAN"){
        matricFlag = 0;
        std::cout<<"invalid value for metric"<<std::endl;
    }
    if(!kFlag || !matricFlag){
        sio.write("0",socket);
        sio.read(socket);// acknowledge
        return;
    }
    sio.write("1",socket);
    sio.read(socket);// acknowledge
    sio.write(separatedStr[0],socket); // send K
    sio.read(socket);// acknowledge
    sio.write(separatedStr[1],socket); // send matric
}


