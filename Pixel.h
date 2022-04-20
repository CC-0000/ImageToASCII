class Pixel
{
public:
	unsigned char r;
	unsigned char g;
	unsigned char b;

	Pixel();
	Pixel(unsigned char r, unsigned char g, unsigned char b);
	float DarknessOfImage();
};

// Default Constructor
Pixel::Pixel()
{
	r = 0;
	g = 0;
	b = 0;
}

// Constructor with RGB parameters
Pixel::Pixel(unsigned char r, unsigned char g, unsigned char b)
{
	this->r = r;
	this->g = g;
	this->b = b;
}


// Density: @&#$50327b1o~;,.
// Will be dealt with in algorithm.h
float Pixel::DarknessOfImage() 
{
	// Convert to float for grayscale
	float grayR = (float)r * 0.21;
	float grayG = (float)g * 0.72;
	float grayB = (float)b * 0.07;

	// Calculate how dark each pixel is
	float darkness = grayR + grayG + grayB;

	return darkness;
}