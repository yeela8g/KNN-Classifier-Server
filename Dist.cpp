
#include "Dist.h"
#include <math.h>

Dist::Dist(){}; //construtcor

double Dist::euclideanDistance(Vector v1, Vector v2){  // euclidian distance calc using mikovski formula with p=2
    return MinkowskiDistance(v1,v2,2);
};

double Dist::manhattanDistance(Vector v1, Vector v2){ // manhatten distance calc using mikovski formula with p=1
   return MinkowskiDistance(v1,v2,1);
}

double Dist::ChebyshevDistance(Vector v1, Vector v2){ 
    double max = 0;
    Vector substract = v1.absValSubtract(v2); //calculating the subtract vector to all pi-qi
    std::vector<double> subVec = substract.getVec();
    for(std::vector<double>::iterator i = subVec.begin(); i!=subVec.end(); i++){ //find the max in subtract vector
          if(*i > max){
            max = *i;
            } 
        }
    return max;
}

double Dist::CanberraDistance(Vector v1, Vector v2){
    double sum = 0;
    std::vector<double> v1Vec = v1.getVec();
    std::vector<double>::iterator itr_v1 = v1Vec.begin(); //get iterator for pi
    std::vector<double> v2Vec = v2.getVec();
    std::vector<double>::iterator itr_v2 = v2Vec.begin(); // get iterator for qi
    Vector sub = v1.absValSubtract(v2);
    std::vector<double> subVec = sub.getVec();
    for(std::vector<double>::iterator i = subVec.begin(); i!=subVec.end(); i++){ //go throught subtract vector of p-q
       sum += (*i) / (abs(*itr_v1) + abs(*itr_v2)); //calc conberra distance
    }
    return sum;
}


double Dist::MinkowskiDistance(Vector v1, Vector v2, double pVal){ //pval changes according to the required formula
    double sum = 0;
    std::vector<double> vec_v2 = v2.getVec();
    std::vector<double>::iterator itr_v2 = vec_v2.begin(); //get v2 begin_iterator
    std::vector<double> vec_v1 = v1.getVec();
    for (std::vector<double>::iterator itr_v1 = vec_v1.begin(); itr_v1 != vec_v1.end(); itr_v1++) //go throught v1
    {
        sum += pow(abs(*itr_v1 - *itr_v2),pVal); //calculate mikovski formula
        itr_v2++; //increament
    }
    return pow(sum,(1/pVal));;
}
