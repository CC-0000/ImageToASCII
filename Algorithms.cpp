#include "Algorithms.h"

//Luke's stuff

// Constructor with vector parameter
Algorithm1::Algorithm1(const vector<Pixel>& _pixels)
{
    for (unsigned int i = 0; i < _pixels.size(); i++)
        pixels.push_back(_pixels[i]);
}

// Density Character Finder
char Algorithm1::Density(float darkness)
{
    char densityChar = ' ';
    if (darkness > 239) densityChar = density[0];
    else if (darkness > 223) densityChar = density[1];
    else if (darkness > 207) densityChar = density[2];
    else if (darkness > 191) densityChar = density[3];
    else if (darkness > 175) densityChar = density[4];
    else if (darkness > 159) densityChar = density[5];
    else if (darkness > 143) densityChar = density[6];
    else if (darkness > 127) densityChar = density[7];
    else if (darkness > 111) densityChar = density[8];
    else if (darkness > 95) densityChar = density[9];
    else if (darkness > 79) densityChar = density[10];
    else if (darkness > 63) densityChar = density[11];
    else if (darkness > 47) densityChar = density[12];
    else if (darkness > 31) densityChar = density[13];
    else if (darkness > 15) densityChar = density[14];
    else if (darkness > 0) densityChar = density[15];

    return densityChar;
}

// Algorithm for assigning each pixel a darkness value
void Algorithm1::PixelDarkness()
{
    /*
    ofstream file("algorithm1test1.txt");
    if (!file.is_open())
    {
        cout << "Invalid file" << address << endl;
        return;
    }
    */

    for (int i = 0; i < pixels.size(); i++)
    {
        float darkness = pixels[i].DarknessOfImage();
        pixelChars.push_back(Density(darkness));
    }

    // Not sure where in the code we are able to write the txt files to test algorithm.
    /*for (int i = 0; i < pixelChars.size(); i++)
    {
        file.write(pixelChars[i]);
    }*/
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

    int textSizeX = 200;
    int textSizeY = textSizeX * height / width / 2;
    for (int textY = 0; textY < textSizeY; textY++)
    {
        for (int textX = 0; textX < textSizeX; textX++)
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
                    int x = (double)width / textSizeX * textX + blockX;
                    int y = (double)height / textSizeY * textY + blockY;

                    if (x < width && y < height && outline[x][y])
                    {
                        meanX += blockX;
                        meanY += blockY;
                        points++;
                    }
                }
            }
            if (points == 0)
            {
                file << ' ';
                continue;
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
                    int x = (double)width / textSizeX * textX + blockX;
                    int y = (double)height / textSizeY * textY + blockY;

                    if (x < width && y < height && outline[x][y])
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
        file << endl;
    }

    file.close();
}
void Algorithm2::PureOutline(Image& image)
{
    outline = new bool*[width];
	for (short i = 0; i < width; i++)
		outline[i] = new bool[height];
    
    unsigned char threshold = 10;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            outline[x][y] = image.pixels[x][y].r > threshold;
            //cout << outline[x][y];
        }
        //cout << endl;
    }
}