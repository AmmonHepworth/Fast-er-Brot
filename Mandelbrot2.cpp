#include "Mandelbrot2.h"
#include <iostream>
#include <cmath>
#include <cstring>
#include <fstream>


Mandelbrot2::Mandelbrot2(std::string file, int r, int c, double x_1, double y_1, double x_2, double y_2, int maxIter):fileName(file),rows(r),cols(c),x1(x_1),y1(y_1),x2(x_2),y2(y_2),maxIters(maxIter){pixelValue.reserve(rows*cols);}


void Mandelbrot2::write()
{
	std::ofstream outFile;
	outFile.open(fileName);
	outFile << "P3" << std::endl << rows << " " << cols << std::endl << 255 << std::endl;

	for(auto&& p:pixelValue) outFile << p << " ";
}

//PSEUDOCODE USED FROM WIKIPEDIA
void Mandelbrot2::generate()
{
	int r,g,b;
	double x0;
	double y0;
	double x = 0.0;
	double y = 0.0;
	int iteration = 0;
	double xtemp;
	
	for(int i=0;i<rows;++i)
	{
		for(int j=0;j<cols;++j)
		{
			x0 = x1+(x2-x1)/cols*j;
			y0 = y1+(y2-y1)/rows*i;
			//x0 = (j-cols/(x1)*
			x = 0.0;
			y = 0.0;
			iteration = 0;

			while (x*x + y*y < 2*2  &&  iteration < maxIters) {
				xtemp = x*x - y*y + x0;
				y = 2*x*y + y0;
				x = xtemp;
				++iteration;
			}
			if (iteration == 1) {
				r = 0; g = 0; b = 0;
			}
			else {
				r = abs(iteration % 255 * sin(iteration));
				g = iteration % 255;
				b = iteration % 255;
			}
			pixelValue.push_back(r);	
			pixelValue.push_back(g);	
			pixelValue.push_back(b);	
		}
	}
}

