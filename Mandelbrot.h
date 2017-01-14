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
	int maxIters;
	std::string fileName;
	int rows;
	int cols;
	std::complex<double> c1;
	std::complex<double> c2;


};


#endif
