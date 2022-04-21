#include "Image.h"

Image::Image(short w, short h)
{
	width = w;
	height = h;
	if (w > 0 && h > 0)
	{
		pixels = new Pixel*[width];
		for (int i = 0; i < width; i++)
			pixels[i] = new Pixel[height];
	}
	else
		pixels = nullptr;

}
Image::~Image()
{
	if (pixels != nullptr)
	{
		for (int i = 0; i < width; i++) 
			delete[] pixels[i];
		delete[] pixels;
	}
}

//Loads image from PNG type
void Image::LoadPNGImage(int w, int h, vector<unsigned char>& pix)
{
	width = w;
	height = h;

	//Creates 2d Pixel pointer array
	//Access by pixels[x-coord][y-coord]
	pixels = new Pixel*[width];
	for (short i = 0; i < width; i++)
		pixels[i] = new Pixel[height];

	//Load Pixels in backwards from vector so removal from pix array is const time
	int color = 0;

	for (short y = 0; y < height; y++)
	{
		for (short x = 0; x < width; x++)
		{
			pixels[x][y].r = pix[color];
			color++;
			pixels[x][y].g = pix[color];
			color++;
			pixels[x][y].b = pix[color];
			color++;

			//Shade transparent black
			if (pix[color] == 0)
			{
				pixels[x][y].r = 255;
				pixels[x][y].g = 255;
				pixels[x][y].b = 255;
			}
			color++;
		}
	}
}

Image& Image::OutlineImage()
{
	static Image outline(width, height);

	//Cycle through orininal image x
	for (short orgx = 0; orgx < width; orgx++)
	{
		//Cycle through orininal image y
		for (short orgy = 0; orgy < height; orgy++)
		{
			int diff = 0;
			int neighbors = 0;
			for (short hor = -1; hor <= 1; hor++)
			{
				for (short ver = -1; ver <= 1; ver++)
				{
					short x = orgx + hor;
					short y = orgy + ver;
					//Check if the pixel is a valid pixel
					if (x >= 0 && y >= 0 && x < width && y < height && (x != orgx || y != orgy))
					{
						diff += abs((int)(pixels[x][y].r - pixels[orgx][orgy].r));
						diff += abs((int)(pixels[x][y].g - pixels[orgx][orgy].g));
						diff += abs((int)(pixels[x][y].b - pixels[orgx][orgy].b));
						neighbors++;
					}
				}
			}
			unsigned char average = diff / 3 / neighbors;
			outline.pixels[orgx][orgy] = Pixel(average, average, average);
		}
	}

	return outline;
}

int Image::abs(int i)
{
	if (i > 0)
		return i;
	else
		return -i;
}