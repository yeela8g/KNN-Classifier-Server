#include "MyServer.h"


MyServer::MyServer(int prt){
    port = prt;
}

void MyServer::communicate(){
    int sock= socket(AF_INET, SOCK_STREAM, 0); //create a TCP socket 
    if(sock < 0){
        perror("couldn't create socket");
        exit(1);
    }
    std::cout << "created main socket" << std::endl;
    struct sockaddr_in serverAdress; //create server address details struct
    memset(&serverAdress,0, sizeof(serverAdress));
    serverAdress.sin_family = AF_INET;
    serverAdress.sin_addr.s_addr = INADDR_ANY;
    serverAdress.sin_port = htons(port);
    if (bind(sock, (const sockaddr *)&serverAdress, sizeof(serverAdress)) < 0) {// bind() assigns the socket to an IP address and a port
        perror("error binding socket");
        exit(1);
    }
    std::cout << "binded port to socket" << std::endl;
    if(listen(sock,MAX_CLIENT)<0){ // listen up to 5 clients
        perror("error accepting client");
        exit(1);
    }
    std::cout << "listening to socket.." << std::endl;
    while (1){
        struct sockaddr_in clientAddress;
        unsigned int client_addr_len = sizeof(clientAddress);
        int secondSock = accept(sock,(sockaddr *)&clientAddress, &client_addr_len); // create second socket after accepting client
        if (secondSock < 0){
            perror("error accepting client");
            exit(1);
        }
        std::cout << "accepted clinet.." << std::endl;
        
        std::thread t(&CLI::start, new CLI, secondSock);//send thread to excecute cli.start()
        t.detach();
    }

    if (close(sock) < 0){ // close the main socket
            perror("ERROR - closing client-specific socket failed: ");
            exit(1);
        }
}