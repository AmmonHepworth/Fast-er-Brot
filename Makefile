release: Mandelbrot.cpp Mandelbrot.h main.cpp
	g++ -std=c++14 -O3 -g0 -o./release Mandelbrot.cpp Mandelbrot.h main.cpp
