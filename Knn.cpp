#include "Knn.h"

 Knn::Knn(std::list<Vector> xList1,std::list<std::string> yList1,Vector x1,int k1,std::string matric1){
    xList=xList1; 
    yList=yList1;
    x=x1;
    k=k1;
    matric=matric1;
 }
std::string Knn::predict(){
    //creating dictane matric
    std::list<double> distanceMetx;
    Dist distance; 
        if (matric =="AUC") { // for this matric go over listX calculate its distance from the X test sample and insert to the distance list
            for(std::list<Vector>::iterator itrX = xList.begin(); itrX != xList.end(); itrX++){
                    distanceMetx.push_back(distance.euclideanDistance(*itrX,x));
            }
        }
        else if (matric == "MAN"){
             for(std::list<Vector>::iterator itrX = xList.begin(); itrX != xList.end(); itrX++){
                distanceMetx.push_back(distance.manhattanDistance(*itrX,x));
             }
       }
        else if (matric == "CHB") {
             for(std::list<Vector>::iterator itrX = xList.begin(); itrX != xList.end(); itrX++){
                distanceMetx.push_back(distance.ChebyshevDistance(*itrX,x));
             }
        }
        else if (matric =="CAN") {
             for(std::list<Vector>::iterator itrX = xList.begin(); itrX != xList.end(); itrX++){
                distanceMetx.push_back(distance.CanberraDistance(*itrX,x));
             }
        }
        else if (matric == "MIN"){
             for(std::list<Vector>::iterator itrX = xList.begin(); itrX != xList.end(); itrX++){
                distanceMetx.push_back(distance.MinkowskiDistance(*itrX,x,distance.p));
             }
        }
        // find K closest labeles
        std::string closestKlableArr[k]; //initiation array for k closest labels
        std::list<double> SortedDistanceMetx = distanceMetx; // creating a copy distance list for saving the original list order 
        SortedDistanceMetx.sort();
        std::list<double>::iterator itrSortedD = SortedDistanceMetx.begin(); //initiate iterator on copied distance list
        std::list<std::string>::iterator itrY = yList.begin();//initiate iterator on label list
        for (int i = 0; i < k ;i++){ // pull the labels of the k closest sampels
            for(std::list<double>::iterator itrD = distanceMetx.begin(); itrD != distanceMetx.end(); itrD++){
                if (*itrD==*itrSortedD) {
                    closestKlableArr[i]=*itrY;
                }
                itrY++;
            }
            itrSortedD++;
        }
        // find most common lable
        int maxCount = 0 ; 
        std::string predictedY="";
        for(int i=0 ;i<k ; i++){ //count how much times a label repeated 
            int countI = 0;
            for (int j = 0 ;j < k; j++){
                if (closestKlableArr[i]==closestKlableArr[j]){ 
                    countI++;
                }
            }
            if (countI > maxCount) { //update if this lable is the most common until now
                maxCount=countI;
                predictedY=closestKlableArr[i];
            }
            if (countI==k){ //optimization if all labels are the same return this label
                break;
            }
        }
        return predictedY; //print the predicted label

    }