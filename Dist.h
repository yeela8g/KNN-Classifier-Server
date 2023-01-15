#include "Vector.h"

class Dist{
    public:
        static constexpr double p = 2.0; //from mikovski formula
        Dist(); //constructor
        double euclideanDistance(Vector v1, Vector v2); //|p-q|
        double manhattanDistance(Vector v1, Vector v2);  //sum(|pi-qi|)
        double ChebyshevDistance(Vector v1, Vector v2);  //max(|pi-qi|)
        double CanberraDistance(Vector v1, Vector v2);   //sum((|pi-qi|)\(|p|+|q|))
        double MinkowskiDistance(Vector v1, Vector v2, double pVal);  // (sum [|xi-yi|^p])^ 1/p
       
};
