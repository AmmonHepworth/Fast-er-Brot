#include "Mandelbrot.h"
#include "Timer.h"
#include <complex>
#include <iostream>


int main(){

	std::complex<double> c1, c2;
	std::cout << "THIS PROGRAM ONLY OUTPUTS ONE IMAGE TO A FILE, IT ONLY GENERATES THE OTHERS" << std::endl;
	std::cout << "Five image generations will be used for the calculations." << std::endl;

	c1.real(-2);
	c1.imag(1);
	c2.real(1);
	c2.imag(-1);

	Mandelbrot m1("m1.ppm",512,512,c1,c2,1024);
	Timer mand1;
	m1.generate();
	for(int i=0;i<5;++i)
	{
		std::cout << mand1.timeTask<Mandelbrot, &Mandelbrot::generate>(new Mandelbrot("m1.ppm", 512, 512, c1, c2, 1024)) << std::endl;
	}
	std::cout << "Average: " << mand1.getAverageTime() << std::endl;
	std::cout << "Std Dev: " << mand1.getStdDev() << std::endl;
	m1.write();
	return 0;
}

