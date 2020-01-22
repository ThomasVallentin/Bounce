#ifndef ITERATORSH
#define ITERATORSH

#include "Camera.h"
#include <vector>

using namespace std;


class PixelArray
{
public:
	PixelArray() {};
	PixelArray(const int width, const int height) { initialize(width, height); }

	void initialize(const int width, const int height);
	vector3& get(const int width, const int height) { return m_pixels[height][width]; }
	void set(const int width, const int height, vector3& value) { m_pixels[height][width] = value; }
	int height() { return m_pixels.size(); }
	int width() { return m_pixels[0].size(); }

private:
	vector<vector<vector3>> m_pixels;
};

class PixelIterator
{
public:
	PixelIterator(PixelArray& pixels, int samples) { m_pixels = pixels; m_width = 0, m_height = 0; m_samples = samples; };
	void reset() { m_i = 0, m_width = 0, m_height = 0; m_sample = 0; };
	void next();
	vector3& getCurrent() { return m_pixels.get(m_width, m_height); }
	bool isDone() { return (m_width >= m_pixels.width() - 1) && (m_height >= m_pixels.height() - 1) && (m_sample >= m_samples - 1); };


	PixelArray m_pixels;
	int m_samples;

	int m_i;
	int m_width;
	int m_height;
	int m_sample;
};



#endif ITERATORSH