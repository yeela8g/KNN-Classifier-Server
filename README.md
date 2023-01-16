# Ex4 - Multi-threaded KNN server-client model
---
## Description
The purpose of this repository is implementing KNN server in multi-threaded model for simultaneously clients treating. 

the server program input is:
- port

the client program input is:
- server ip
- server port

When a client connects to the knn server, the server introduce the program menu and the user can choose one of the following actions:

- 1-upload csv files to the server (classified and unclassified data).
- 2-set the knn algorithm parameters.
- 3-classifying all unclassified data using the knn classifier.
- 4-print all labels from the classification.
- 5-download all labels classification from the as a file.
- 8-exit&disconnect the server.
> for any invalid input the menu will be presented again and the user will be able to try again.
> if the order of the options isn't logically correct - a message will be printed and the user will return to menu.

## Optimization

- One function for sending all kinds of csv files from client to server.
- Client contains member of SocketIO in the class for uniformly reading and writing to the server.
>this optimized our code by preventing code duplication.

## notes
- if the connection for some reason fails, error message will be presented and the client and server programs will be closed.
- for Option two: assuming that for edit the knn parameters client insert k and than the metric, separated with space. 

## How to use
>for running on university u2 server use the commands:

for running the server:
### $make
### $./Server.out [port]

>and for running the client:
### $./Client.out [ip] [port]
>for example:

-![image](https://user-images.githubusercontent.com/118124478/212755447-02a25d6f-1075-4b06-9a0a-0504f8eba303.png)

