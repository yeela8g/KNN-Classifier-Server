# include "GetInput.h"

GetInput::GetInput(){};

Vector GetInput::getV1(){
    return v1;
}

Vector GetInput::getV2(){
    return v2;
}

bool GetInput::getValid_toMain(){
    return valid_toMain;
    }

void GetInput::input(std::string str1, std::string str2){
        valid_toMain = true; //reseting the validation flag for new X_I
        check.setValid(true);
        
        try{
            check.isNumber(str1); //check input is digit
            check.isNumber(str2);

            if (check.getValid()){ //if input is digit insert to vector and continue validation
               Vector vec1(str1);
               v1= vec1; //intialize v1 memeber
               Vector vec2(str2);
               v2= vec2; //intialize v2 member
               check.vectorSize(v1,v2); //check vector from equal size
               check.zeroDivision(v1,v2); //check no 0 in same position
               check.isEmpty(v1); //check vectors aren't empty
               check.isEmpty(v2);
        }  
    }
    catch(...){ //if input inserted in a bad way, evoking input-error -> catch and inform check
        check.setValid(false);
    }
    if (!check.getValid()){//if the user inserted invalid input - update flag for the main to exit
        valid_toMain = false;
    } 
}

bool GetInput::fileInputClassified(std::string myFile, std::list<std::string> (&featuresLabelsArr)[2]){ //gets file of data and return arr: arr[0] = features list arr[1] = labels list
    std::ifstream inputFile;
    inputFile.open(myFile);      
    if(!inputFile.is_open()){ //file input validation
        return 0;
    }if(!inputFile.good()){  
        throw std::runtime_error("couldn't open the file :" + myFile);
    }
    std::list<std::string> separatedLine; //vector to separate thef eatures from the label in one line
    std::list<std::string> features;
    std::list<std::string> labels;
    std::string line;
    while(std::getline(inputFile,line)){ //get one sample (features+label)
        std::stringstream ss(line);  //wrapping line for the getline function
        std::string word;
        separatedLine.clear(); //intiation of line container
        while(std::getline(ss, word, ',')){  //separetad each line by comma into the container
            separatedLine.push_back(word);
            }
        labels.push_back(separatedLine.back()); //push into labels list the sample label
        separatedLine.pop_back(); //remove the label from the list, only fetures remain
        std::string temp ="";
        for(std::list<std::string>::iterator itrSeparatedLine = separatedLine.begin(); itrSeparatedLine != separatedLine.end(); itrSeparatedLine++){
            temp += *itrSeparatedLine; //creating string of features
            temp += " ";
            }
        features.push_back(temp);  //enter one sample fetures to the all features samples list
    }
    inputFile.close();
    featuresLabelsArr[0] = features; //insert two values into one return
    featuresLabelsArr[1] = labels;
    return 1;
}

 void GetInput::fileInputUnclassified(std::string myFile, std::list<std::string> (&features)){
    std::ifstream inputFile;
    inputFile.open(myFile); 
    if(!inputFile.good()){  
        throw std::runtime_error("couldn't open the file :" + myFile);
    }
    std::list<std::string> separatedLine; //vector to separate thef eatures from the label in one line
    std::string line;
    while(std::getline(inputFile,line)){ //get one sample (features+label)
        if(line.back() == '\r'){
            line.pop_back();
        }
        std::stringstream ss(line);  //wrapping line for the getline function
        std::string word;
        separatedLine.clear(); //intiation of line container
        while(std::getline(ss, word, ',')){  //separetad each line by comma into the container
            separatedLine.push_back(word);
        }
        std::string temp ="";
        for(std::list<std::string>::iterator itrSeparatedLine = separatedLine.begin(); itrSeparatedLine != separatedLine.end(); itrSeparatedLine++){
            temp += *itrSeparatedLine; //creating string of features
            temp += " ";
            }
        features.push_back(temp);  //enter one sample fetures to the all features samples list
    }
    inputFile.close();
 }