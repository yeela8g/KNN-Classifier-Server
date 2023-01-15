#include <vector>
#include <string>
#include <sstream>
#include <iostream>

class Vector{
   private:
        std::vector<double> vec; //container member
    public:
        Vector(); //default constructor
        Vector(std::string str); //constructor intiate the vector member
        std::vector<double> getVec(); //getter
        void setVec(std::vector<double> v);//setter
        std::vector<double> makeDoubleVector (std::string str); //this function get string of input and convert it to double vector
        void print(); //this function prints the vector value
        double absValDist(Vector v2, double p); //sum(|p-q|^p)^(1/p), p is constant static member of vector class 
        Vector absValSubtract(Vector v1); ///this function returns one abs subtraction (-) Vector --> v = |v1 - v2|;
};