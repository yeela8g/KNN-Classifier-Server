#include "SettingsKnn.h"

SettingsKnn::SettingsKnn(){
    k = 5;
    matric = "AUC";
    description = "2. algorithm settings\n";

}
void SettingsKnn::excecute(int secondSock){
    sio.write("The current KNN parameters are: K = " + std::to_string(k) + ", distance metric = " + matric + "\n", secondSock);
    std::string flag = sio.read(secondSock);
    std::cout<<"flag:"<<flag<<std::endl;
    sio.write("flag accepted",secondSock); //acknowledge
    if(flag == "0"){
        return;
    }
    std::string newK = sio.read(secondSock);
    k = std::stoi(newK);
    sio.write("k accepted",secondSock);
    std::string newMatric = sio.read(secondSock);
    matric = newMatric;
}
int SettingsKnn::getK(){
    return k;
}
std::string SettingsKnn::getMatric(){
    return matric;
}