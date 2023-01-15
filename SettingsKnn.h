#include "Command.h"
#include <iostream>

class SettingsKnn : public Command{
    private:
        int k; 
        std::string matric;
    public:
        SettingsKnn();
        void excecute(int secondSock) override; 
        int getK();
        std::string getMatric();
};