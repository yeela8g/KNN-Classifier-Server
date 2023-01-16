#include "SocketIO.h"

SocketIO::SocketIO(){}

std::string SocketIO::read(int secondSock){ //read data sent from client over the socket
    char buffer[BUFFERSIZE]; //create string to contain the message from client
    memset(buffer, 0, BUFFERSIZE); //initiation
    int read_bytes = recv(secondSock,buffer,sizeof(buffer),0); // get message
    if(read_bytes == 0){  // Read no bytes - either connection has closed or client taking too long // Let's exit
        return "";
    } else if (read_bytes<0){
        perror("Error reading from connection socket");
        exit(1);
    }
    return buffer;
}


void SocketIO::write(std::string reply, int secondSock){//send data to client over the socket
    int sent_bytes = send(secondSock,reply.c_str(),reply.size(),0);//send response
    if (sent_bytes < 0){
        perror("error sending to client");
        exit(1);
    }
}
