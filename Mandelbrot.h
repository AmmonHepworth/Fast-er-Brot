#ifndef MANDELBROT_H
#define MANDELBROT_H

#include<vector>
#include <string>
#include <complex>
class Mandelbrot{

	public:
	Mandelbrot(std::string file, int rows, int cols, std::complex<double> c1, std::complex<double> c2, int maxIters);

	std::vector<int> pixelValue;
	void generate();
	void write();

	//void generate2();

	private:
	int mandelbrot(std::complex<double>, int);
	void storeColor(std::complex<double> c1);
	std::string fileName="";
	int rows=512;
	int cols=512;
	std::complex<double> c1 = {-2,1};
	std::complex<double> c2 = {1,-1};
	int maxIters=1000;


};


#endif
