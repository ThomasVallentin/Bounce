//#include "Iterators.h"
//
//void PixelArray::initialize(const int width, const int height) {
//	vector<vector<Vector3>> newArray;
//	newArray.resize(width);
//	for (vector<Vector3>& line : newArray)
//	{
//		line.resize(height);
//	}
//	m_pixels = newArray;
//}
//
//void const PixelIterator::next()
//{
//	m_width++;
//
//	if ((m_height >= m_pixels.height() - 1) && (m_width >= m_pixels.width()))
//	{
//		m_isDone = true;
//	}
//
//	if (m_width == m_pixels.width()) {
//		m_width = 0;
//
//		m_height++;
//		if (m_height == m_pixels.height()) {
//			m_height = 0;
//		}
//	}
//}
//
//void const PixelSampler::next()
//{
//	m_sample++;
//
//	if ((m_height >= m_pixels.height() - 1)
//		&& (m_width >= m_pixels.width() - 1)
//		&& (m_sample >= m_samples))
//	{
//		m_isDone = true;
//	}
//
//	if (m_sample == m_samples) {
//		m_sample = 0;
//
//		m_width++;
//		if (m_width == m_pixels.width()) {
//			m_width = 0;
//
//			m_height++;
//			if (m_height == m_pixels.height()) {
//				m_height = 0;
//			}
//		}
//	}
//}
//
//void const ProgressivePixelSampler::next()
//{
//	m_width++;
//
//	if ((m_height >= m_pixels.height() - 1)
//		&& (m_sample >= m_samples - 1)
//		&& (m_width >= m_pixels.width()))
//	{
//		m_isDone = true;
//	}
//
//	if (m_width == m_pixels.width()) {
//		m_width = 0;
//
//		m_height++;
//		if (m_height == m_pixels.height()) {
//			m_height = 0;
//
//			m_sample++;
//			if (m_sample == m_samples) {
//				m_sample = 0;
//
//			}
//		}
//	}
//}
