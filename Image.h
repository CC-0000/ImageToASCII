#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "Pixel.h"
using namespace std;

class Image
{
public:
	Image();
	~Image();

	void LoadPNGImage(int w, int h, vector<unsigned char> colors);

	void SaveImage(string address);

	Pixel** pixels;

private:
	short width;
	short height;
};