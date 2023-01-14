#include <string>

class DefaultIO{
    public:
        virtual std::string read(int secondSock) = 0;
        virtual void write(std::string text, int secondSock) = 0;
};
