release: Mandelbrot.cpp Mandelbrot.h Mandelbrot2.h Mandelbrot2.cpp main.cpp
	g++ -std=c++14 -Werror -Wextra -Wall -O3 -o./release -pthread Mandelbrot.cpp Mandelbrot.h Mandelbrot2.h Mandelbrot2.cpp main.cpp
