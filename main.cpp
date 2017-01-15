#include "Mandelbrot2.h"
#include "Timer.h"
#include <iostream>


int main(){

	std::cout << "THIS PROGRAM ONLY OUTPUTS ONE IMAGE TO A FILE, IT ONLY GENERATES THE OTHERS" << std::endl;
	std::cout << "Five image generations will be used for the calculations." << std::endl;

	Mandelbrot2 m1("m2.ppm",512,512,(double)-2,(double)1,(double)1,(double)-1,1024);
	Timer mand1;
	std::cout << std::endl << "Warming up the cache for accurate timings, please wait..." << std::endl;
	m1.generate();
	for(int i=0;i<5;++i)
	{
		std::cout << mand1.timeTask<Mandelbrot2, &Mandelbrot2::generate>(new Mandelbrot2("m1.ppm", 512, 512,(double)-2,(double)1,(double)1,(double)-1, 1024)) << std::endl;
	}
	std::cout << "Average: " << mand1.getAverageTime() << std::endl;
	std::cout << "Std Dev: " << mand1.getStdDev() << std::endl;
	m1.write();
	return 0;
}

