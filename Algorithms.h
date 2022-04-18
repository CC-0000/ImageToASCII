#include "Image.cpp"

//Luke's Algorithm
class Algorithm1;





//Nathan's Algorithm
class Algorithm2
{
public:
    Algorithm2(Image& image);
    ~Algorithm2();
    void Run(string address);

private:
    void PureOutline(Image& image);

    bool** outline;

    short width;
    short height;
};