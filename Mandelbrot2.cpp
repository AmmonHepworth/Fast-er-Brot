#include "Mandelbrot2.h"
#include <iostream>
#include <cmath>
#include <cstring> 
#include <fstream>
#include <thread>


Mandelbrot2::Mandelbrot2(std::string file, int r, int c, double x_1, double y_1, double x_2, double y_2, int maxIter, int numThreads):fileName(file),rows(r),cols(c),x1(x_1),y1(y_1),x2(x_2),y2(y_2),maxIters(maxIter),threadCount(numThreads)
{
	pixelValue.reserve(3*rows*cols);
}


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
			x = 0.0;
			y = 0.0;
			iteration = 0;

			while (x*x + y*y < 4  &&  iteration < maxIters) {
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
			pixelValue[3*i]   = r;
			pixelValue[(3*i)+1] = g;
			pixelValue[(3*i)+2] = b;
		}
	}
}


void Mandelbrot2::generateParallel()
{

	std::vector<std::thread> threads;
	for(int i=1;i<=threadCount-1;i++)
	{
		threads.push_back(std::thread([=](){this->createpixelFabric((i-1)*(rows*cols)/threadCount,i*(rows*cols)/threadCount);}));
	}
	createpixelFabric((threadCount-1)*(rows*cols)/threadCount,threadCount*(rows*cols)/threadCount);

	for(auto && t:threads)
	{
		t.join();
	}

}


void Mandelbrot2::createpixelFabric(int start, int end)
{

	int r,g,b;
	double x0;
	double y0;
	double x = 0.0;
	double y = 0.0;
	int iteration = 0;
	double xtemp;
	for(int i=start;i<end;++i)
	{
			x0 = x1+(x2-x1)/cols*(i%cols);
			y0 = y1+(y2-y1)/rows*(i/rows);
			x = 0.0;
			y = 0.0;
			iteration = 0;

			while (x*x + y*y < 4  &&  iteration < maxIters) {
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
			pixelValue[3*i] = r;
			pixelValue[(3*i)+1] = g;
			pixelValue[(3*i)+2] = b;
	}

}
