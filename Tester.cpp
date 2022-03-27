#include <string>
#include <iostream>
#include "lodepng.h"
using namespace std;

int main()
{
	/*
		the decode() function is given a filename and returns the:
			- height
			- width
			- image pixel values
			- an optional error code

		.png image files are decoded into a RGBA format, where:
			- R = red saturation (0 - 255)
			- G = green saturation (0 - 255)
			- B = blue saturation (0 - 255)
			- A = alpha / opacity (0 - 255) * 0 will give you a transparent image
		
		the RGBA values are stored in succession in an vector container called image. 
			- e.g. a fully red picture would look like this in the vector: 255, 0, 0, 255, 255, 0, 0, 255
			- because of the nature of the RGBA format, the vector size() will always be a factor of 4

		the width and height of the images are stored in unsigned ints called width and height

		an extra boolean variable is used to capture the return code of the decode function which can be used to determine if the function failed or not
	*/
	vector<unsigned char> image;
	char* filename = "images/testPicture.PNG";
	unsigned int width, height;
	bool error = lodepng::decode(image, width, height, filename);

	if(error)
	{
		cout << "image file could not be decoded" << endl;
	}
	else
	{
		/*
			CONTINUE YOUR CODE HERE
			e.g. insert function for processing the data
		*/

		// re-encode the image to a PNG <- I'm not sure if we need to do this yet, but it's better to have the code already there. 
		filename = "images/newTestPicture.PNG";
		error = lodepng::encode(filename, image, width, height);
		if(error)
		{
			cout << "image file could not be encoded" << endl;
		}
		else
		{
			// don't do anythin yet
		}
	}
}
