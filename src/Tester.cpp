#include "Algorithms.cpp"
#include "lodepng.cpp" // an open source library for converting PNGs to a vector of pixels hosted on https://lodev.org/lodepng/

int main()
{
	/*
		the decode() function is given a filename and returns the:
			- height
			- width
			- color values
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

	// main function
	cout << "Welcome to the Image to ASCII program!\n" << endl;
	bool exit = false;
	while(!exit)
	{
		cout << "Input the path to the PNG image (Ex: images/file.PNG): ";
		string picturePath = "";
		getline(cin, picturePath);

		cout << "Input the desired width of the text output: ";
		string widthOfTextString = "";
		getline(cin, widthOfTextString);
		int widthOfText = stoi(widthOfTextString);

	int indexOfLastSlash = 0;
	for(int i = picturePath.length(); i >= 0; i--)
	{
		if(picturePath.substr(i, 1) == "/" || picturePath.substr(i, 1) == "\\")
		{
			indexOfLastSlash = i+1;
			break;
		}
	}



		// find out the path to the picture for outputting the txt file to the same location
		string alg1TxtName = "txt/" + picturePath.substr(indexOfLastSlash);
		alg1TxtName = alg1TxtName.substr(0, alg1TxtName.length() - 4) + "(1).txt";
		string alg2TxtName = "txt/" + picturePath.substr(indexOfLastSlash);
		alg2TxtName = alg2TxtName.substr(0, alg2TxtName.length() - 4) + "(2).txt";


		vector<unsigned char> colors;
		string filename = picturePath;
		unsigned int width, height;
		bool error = lodepng::decode(colors, width, height, filename);

		if (error)
		{
			cout << "image file could not be decoded" << endl;
		}
		else
		{
			//Nathan Test cases
			int textSize = widthOfText;
			Image source;
			source.LoadPNGImage(width, height, colors);

			Algorithm1 a1(source);
			a1.Run(alg1TxtName, textSize);

			Algorithm2 a2(source);
			a2.Run(alg2TxtName, textSize);

			cout << "Algorithms 1 and 2 have finished\nWould you like to run it again? (Y/N) " << endl;
			string s;
			getline(cin, s);
			exit = s[0] != 'Y';
		}
	}

}
