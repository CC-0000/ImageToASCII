#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "Pixel.h"
using namespace std;

class Image
{
public:
	Image(short w = -1, short h = -1);
	void DeleteImage();
	~Image();

	void LoadPNGImage(int w, int h, vector<unsigned char>& colors);
	void SaveImage(string address);

	Image& OutlineImage();

	Pixel** pixels;

	short width;
	short height;

private:
	static int abs(int i);
};