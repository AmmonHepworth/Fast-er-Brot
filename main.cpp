#include "Mandelbrot2.h"
#include "Timer.h"
#include "ThreadPool.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>


int main(){

	Mandelbrot2 m1("m1.ppm",512,512,(double)-2,(double)1,(double)1,(double)-1,1024, 4, 5);
	m1.generateParallelPool();
	Timer mand1;
	std::vector<std::ofstream> outFile;
	outFile.push_back(std::ofstream("./graphFiles/pixel.dat"));
	outFile.push_back(std::ofstream("./graphFiles/lessRow.dat"));
	outFile.push_back(std::ofstream("./graphFiles/row.dat"));
	outFile.push_back(std::ofstream("./graphFiles/moreRow.dat"));
	outFile.push_back(std::ofstream("./graphFiles/rowDivN.dat"));
	
	for(int chunkType=1;chunkType<6;++chunkType)
	{
		std::cout << "ChunkType: " << chunkType << std::endl;
		for(int i=1; i<9; ++i)
		{
			{
				outFile[chunkType-1] << i << " " ;
				outFile[chunkType-1] << mand1.timeTask<Mandelbrot2, &Mandelbrot2::generateParallelPool>(new Mandelbrot2("m1.ppm", 512, 512,(double)-2,(double)1,(double)1,(double)-1, 1024, i, chunkType)) << std::endl;
			}
		}
	}
	m1.write();

	/*
		 std::cout << "THIS PROGRAM ONLY OUTPUTS ONE IMAGE TO A FILE, IT ONLY GENERATES THE OTHERS" << std::endl;
		 std::cout << "Five image generations will be used for the calculations." << std::endl;

		 Mandelbrot2 m1("m1.ppm",512,512,(double)-2,(double)1,(double)1,(double)-1,1024, 4);
		 Timer mand1,mand2;

		 std::cout << std::endl << "Warming up the cache for accurate timings, please wait..." << std::endl;

		 m1.generateParallel();

		 for(int i=0;i<5;++i)
		 {
		 std::cout << mand2.timeTask<Mandelbrot2, &Mandelbrot2::generate>(new Mandelbrot2("m1.ppm", 512, 512,(double)-2,(double)1,(double)1,(double)-1, 1024, 4)) << std::endl;
		 }
		 std::cout << "Average: " << mand2.getAverageTime() << std::endl;
		 std::cout << "Std Dev: " << mand2.getStdDev() << std::endl;


		 std::ofstream graphData("data.dat");
		 std::string data;

	//generates average mandelbrots for 1-4 threads
	for(int threads=1; threads<9; ++threads){
	mand1 = Timer();
	std::cout << "------------------------------------------------" << std::endl;
	std::cout << threads << " THREADS: " << std::endl << std::endl;
	for(int i=0;i<5;++i)
	{

	std::cout << mand1.timeTask<Mandelbrot2, &Mandelbrot2::generateParallel>(new Mandelbrot2("m"+std::to_string(threads)+".ppm", 512, 512,(double)-2,(double)1,(double)1,(double)-1, 1024, threads)) << std::endl;

	}
	std::cout << "Average: " << mand1.getAverageTime() << std::endl;
	std::cout << "Std Dev: " << mand1.getStdDev() << std::endl;
	graphData << threads << " " << mand1.getAverageTime() << std::endl;
	std::cout << std::endl << "Speedup over the average: " << mand2.getAverageTime()/mand1.getAverageTime() << std::endl;
	std::cout << "Efficiency: " << (mand2.getAverageTime()/mand1.getAverageTime())/threads << std::endl;

	}

	m1.write();
	return system("gnuplot -p gnucmd.txt");

*/
}
