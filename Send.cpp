#include "Send.h"
Send::Send(){
    description = "4. display results\n";
}

void Send::excecute(int secondSock){
    std::string file_test_name = "out1" + std::to_string(secondSock) + "test"; // test file to check if Upload was called, and upload file
    std::string outFile_name = "out1" + std::to_string(secondSock) + "testClassified"; // classified file to send
    if(access(file_test_name.c_str(), F_OK) == -1) {// if test File doesn't exists
        sio.write("please upload data",secondSock);
        sleep(1);
        return;
    }
    if(access(outFile_name.c_str(), F_OK) == -1) {// if test File doesn't exists
        sio.write("please classify the data",secondSock);
        sleep(1);
        return;
    }
    sio.write("1",secondSock); // send flag that the server is about to send the data. 
    sio.read(secondSock); // feedbake from the client
    std::ifstream in_file(outFile_name,std::ios::binary);
    char buffer[BUFFERSIZE];
    while(in_file){
        memset(buffer,0,BUFFERSIZE);
        in_file.read(buffer,BUFFERSIZE);
        sio.write(buffer,secondSock);
    }
    in_file.close();

}