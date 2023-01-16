#include "Upload.h"


Upload::Upload(){
    description = "1. upload an unclassified csv data file\n";
}

void Upload::excecute(int secondSock){
    sio.write("Please upload your local train CSV file.", secondSock);//write to client to send its files
    std::string fileFlag = sio.read(secondSock); //check if the files sent as requiered
    if(fileFlag == "0"){
        sleep(1); //something wrong the the files (invalid path)
        return;
    }
    sio.write("got upload",secondSock); // if the path is okay
    readFileDownload(secondSock, "train"); //read file - download it
    sio.write("Upload complete.", secondSock);//write to client
    sio.read(secondSock);//wait till the client reads
    sio.write("Please upload your local test CSV file.", secondSock);//write to client
    fileFlag = sio.read(secondSock);
    if(fileFlag == "0"){
        std::string trainFile = "out1" + std::to_string(secondSock)+"train";
        remove(trainFile.c_str());
        sleep(1);
        return;
    }
    sio.write("got upload",secondSock); // if the path is okay
    readFileDownload(secondSock, "test");//read file - download it
}

void Upload::readFileDownload(int secondSock, std::string fileType){
    std::string file_name = "out1" + std::to_string(secondSock) + fileType;
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
        }else if (bytes_received < BUFFERSIZE){
            out_file.write(buffer, bytes_received); //write last bytes < 4096 bytes
            break;
        }
        out_file.write(buffer, bytes_received); //write 4096 bytes = full size
    }
    out_file.close();
 }