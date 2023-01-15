#include "Upload.h"


Upload::Upload(){
    description = "1. upload an unclassified csv data file\n";
}

void Upload::excecute(int secondSock){
    sio.write("Please upload your local train CSV file.", secondSock);//write to client
    readFileDownload(secondSock, "train"); //read file - download it
    sio.write("Upload complete.", secondSock);//write to client
    sio.read(secondSock);//wait till the client reads
    sio.write("Please upload your local test CSV file.", secondSock);//write to client
    readFileDownload(secondSock, "test");//read file - download it
}

void Upload::readFileDownload(int secondSock, std::string fileType){
    std::string file_name = "out1" + std::to_string(secondSock) + fileType;
    std::ofstream out_file(file_name, std::ios::binary); //open file "file_name"
    if(!out_file.is_open()) {
        perror("Error opening file ");
        return;
    }
    std::cout<<"server opened name_file" <<std::endl;
    char buffer[BUFFERSIZE];
    while(1){
        memset(buffer, 0, BUFFERSIZE);
        int bytes_received = recv(secondSock,buffer, BUFFERSIZE, 0);
        std::cout<< "bytes_received" << bytes_received << std::endl;
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
    //sio.write("server finish downloading the file", secondSock);
 }