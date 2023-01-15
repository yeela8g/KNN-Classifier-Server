#include "InputValidation.h"
#include <cctype>
#include <cstring>

InputValidation::InputValidation(){}; // constructor

void InputValidation::setValid(bool flag){//setter
    valid = flag;
}

bool InputValidation::getValid(){//getter
    return valid;
}

void InputValidation::vectorSize(Vector v1, Vector v2){ //check both vector from the same size.
    std::vector<double> vec_v1 = v1.getVec();
    std::vector<double> vec_v2 = v2.getVec();
    if(vec_v1.size()!=vec_v2.size()){
         setValid(false);
    }
}

 void InputValidation::zeroDivision(Vector v1, Vector v2){ //prevent zero division
    std::vector<double> vec_v1 = v1.getVec();
    std::vector<double> vec_v2 = v2.getVec();
    std::vector<double>::iterator itr_v2 = vec_v2.begin();//get v2 iterator 
    for (std::vector<double>::iterator itr_v1 = vec_v1.begin(); itr_v1 != vec_v1.end(); itr_v1++)//go throught v1 
    {
        if(*itr_v1==0 && *itr_v2==0){//check no zero in both vectors position
            setValid(false);
        }
        *itr_v2++; //increament
    }
 }

 void InputValidation::isEmpty(Vector v1){
    std::vector<double> vec_v1 = v1.getVec();
    if (vec_v1.empty()){
        setValid(false);
    }
 }

 void InputValidation::isNumber(std::string str){ 
    std::stringstream sstrim(str); //streaming the input
    std::string newStr; //new string to contain each word from the input string which be converted to double
       try{
            while(std::getline(sstrim,newStr,' ')){
                int pointCount = 0; //prevent two points like 2..0
                int hyphenCount = 0; // prevent two hyphens like --, but provide negative like -33
                for (int i = 0; i < newStr.length(); i++){ 
                    if(newStr[i]=='.'){ // counting points
                        pointCount++;
                    }
                    if(newStr[i]=='-'){ //pay attention that prevention of newStr = '-' preveneted in the vector while converting it to double
                        hyphenCount++;
                    }
                    if (!(newStr[i]=='.') && !(newStr[i]=='-') && (!isdigit(newStr[i]))){ //make sure it's a digit or a point
                       return setValid(false);
                    }
                }if (pointCount>1){ //prevent two points like 2..0
                    return setValid(false);
                }
                if (hyphenCount>1 || (hyphenCount == 1 && newStr[0] != '-')){ //prevent two points like 2..0
                    return setValid(false);
                }
                if (newStr[newStr.length()-1] == '.'){ //prevent 2.
                    return  setValid(false);
                }
                stod(newStr);
               
                
            }
        }catch (...) {
            
            return setValid(false);
        }
}

bool InputValidation::validVectorMatricK(std::string (&vectorMatricK)[3]){ //remember all in string format, [0]-x, [1]-metric [2]-k
    bool flag = 1;
    isNumber(vectorMatricK[0]); 
    if(getValid()== false || vectorMatricK[0].empty()){//x contains only digits and no empty
        return 0;
    }//valid distance metric
    if(vectorMatricK[1]!="AUC" && vectorMatricK[1]!="CHB" && vectorMatricK[1]!="CAN" && vectorMatricK[1]!="MIN" && vectorMatricK[1]!="MAN"){
        return 0; 
    }
    isNumber(vectorMatricK[2]);//valid k
    if (getValid()== false){
        return 0;
    } 
    if(std::stoi(vectorMatricK[2])!= std::stod(vectorMatricK[2])){//check k is integer
        return 0;
    } else if (std::stoi(vectorMatricK[2])<1){ //check k is 1+
        return 0;
    }
    return 1; // vector, distance and k are valid

}

bool InputValidation::separateVectorMatricK(std::string str, std::string (&vectorMatricK)[3]){
    std::list<std::string> separatedStr;
    std::stringstream ss(str);  //wrapping line for the getline function
    std::string word;
    while(std::getline(ss, word, ' ')){  //separetad each line by comma into the container
        separatedStr.push_back(word);
    }
    if (separatedStr.size() < 3){
        return 0;
    }
    vectorMatricK[2] = (separatedStr.back()); //push into k the last string from the user input
    separatedStr.pop_back(); //remove the k from the list
    vectorMatricK[1] = (separatedStr.back()); //push into matric the second from the end user input
    separatedStr.pop_back(); //remove the matric from the list
    std::string x ="";
    for(std::list<std::string>::iterator itrSeparatedStr = separatedStr.begin(); itrSeparatedStr != separatedStr.end(); itrSeparatedStr++){
        x += *itrSeparatedStr; //creating string of features
        x += " ";
    }
    vectorMatricK[0] = x;
    return 1;
}
 
