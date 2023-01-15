#include "SettingsKnn.h"

SettingsKnn::SettingsKnn(){
    k = 5;
    matric = "AUC";
    description = "2. algorithm settings\n";

}
void SettingsKnn::excecute(int secondSock){
    sio.write("The current KNN parameters are: K = " + std::to_string(k) + ", distance metric = " + matric + "\n", secondSock);
    std::string flag = sio.read(secondSock);//get flag if params ok
    sio.write("flag accepted",secondSock); //flag acknowledge
    if(flag == "0"){
        sleep(1);
        return;
    }
    std::string newK = sio.read(secondSock);//reak k from client
    k = std::stoi(newK);
    sio.write("k accepted",secondSock); //acknowledge k
    std::string newMatric = sio.read(secondSock);//read metric from client
    matric = newMatric;
}
int SettingsKnn::getK(){
    return k;
}
std::string SettingsKnn::getMatric(){
    return matric;
}