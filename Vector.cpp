
#include "Vector.h"
#include "math.h"
#include "stdio.h"

    Vector::Vector(){}; 
    Vector::Vector(std::string str){ //initiate the vector with double values converted from the input string
        vec = makeDoubleVector(str); 
    };

     std::vector<double> Vector::getVec(){
        return vec;
     }

    void Vector::setVec(std::vector<double> v){
       vec = v;
    }

    std::vector<double> Vector::makeDoubleVector (std::string str){ //push to vector the double values converted from string input
        std::stringstream sstrim(str); //streaming the input
        std::string newStr; //new string to contain each word from the input string which be converted to double
        while(std::getline(sstrim,newStr,' '))
        {
            vec.push_back(stod(newStr));  //going throught the input and divide it to words by " ", convert to double and push to vector.
        }
        return vec; // end of string -> return intiate vector.
    }


    void Vector::print(){
        if (!vec.empty()){ //if the vector is not intialized - return error
            for(std::vector<double>::iterator i = vec.begin();i!=vec.end();i++){
                std::cout<<"print:"<<*i; //print vector values
            }
            std::cout<<std::endl;
        }
        else {
            std::cout<<"error:the vector is empty"<<std::endl;
        }
    }


     Vector Vector::absValSubtract(Vector v2){ //this function return a |substract| vector of this(p1) and p2. 
        Vector subtract; 
        std::vector<double> vec_v2 = v2.getVec();
        std::vector<double> vec_subtract = subtract.getVec();
        std::vector<double>::iterator itr_v2 = vec_v2.begin();
        std::vector<double>::iterator itr_substract = vec_subtract.begin(); //taking begin_itertaor of subtract and v2
         for (std::vector<double>::iterator itr_v1 = vec.begin(); itr_v1 != vec.end(); itr_v1++){
             vec_subtract.push_back(abs(*itr_v1 - *itr_v2)); 
             *itr_v2++; //increament
             *itr_substract++;
         }
         subtract.setVec(vec_subtract); //update the subtract vector member by its setter
         return subtract;
     }
   