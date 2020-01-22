#include "Iterators.h"

void PixelArray::initialize(const int width, const int height) {
	vector<vector<vector3>> newArray;
	newArray.resize(width);
	for (vector<vector3>& line : newArray)
	{
		line.resize(height);
	}
	m_pixels = newArray;
}

void PixelIterator::next()
{
	m_sample++;
	if (m_sample == m_samples) {
		m_sample = 0;

		m_width++;
		if (m_width == m_pixels.width()) {
			m_width = 0;

			m_height++;
			if (m_height == m_pixels.height()) {
				m_height = 0;
			}
		}
	}
}
