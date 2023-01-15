#include "Command.h"
#include <list>
#include "GetInput.h"
#include <unistd.h>
#include "Knn.h"

class Classify:public Command{
    private:
        std::list<std::string> featuresLabelsArr[2];
        std::list<std::string> featuresOnly;
        std::string matric;
        int k;
    public:
        Classify();
        void excecute(int secondSock) override; 
        std::string mngKnn(std::string xStr, std::string metric, int kStr);
        void setMatric(std::string newMatric);
        void setK(int newK);
};