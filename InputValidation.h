#include "Dist.h"
#include <stdexcept>
#include <fstream>
#include <list>

class InputValidation{ //this class gets input from getInput class and validate it.
private:
    bool valid = true;
public:
    InputValidation(); //constructor
    void setValid(bool flag); //setter
    bool getValid(); //getter
    void vectorSize(Vector v1, Vector v2); //vector from same sizes
    void zeroDivision(Vector v1, Vector v2); //no positions with two 0 (for conbbera formula)
    void isEmpty(Vector v1); //no empty vector
    void isNumber(std::string str); //no chars inside the input
    bool separateVectorMatricK(std::string str, std::string (&vectorMatricK)[3]); //return 0 if less than 3 arguemnts sended to the server, else 1
    bool validVectorMatricK(std::string (&vectorMatricK)[3]); //valid the 3 components from the user input

};