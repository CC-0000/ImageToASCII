#include "Image.cpp"

//Luke's Algorithm
class Algorithm1
{
public:
    Algorithm1(Image& image);
    char Density(float darkness);
    void Run(string address);

private:
    Pixel** pixels;
    Image image;
    const string density = "@&#$50327b1o~;,.";

    short width;
    short height;
};


//Nathan's Algorithm
class Algorithm2
{
public:
    Algorithm2(Image& image);
    ~Algorithm2();
    void Run(string address, int textSize);

private:
    void PureOutline(Image& image);

    bool** outline;

    short width;
    short height;
};