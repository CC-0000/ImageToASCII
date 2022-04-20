#include "Algorithms.h"

//Luke's stuff

// Constructor with vector parameter
Algorithm1::Algorithm1(Image& _image)
{
    image = _image;
    pixels = image.pixels;
    width = image.width;
    height = image.height;
}

// Density to Character
char Algorithm1::Density(float darkness)
{
    char c = ' ';
    if (darkness > 239) c = density[0];
    else if (darkness > 223) c = density[1];
    else if (darkness > 207) c = density[2];
    else if (darkness > 191) c = density[3];
    else if (darkness > 175) c = density[4];
    else if (darkness > 159) c = density[5];
    else if (darkness > 143) c = density[6];
    else if (darkness > 127) c = density[7];
    else if (darkness > 111) c = density[8];
    else if (darkness > 95) c = density[9];
    else if (darkness > 79) c = density[10];
    else if (darkness > 63) c = density[11];
    else if (darkness > 47) c = density[12];
    else if (darkness > 31) c = density[13];
    else if (darkness > 15) c = density[14];
    else if (darkness > 0) c = density[15];

    return c;
}

// Algorithm for assigning each pixel a darkness value
void Algorithm1::Run(string address)
{
    
    ofstream file(address);
    if (!file.is_open())
    {
        cout << "Invalid file" << address << endl;
        return;
    }
   
    int heightIncrement = (height / 100) * 2;
    int widthIncrement = (width / 100);

    if (heightIncrement == 0) heightIncrement = 2;
    if (widthIncrement == 0) widthIncrement = 1;

    for (int i = 0; i < height; i = i + heightIncrement)
    {
        for (int j = 0; j < width; j = j + widthIncrement)
        {
            float darkness = pixels[j][i].DarknessOfImage();
            file << Density(darkness);
        }
        file << '\n';
    }
    
    file.close();
}


//Nathan's stuff
Algorithm2::Algorithm2(Image& image)
{
    width = image.width;
    height = image.height;

    Image outlineImage = image.OutlineImage();
    PureOutline(outlineImage);
}
Algorithm2::~Algorithm2()
{
    if (outline != nullptr)
	{
		for (int i = 0; i < width; i++)
			delete[] outline[i];
		delete[] outline;
	}
}
void Algorithm2::Run(string address)
{
    ofstream file(address);
    if (!file.is_open())
    {
        cout << "Invalid file" << address << endl;
        return;
    }

    int textSizeX = 50;
    int textSizeY = textSizeX * height / width / 2;
    for (int textX = 0; textX < textSizeX; textX++)
    {
        for (int textY = 0; textY < textSizeY; textY++)
        {
            //Line of Best Fit (Least Square Method)

            //Calculate averages
            int points = 0;
            int meanX = 0;
            int meanY = 0;
            for (int blockX = 0; blockX < width / textSizeX; blockX++)
            {
                for (int blockY = 0; blockY < height / textSizeY; blockY++)
                {
                    int x = width / textSizeX * textX + blockX;
                    int y = height / textSizeY * textY + blockY;

                    if (outline[x][y])
                    {
                        meanX += blockX;
                        meanY += blockY;
                        points++;
                    }
                }
            }
            meanX /= points;
            meanY /= points;

            //Calculate slope
            int top = 0;
            int bottom = 0;
            for (int blockX = 0; blockX < width / textSizeX; blockX++)
            {
                for (int blockY = 0; blockY < height / textSizeY; blockY++)
                {
                    int x = width / textSizeX * textX + blockX;
                    int y = height / textSizeY * textY + blockY;

                    if (outline[x][y])
                    {
                        top += (blockX - meanX) * (blockY - meanY);
                        bottom += (blockX - meanX) * (blockX - meanY);
                    }
                }
            }
            double slope;
            if (bottom != 0)
                slope = (double)top / (double)bottom;
            else
                slope = 100;

            //Slope to char
            char c = '#';
            if (slope > 1 && slope < 5)
                c = '/';
            else if (slope >= 5 || slope <= -5)
                c = '|';
            else if (slope < -1 && slope > -5)
                c = '\\';
            else
                c = '-';
            
            file << c;
        }
        file << '\n';
    }

    file.close();
}
void Algorithm2::PureOutline(Image& image)
{
    outline = new bool*[width];
	for (short i = 0; i < width; i++)
		outline[i] = new bool[height];
    
    unsigned char threshold = 1;
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            outline[x][y] = image.pixels[x][y].r > threshold;
            cout << (image.pixels[x][y].r / 3 + 33);
        }
        cout << endl;
    }
}