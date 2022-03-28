#include "Image.h"

Image::Image()
{
	width = -1;
	height = -1;
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

void Image::LoadPNGImage(int w, int h, vector<unsigned char> pix)
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
	ofstream file(address, ios_base::binary);

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
}