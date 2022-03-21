#include "Image.h"

Image::Image()
{
	width = -1;
	height = -1;
	pixels = nullptr;
}
Image::Image(string address)
{
	width = -1;
	height = -1;
	pixels = nullptr;

	LoadImage(address);
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

void Image::LoadImage(string address)
{
	ifstream file(address, ios_base::binary);
	if (file.is_open())
	{
		char uselessInfo[12];
		file.read(uselessInfo, 12);
		file.read((char*)&width, 2);
		file.read((char*)&height, 2);
		file.read(uselessInfo, 2);

		if (pixels != nullptr)
		{
			for (int i = 0; i < width; i++)
				delete[] pixels[i];
			delete[] pixels;
		}

		pixels = new Pixel * [width];
		for (int i = 0; i < width; i++)
			pixels[i] = new Pixel[height];

		for (int x = 0; x < width; x++)
		{
			for (int y = 0; y < height; y++)
			{
				unsigned char r = 0;
				unsigned char g = 0;
				unsigned char b = 0;

				file.read((char*)&b, 1);
				file.read((char*)&g, 1);
				file.read((char*)&r, 1);

				pixels[x][y] = Pixel(r, g, b);
			}
		}
	}
	else
	{
		cout << "Image " << address << " not found!" << endl;
	}
}
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