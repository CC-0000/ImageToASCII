#include "Algorithms.h"

//Luke's stuff







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
    int textSizeY = 50;
    for (int textX = 0; textX < textSizeX; textX++)
    {
        for (int textY = 0; textY < textSizeY; textY++)
        {
            char c = ' ';
            for (int blockX = 0; blockX < width / textSizeX; blockX++)
            {
                for (int blockY = 0; blockY < height / textSizeY; blockY++)
                {
                    int x = width / textSizeX * textX + blockX;
                    int y = height / textSizeY * textY + blockY;
                    if (outline[x][y])
                    {
                        c = '#';
                    }
                }
            }
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