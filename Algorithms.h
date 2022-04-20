#include "Image.cpp"

//Luke's Algorithm
class Algorithm1
{
public:
    Algorithm1(Image& image);
    char Density(float darkness);
    string Run(string address, int textSize);

private:
    Pixel** pixels;
    Image image;
    const string density = "@$WX8?x;:~,.  ";

    short width;
    short height;
};


//Nathan's Algorithm
class Algorithm2
{
public:
    Algorithm2(Image& image);
    ~Algorithm2();
    string Run(string address, int textSize);

private:
    void PureOutline(Image& image);

    bool** outline;

    short width;
    short height;
};