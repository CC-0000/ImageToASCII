#include "Image.h"

Image::Image(short w, short h)
{
	width = w;
	height = h;
	if (w > 0 && h > 0)
		for (int i = 0; i < width; i++)
			pixels[i] = new Pixel[height];
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
	//Acces by pixels[x-coord][y-coord]
	for (int i = 0; i < width; i++)
		pixels[i] = new Pixel[height];
	
	//Load Pixels in backwards from vector so removal from pix array is const time
	for (int x = width - 1; x >= 0; x--)
	{
		for (int y = width - 1; y >= 0; y--)
		{
			//Ignore alpha channel
			pix.pop_back();

			unsigned char b = pix.back();
			pix.pop_back();

			unsigned char g = pix.back();
			pix.pop_back();

			unsigned char r = pix.back();
			pix.pop_back();

			pixels[x][y] = Pixel(r, g, b);
		}
	}
}
//Saves image to tga format for testing
void Image::SaveImage(string address)
{
	ofstream file(address);
	if (!file.is_open())
	{
		cout << "Can't open file: " << address << endl;
		return;
	}
	else
	{
		cout << "Writing file: " << address << endl;
	}

	char header[12];
	for (int i = 0; i < 12; i++)
	{
		header[i] = 0;
	}
	header[2] = 2;

	file.write(header, 12);
	file.write((char*)&width, 2);
	file.write((char*)&height, 2);
	header[0] = 24;
	file.write(header, 2);

	if (pixels != nullptr)
	{
		for (int x = 0; x < width; x++)
		{
			for (int y = 0; y < height; y++)
			{
				file.write((char*)&pixels[x][y].b, 1);
				file.write((char*)&pixels[x][y].g, 1);
				file.write((char*)&pixels[x][y].r, 1);
			}
		}
	}

	file.close();
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