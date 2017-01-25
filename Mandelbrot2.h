#ifndef MANDELBROT2_H
#define MANDELBROT2_H

#include<vector>
#include <string>
class Mandelbrot2{

	public:
	Mandelbrot2(std::string file, int rows, int cols, double x_1, double y_1, double x_2, double y_2, int maxIters, int numThreads);

	std::vector<int> pixelValue;
	void generate();
	void write();
	void generateParallel();
	void createpixelFabric(int pixelStart, int pixelEnd);
	void stitchFabrics();

	private:
	std::string fileName;
	int rows;
	int cols;
	double x1,y1,x2,y2;
	int maxIters;
	int threadCount;



};


#endif
