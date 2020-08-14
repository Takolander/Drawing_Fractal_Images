#include <iostream>
#include <cstdint>
#include <memory>
#include "Bitmap.h"
#include "Mandelbrot.h"

int main() {

	int const WIDTH = 800;
	int const HEIGHT = 600;

	Bitmap bitmap(WIDTH, HEIGHT);

	double min = 999999;
	double max = -999999;

	std::unique_ptr<int[]> histogram(new int[Mandelbrot::MAX_ITERATIONS + 1]{0});

	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			double xFractal = (x - WIDTH/2 - 200) * 2.0/ HEIGHT;
			double yFractal = (y - HEIGHT/2) * 2.0 / HEIGHT;

			int iterations = Mandelbrot::getIterations(xFractal, yFractal);

			histogram[iterations]++;

			uint8_t color = (uint8_t)(256 * (double)iterations / Mandelbrot::MAX_ITERATIONS);

			color = color * color * color;

			bitmap.setPixel(x, y, 0, color, 0);
			if (color < min) min = color;
			if (color > max) max = color;
		}
	}

	std::cout << std::endl;

	int count = 0;
	for (int i = 0; i <= Mandelbrot::MAX_ITERATIONS; i++) {
		std::cout << histogram[i] << " " << std::flush;
		count += histogram[i];
	}

	std::cout << count << "; " << WIDTH * HEIGHT << std::endl;

	std::cout << std::endl;

	std::cout << min << ", " << max << std::endl;

	bitmap.write("test.bmp");

	std::cout << "Finished." << std::endl;
	return 0;
}