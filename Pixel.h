class Pixel
{
public:
	Pixel();
	Pixel(unsigned char r, unsigned char g, unsigned char b);

	unsigned char r;
	unsigned char g;
	unsigned char b;
};

Pixel::Pixel()
{
	r = 0;
	g = 0;
	b = 0;
}
Pixel::Pixel(unsigned char r, unsigned char g, unsigned char b)
{
	this->r = r;
	this->g = g;
	this->b = b;
}