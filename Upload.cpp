#include "Upload.h"
#include <fstream>

Upload::Upload(){
    description = "1. upload an unclassified csv data file/n";
}

std::string Upload::getDescription(){
    return description;
}

void Upload::excecute(int secondSock){
    sio.write("Please upload your local train CSV file.", secondSock);//write to client
    readFileDownload(secondSock); //read file - download it
    sio.write("Upload complete.\n", secondSock);//write to client
    sio.write("Please upload your local test CSV file.", secondSock);//write to client
    readFileDownload(secondSock);//read file - download it
}

void Upload::readFileDownload(int secondSock){
    std::string file_name(sio.read(secondSock)); //get file_name
    std::ofstream out_file(file_name, std::ios::binary); //open file "file_name"
    if(!out_file.is_open()) {
        perror("Error opening file ");
        return;
    }
    char buffer[BUFFERSIZE];
    while(1){
        memset(buffer, 0, BUFFERSIZE);
        int bytes_received = recv(secondSock,buffer, BUFFERSIZE, 0);
        if(bytes_received == 0){  // Read no bytes - either connection has closed or client taking too long // Let's exit
            break;
        } else if (bytes_received<0){
            perror("Error reading from Upload command secondSocket");
            exit(1);
        }
        out_file.write(buffer, bytes_received);
    }
    out_file.close();
 }