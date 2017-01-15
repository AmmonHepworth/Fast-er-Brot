#include <iostream>
#include <cmath>
#include <cstring>
#include <fstream>
#include <complex>
#include "Mandelbrot.h"

const int MAXITERS = 1024;

Mandelbrot::Mandelbrot(std::string file, int r, int c, std::complex<double> tlRange, std::complex<double> lrRange, int maxIter):fileName(file),rows(r),cols(c),c1(tlRange),c2(lrRange),maxIters(maxIter){pixelValue.reserve(rows*cols);}

int Mandelbrot::mandelbrot(std::complex<double> c, int maxIters) {

	int i = 0;
	std::complex<double> z;
	z = c;
	while (abs(z) <= 2 && i<maxIters) {
		z = z*z + c;
		++i;
	}
	return i;
}

void Mandelbrot::generate()
{
	std::complex<double> ci;
	int temp = c1.real();

	ci = c1;
	for (int i = 0; i<rows; ++i) {
		ci.imag(c1.imag() + (c2.imag() - c1.imag()) / rows*i);
		for (int j = 0; j<cols; ++j) {
			ci.real(c1.real() + (c2.real() - c1.real()) / cols*j);
			storeColor(ci);
		}
		ci.real(temp);
	}
}

void Mandelbrot::write()
{
	std::ofstream outFile;
	outFile.open(fileName);
	outFile << "P3" << std::endl << rows << " " << cols << std::endl << 255 << std::endl;

	for(auto&& p:pixelValue) outFile << p << " ";
}

void Mandelbrot::storeColor(std::complex<double> ci)
{
	int r,g,b;
	auto cValue = mandelbrot(ci,maxIters);
	if (cValue == 0) {
		r = 0; g = 0; b = 0;
	}
	else {
		r = cValue % 255 * sin(cValue);
		g = cValue % 255 * cos(cValue);
		b = cValue % 255;
	}

	pixelValue.push_back(r);	
	pixelValue.push_back(g);	
	pixelValue.push_back(b);	
}
/*
void Mandelbrot::generate2()
{
	int r,g,b;
	for(int i=0;i<rows;++i)
	{
		for(int j=0;i<cols;++j)
		{
			double x0 = x1+(x1-x2)/cols*i;
			double y0 = y1+(y1-y2)/rows*j;
			double x = 0.0;
			double y = 0.0;
			int iteration = 0;
			int max_iteration = 1000;
			double xtemp;
			while (x*x + y*y < 2*2  &&  iteration < max_iteration) {
				xtemp = x*x - y*y + x0;
				y = 2*x*y + y0;
				x = xtemp;
				++iteration;
			}
			if (iteration == 0) {
				r = 0; g = 0; b = 0;
			}
			else {
				r = iteration % 255 * sin(iteration);
				g = iteration % 255 * cos(iteration);
				b = iteration % 255;
			}
			pixelValue.push_back(r);	
			pixelValue.push_back(g);	
			pixelValue.push_back(b);	

			//color = palette[iteration]
			//	plot(Px, Py, color)
		}
	}
}
*/
