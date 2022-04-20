#include "Algorithms.h"

//Luke's stuff

// Constructor with image parameter
Algorithm1::Algorithm1(Image& _image)
{
    image = _image;
    pixels = _image.pixels;
    width = _image.width;
    height = _image.height;
}

// Density to Character
char Algorithm1::Density(float darkness)
{
    char c = ' ';
    int index = darkness * (density.size() - 1) / 255;
    c = density[index];

    return c;
}

// Algorithm for assigning each pixel a darkness value
void Algorithm1::Run(string address, int textSize)
{
    
    ofstream file(address);
    if (!file.is_open())
    {
        cout << "Invalid file" << address << endl;
        return;
    }
   
    int textSizeX = textSize;
    int textSizeY = textSizeX * height / width / 2;
    for (int textY = 0; textY < textSizeY; textY++)
    {
        for (int textX = 0; textX < textSizeX; textX++)
        {
            //Line of Best Fit (Least Square Method)

            //Calculate averages
            float darkness = 0;
            int points = 0;
            for (int blockX = 0; blockX < width / textSizeX; blockX++)
            {
                for (int blockY = 0; blockY < height / textSizeY; blockY++)
                {
                    int x = width * textX / textSizeX + blockX;
                    int y = height * textY / textSizeY + blockY;
                    if (x < width && y < height)
                    {
                        darkness = darkness + pixels[x][y].DarknessOfImage();
                        points++;
                    }
                }
            }

            //char
            darkness = darkness / points;
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
void Algorithm2::Run(string address, int textSize)
{
    ofstream file(address);
    if (!file.is_open())
    {
        cout << "Invalid file" << address << endl;
        return;
    }

    int textSizeX = textSize;
    int textSizeY = textSizeX * height / width / 2;

    for (int textY = 0; textY < textSizeY; textY++)
    {
        for (int textX = 0; textX < textSizeX; textX++)
        {
            //Line of Best Fit (Least Square Method)

            //Calculate averages
            int points = 0;
            double meanX = 0;
            double meanY = 0;
            for (int blockX = 0; blockX < width / textSizeX; blockX++)
            {
                for (int blockY = 0; blockY < height / textSizeY; blockY++)
                {
                    int x = width * textX / textSizeX + blockX;
                    int y = height * textY / textSizeY + blockY;

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
            if (points == 1)
            {
                file << '_';
                continue;
            }
            meanX /= points;
            meanY /= points;

            //Calculate slope
            double top = 0;
            double bottom = 0;
            for (int blockX = 0; blockX < width / textSizeX; blockX++)
            {
                for (int blockY = 0; blockY < height / textSizeY; blockY++)
                {
                    int x = width * textX / textSizeX + blockX;
                    int y = height * textY / textSizeY + blockY;

                    if (x < width && y < height && outline[x][y])
                    {
                        top += (blockX - meanX) * (blockY - meanY);
                        bottom += (blockX - meanX) * (blockX - meanY);
                    }
                }
            }
            double slope;
            if (bottom != 0)
                slope = -top / bottom;
            else
                slope = 100;

            //Slope to char
            char c = '#';
            if (slope > 0.3 && slope < 5)
                c = '/';
            else if (slope >= 5 || slope <= -5)
                c = '|';
            else if (slope < -0.3 && slope > -5)
                c = '\\';
            else
                c = '_';
            
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
        for (int y = 0; y < height; y++)
            outline[x][y] = image.pixels[x][y].r > threshold;

    for (int y = 0; y < height - 1; y++)
        for (int x = 0; x < width - 1; x++)
            if (outline[x][y] && outline[x+1][y] && outline[x][y+1])
                outline[x][y] = false;
}