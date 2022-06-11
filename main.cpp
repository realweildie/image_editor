#include <iostream>
#include <fstream>
#include "inc/image.hpp"

int main()
{
	std::ifstream in("../in.bmp", std::ios::binary);

	img::BMP new_img(in);

	new_img.save("../out.bmp");

}