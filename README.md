# Welcome to the KNN Classifier

This project implements a K Nearest Neighbors (KNN) classifier for classifying numeric data. The classifier is implemented using C++ and utilizes sockets for server-client architecture. The KNN Classifier is designed to efficiently classify numeric CSV test files using labeled data. The server is multithreaded and supports multiple clients simultaneously. It is implemented using TCP/IP sockets for efficient communication.

**Note**: The repository contains an example dataset ("iris" dataset) located in the "data" directory, which can be used for using the program conveniently.

## How to Run

To run the KNN Classifier, you need to execute both the client and the server programs. Follow the steps below:

1. **Compilation using Makefile** - use the ```make``` command in the commmand line for compiling all source codes. 
2.  **Start the Server**: Run the server program `Server.out` with the desired port number as an argument. For example:
   ```
    ./Server.out <port_number>
   ```

3. **Start the Client**: Execute the client program with the server's IP address and port number as arguments. For example:
   ```
   ./Client.out <server_ip> <server_port>
   ```
- Once connected, you will be presented with a menu to interact with the KNN Classifier functionalities.

**Note**: In case of connection failures, appropriate error messages will be displayed, and both client and server programs will be closed.

_examples_

![image](https://github.com/yeela8g/Ex4/assets/118124478/78eec261-3ba5-49f3-9203-82c5efb226fc)

![image](https://github.com/yeela8g/Ex4/assets/118124478/033091c5-8d06-4def-a6a5-c514d7893085)


## How to Use

Upon launching the client program, you will be presented with a menu to choose from various options. Here's a brief overview of the menu:

1. **Upload CSV Files**: upload both training and testing CSV files to the server for classification.
2. **Set KNN Parameters**: Configure parameters for the KNN algorithm, including the value of K and the distance metric.
3. **Classify Data**: Perform classification on the uploaded testing data using the configured KNN parameters.
4. **Get Classifications**: Retrieve display of the classification results from the server.
5. **Download Results**: Download the classified data from the server to your local machine.
8. **Exit**: Terminate the connection with the server and exit the client program. 

## Programming Principles

The KNN Classifier project adheres to several programming principles to ensure robustness, maintainability, and efficiency:

1. **Object-Oriented Design**: The implementation follows object-oriented principles, utilizing classes, inheritance and intefaces to model real-world entities and relationships.

2.  **Modularity**: The project is divided into separate classes, each responsible for a specific task, promoting code reuse and maintainability.
   
3.  **Polymorphism**: The use of virtual functions enables polymorphic behavior, allowing for flexibility in command execution.
   
4. **Error Handling**: Comprehensive error handling is implemented throughout the project to handle invalid inputs, file operations, and network communications gracefully.

## Optimizations

The KNN Classifier incorporates various optimizations to enhance performance and maintainability. These optimizations include:

- **Command Pattern**: The Command design pattern is employed to encapsulate various actions the users chooses as objects. Each action\command is represented by a concrete class that implements a common interface, typically containing an execute() method. These command objects enable flexible and extensible execution of actions within the system. For example, commands such as uploading data, configuring KNN settings, classifying data, and displaying results are encapsulated as separate command objects. By decoupling the invoker (CLI) from the receiver (concrete command classes), the Command Pattern promotes modular design and facilitates the addition of new commands without modifying existing code. This pattern enhances code maintainability and scalability by providing a clear separation of concerns and promoting code reuse.

![image](https://github.com/yeela8g/Ex4/assets/118124478/c6a785b3-03a1-4a24-92ec-cd81e2a5e695)

- **Input Validation**: Input validation is performed using a dedicated class (`InputValidation`), ensuring that all user inputs values and files are adjusted and  ensures that input data meets specified criteria. The validation checks include verifying the equality in the vectors size, preventing zero division,
ensuring non-empty vectors, and validating numeric input.

- **Multithreading**: The server is implemented as a multithreaded application to support concurrent client connections efficiently, enhancing scalability and responsiveness.

- **TCP/IP Communication**: The client-server communication is based on the TCP/IP protocol, providing reliable and ordered delivery of data packets, essential for real-time interactions.

Feel free to adjust and expand this repository according to your needs!
