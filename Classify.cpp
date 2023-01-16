#include "Classify.h"

Classify::Classify(){
    description = "3. classify data\n";
    matric = "AUC";
    k=5;
}
void Classify::setMatric(std::string newMatric){
    matric = newMatric;
}

void Classify::setK(int newK){
    k=newK;
}

void Classify::excecute(int secondSock){
    featuresLabelsArr[0].clear();
    featuresLabelsArr[1].clear();
    featuresOnly.clear();

    std::string file_train_name = "out1" + std::to_string(secondSock) + "train";
    GetInput in;
    bool flag = in.fileInputClassified(file_train_name,featuresLabelsArr);
    if(!flag){
        sio.write("please upload data",secondSock);
        sleep(1);
        return;
    }
    std::string file_test_name = "out1" + std::to_string(secondSock) + "test";
    in.fileInputUnclassified(file_test_name,featuresOnly);

    std::string outFile_name = "out1" + std::to_string(secondSock) + "testClassified";
    if(access(outFile_name.c_str(), F_OK) != -1) {// File exists, so delete it
        remove(outFile_name.c_str());
    }
    std::ofstream out_file(outFile_name, std::ios::binary); //open file "outFile_name"
    if(!out_file.is_open()) {
        perror("Error opening file ");
        return;
    }
    bool fileEmpty = 1;//flag to checks if some classificasions inserted to the file during the loop
    int i = 1;//counting number of classify
    for(std::list<std::string>::iterator itrX = featuresOnly.begin(); itrX != featuresOnly.end(); itrX++){
        std::string label = mngKnn(*itrX,matric,k); // remember lable can be -> "k too big" !!!!!!!!!
        if(label == "k too big"){
            continue;
        }
        label = std::to_string(i) + "   " + label + "\n";
        out_file.write(label.c_str(), label.size());
        fileEmpty = 0;
        i++;
    }
    out_file.close();
    if(fileEmpty){ // if there is no exist neighbor or neighbors less than k.
        sio.write("invalid input",secondSock);
        remove(outFile_name.c_str());
        sleep(1);
        return;
    }
    sio.write("classifying data complete",secondSock);
    sleep(1);
}

std::string Classify::mngKnn(std::string xStr, std::string metric, int k){
    GetInput in;
    std::list<Vector> xValidList;
    std::list<std::string> yValidList;
    std::list<std::string>::iterator itrY = featuresLabelsArr[1].begin(); //loop for data validation and creating vectors out of the strings
        for(std::list<std::string>::iterator itrX = featuresLabelsArr[0].begin(); itrX != featuresLabelsArr[0].end(); itrX++){
            in.input(*itrX, xStr);
            if(in.getValid_toMain() == true){
                Vector v1=in.getV1();  //vectors creation for x_i list
                xValidList.push_back(v1);
                yValidList.push_back(*itrY);
            }
            itrY++;
        }
        if(k > xValidList.size()){ //checking k values
            return "k too big";
        }
        Vector xVect = in.getV2();//vectors creation for x test sample
        Knn knn(xValidList,yValidList,xVect,k, metric);
        return knn.predict(); //calculat distances metrix, find k nearest neighbors and return most common label
}