#include "Image.cpp"

//Luke's Algorithm
class Algorithm1
{
private:
    vector<Pixel> pixels;
    vector<char> pixelChars;
    const string density = "@&#$50327b1o~;,.";

public:
    Algorithm1(const vector<Pixel>& pixels);
    char Density(float darkness);
    void PixelDarkness();
};


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