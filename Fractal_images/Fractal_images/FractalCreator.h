#ifndef FRACTALCREATOR_H_
#define FRACTALCREATOR_H_
#include <string>
#include <memory>
#include <cstdint>
#include <math.h>
#include <vector>
#include "ZoomList.h"
#include "Bitmap.h"
#include "Mandelbrot.h"
#include "RGB.h"

class FractalCreator {
private:
	int m_width;
	int m_height;
	std::unique_ptr<int[]> m_histogram;
	std::unique_ptr<int[]> m_fractal;
	Bitmap m_bitmap;
	ZoomList m_zoomList;
	int m_total{ 0 };

	std::vector<int> m_ranges;
	std::vector<RGB> m_colors;

public:
	FractalCreator(int width, int height);
	virtual ~FractalCreator();
	void addZoom(const Zoom& zoom);
	void addRange(double rangeEnd, const RGB& rgb);

private:
	void calculateIterations();
	void calculateTotalIterations();
	void drawFractal();
	void writeBitmap(std::string name);

public:
	void run(std::string name);

};

#endif
