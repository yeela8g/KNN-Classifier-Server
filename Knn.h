#include "GetInput.h"

class Knn{
    private:
    std::list<Vector> xList; //list of samples
    std::list<std::string> yList; //list of matching labels
    Vector x; //the test sample to predict
    int k;  //number of nearest neighbors to predict by them
    std::string matric; //distance metric calculation

    public:
    Knn(std::list<Vector> xList,std::list<std::string> yList,Vector x,int k,std::string matric); //constructor
    std::string predict(); //calculat distances metrix, find k nearest neighbors and return most common labels
};