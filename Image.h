#include <string>
#include <fstream>
#include <iostream>
#include "Pixel.h"
using namespace std;

class Image
{
public:
	Image();
	Image(string address);
	~Image();

	void LoadImage(string address);
	void SaveImage(string address);

	Pixel** pixels;

private:
	short width;
	short height;
};