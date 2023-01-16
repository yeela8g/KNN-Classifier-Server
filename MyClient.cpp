# include "MyClient.h"



MyClient::MyClient(){} //constructor

void MyClient::communicate(std::string ip,int port){

    int sock= socket(AF_INET, SOCK_STREAM, 0); //create a TCP socket 
    if(sock < 0){
        perror("couldn't create socket");
        exit(1);
    }
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
    while (1){
        std::cout<<sio.read(sock); // print welcome
        sio.write("got one", sock);
        for (int i=0 ;i<5;i++){ 
            std::cout<<sio.read(sock); // print menu
            sio.write("got one", sock);
        }

        std::string data;
        std::getline(std::cin,data);//get option choise from user.
        while (data != "1" && data != "2" && data != "3" && data != "4" && data != "5" && data != "8"){
            std::cout <<"invalid input"<<std::endl;
            std::getline(std::cin,data);
        }
        if(send(sock,data.c_str(),strlen(data.c_str()),0) < 0) {//send input to server
            perror("error sending message to client");
        }

        switch (std::stoi(data)){
            case 1:
                manageUploadCommunication(sock);//uplode csv files
                break;
            case 2:
                manageKnnParameters(sock); //set parameter of the knn algorithm
                break;
            case 3:
                std::cout<<sio.read(sock)<<std::endl; //classify vectors
                break;
            case 4:
                getClassifications(sock); //get classificasion from server
                break;
            case 5:
            {
                std::thread t(&MyClient::downloadClassifications,this,sock);//send thread to download classifications File to the user computer
                t.join(); //avoiding overriding the file data with the menu data 
                break;
            }
            case 8:
                close(sock); //disconnect from server
                exit(0);
            break;
        }
    }
}


void MyClient::manageUploadCommunication(int socket){
    std::cout<<sio.read(socket)<<std::endl; // server ask to upload 
    std::string path;
    bool FileFlag = checkPath(socket,path);
    sio.write(std::to_string(FileFlag),socket);
    if(FileFlag){
        sio.read(socket); // acknowledge
        uploadToServer(socket,path); // upload to server
        std::cout<<sio.read(socket)<<std::endl; // upload complet
        sio.write("got msg complet download file1",socket);// acknowledge
        std::cout<<sio.read(socket)<<std::endl;// server ask to upload test CSV 
        FileFlag = checkPath(socket,path);
        sio.write(std::to_string(FileFlag),socket);
        if(FileFlag){
            sio.read(socket);// acknowledge
            uploadToServer(socket,path);
        }
    }
}

bool MyClient::checkPath(int socket ,std::string &path){ //check path is valid
    std::getline(std::cin,path);
    struct stat st;
    int status = 0;
    status = stat(path.c_str(), &st);
    if(status == -1){
        std::cout << "invalid input" << std::endl;
        return 0;
    }
    return 1;
}

void MyClient::uploadToServer(int socket,std::string path){ //send the this path file to the server
    std::string file_name = path;
    std::ifstream in_file(file_name,std::ios::binary);
    char buffer[BUFFERSIZE];
    while(in_file){
        memset(buffer,0,BUFFERSIZE);
        in_file.read(buffer,BUFFERSIZE);
        sio.write(buffer,socket);
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

void MyClient::getClassifications(int socket){
    std::string feedback = sio.read(socket); // if the server is going to dend classifications
    if(feedback != "1"){
        std::cout<<feedback<<std::endl;
        return;
    }
    sio.write("feedback accepted",socket);
    char buffer[BUFFERSIZE];
    while(1){
        memset(buffer, 0, BUFFERSIZE);
        int bytes_received = recv(socket,buffer, BUFFERSIZE, 0);
        if(bytes_received == 0){  // Read no bytes - either connection has closed or client taking too long // Let's exit
            break; 
        } else if (bytes_received<0){
            perror("Error reading from Upload command secondSocket");
            exit(1);
        }else if (bytes_received < BUFFERSIZE){
            std::cout<<buffer; //write last bytes < 4096 bytes
            break;
        }
        std::cout<<buffer; //write 4096 bytes = full size
    }
    sio.write("file accepted",socket); // feedbake from the client
    std::cout<<"Done."<<std::endl;
    std::string input; //get input for changing+for what or not changing the parameters
    std::getline(std::cin,input);
    while(!input.empty()){ // if the client press enter return to menu
        std::getline(std::cin,input);
    }
}

void MyClient::downloadClassifications(int socket){
    std::string feedback = sio.read(socket); // if the server is going to dend classifications
    if(feedback != "1"){
        std::cout<<feedback<<std::endl;
        return;
    }
    sio.write("feedback accepted",socket);
    std::string file_path;
    std::getline(std::cin,file_path);
    std::ofstream out_file(file_path, std::ios::binary); //open file "outFile_name"
    if(!out_file.is_open()) {
        perror("Error opening file ");
        exit(1);
    }
    char buffer[BUFFERSIZE];
    while(1){
        memset(buffer, 0, BUFFERSIZE);
        int bytes_received = recv(socket,buffer, BUFFERSIZE, 0);
        if(bytes_received == 0){  // Read no bytes - either connection has closed or client taking too long // Let's exit
            break; 
        } else if (bytes_received<0){
            perror("Error reading from Upload command secondSocket");
            exit(1);
        }else if (bytes_received < BUFFERSIZE){
            out_file.write(buffer, bytes_received); //write last bytes < 4096 bytes
            break;
        }
        out_file.write(buffer, bytes_received); //write 4096 bytes = full size
    }
    out_file.close();
    sio.write("file accepted",socket); // feedbake from the client that the file accepted.
}

