#ifndef GetInput_H_
#define GetInput_H_
#include "InputValidation.h"



class GetInput{ //this class get input from user and catch exception from the stream, then send to validation class.
    private:
        InputValidation check; //validation member to send input to
        bool valid_toMain = true;
        Vector v1; //if input inserted and it's only digits - intialize v1 and v2 and send the vectors to validation. in the end return Vectors to main
        Vector v2;

    public:
        GetInput(); //constructor
        void input(std::string str1, std::string str2s); // gets input and sent to validation
        bool fileInputClassified(std::string path, std::list<std::string> (&arr) [2]); //fill list with classified vectors
        void fileInputUnclassified(std::string path, std::list<std::string> (&features));//fill list with unClassified vectors
        Vector getV1(); //getter
        Vector getV2(); //getter
        bool getValid_toMain(); // getter

};
#endif