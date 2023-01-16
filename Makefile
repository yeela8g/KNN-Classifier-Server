All : Server Client clean

Server: DefaultIO.o Command.o Server.o MyServer.o CLI.o SocketIO.o Upload.o SettingsKnn.o Classify.o GetInput.o InputValidation.o Dist.o Vector.o Knn.o Send.o
		g++ Server.o MyServer.o CLI.o SocketIO.o Upload.o SettingsKnn.o Classify.o GetInput.o InputValidation.o Dist.o Vector.o Knn.o Send.o -o Server.out

Client: DefaultIO.o Client.o MyClient.o SocketIO.o InputValidation.o Dist.o Vector.o 
		g++ Client.o MyClient.o SocketIO.o InputValidation.o Dist.o Vector.o -o Client.out

Command.o: Command.h
	g++ -std=c++11 -c Command.h 

DefaultIO.o: DefaultIO.h
	g++ -std=c++11 -c DefaultIO.h 	

Server.o: Server.cpp
	g++ -std=c++11 -c Server.cpp 

Client.o: Client.cpp
		g++ -std=c++11 -c Client.cpp 

MyServer.o: MyServer.h MyServer.cpp
		g++ -std=c++11 -c MyServer.cpp

CLI.o: CLI.h CLI.cpp
		g++ -std=c++11 -c CLI.cpp

SocketIO.o: SocketIO.h SocketIO.cpp
		g++ -std=c++11 -c SocketIO.cpp

Upload.o: Upload.h Upload.cpp
		g++ -std=c++11 -c Upload.cpp

SettingsKnn.o: SettingsKnn.h SettingsKnn.cpp
		g++ -std=c++11 -c SettingsKnn.cpp

Classify.o: Classify.h Classify.cpp
		g++ -std=c++11 -c Classify.cpp

GetInput.o: GetInput.h GetInput.cpp
		g++ -std=c++11 -c GetInput.cpp

InputValidation.o: InputValidation.h InputValidation.cpp
		g++ -std=c++11 -c InputValidation.cpp

Dist.o: Dist.h Dist.cpp
		g++ -std=c++11 -c Dist.cpp

Vector.o: Vector.h Vector.cpp
		g++ -std=c++11 -c Vector.cpp

Knn.o: Knn.h Knn.cpp
		g++ -std=c++11 -c Knn.cpp

Send.o: Send.h Send.cpp
		g++ -std=c++11 -c Send.cpp

MyClient.o: MyClient.h MyClient.cpp
		g++ -std=c++11 -c MyClient.cpp

clean:
		rm -f *.o










