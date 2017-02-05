release: Mandelbrot2.h Mandelbrot2.cpp ThreadPool.h ThreadPool.cpp TSQ.h main.cpp
	g++ -std=c++14 -Werror -Wextra -Wall -O3 -o./release -pthread  Mandelbrot2.h Mandelbrot2.cpp ThreadPool.h ThreadPool.cpp TSQ.h main.cpp
debug: Mandelbrot2.h Mandelbrot2.cpp main.cpp
	g++ -std=c++14  -Wextra -Wall -O0 -g -o./debug -pthread Mandelbrot2.h Mandelbrot2.cpp main.cpp ThreadPool.h ThreadPool.cpp TSQ.h
