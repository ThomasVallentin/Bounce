//#ifndef ITERATORSH
//#define ITERATORSH
//
//#include "Camera.h"
//#include "mathUtils.h"
//#include <vector>
//
//// == ABSTRACT ITERATOR ===========================================================================
//
//class AbstractIterator {
//public:
//	virtual void const begin() = 0;
//	virtual void const next() = 0;
//	virtual bool const isDone() { return m_isDone; };
//
//protected:
//	bool m_isDone;
//};
//
//// == PIXEL ARRAY =================================================================================
//
//class PixelArray
//{
//public:
//	PixelArray() {};
//	PixelArray(const int width, const int height) { initialize(width, height); }
//
//	void initialize(const int width, const int height);
//	Vector3& get(const int width, const int height) { return m_pixels[height][width]; }
//	void set(const int width, const int height, Vector3& value) { m_pixels[height][width] = value; }
//	int height() { return m_pixels.size(); }
//	int width() { return m_pixels[0].size(); }
//
//private:
//	vector<vector<Vector3>> m_pixels;
//};
//
//// == PIXEL ITERATOR ==============================================================================
//
//class PixelIterator : public AbstractIterator
//{
//public:
//	PixelIterator() { m_width = 0, m_height = 0; m_isDone = false; }
//	PixelIterator(PixelArray& pixels) { m_pixels = pixels; m_width = 0, m_height = 0; };
//	virtual void const begin() { m_width = 0, m_height = 0;};
//	virtual void const next();
//	virtual bool const isDone() { return m_isDone; }
//
//	Vector3& get() { return m_pixels.get(m_width, m_height); }
//	int const height() { return m_height; }
//	int const width() { return m_width; }
//
//protected:
//	PixelArray m_pixels;
//
//	int m_width;
//	int m_height;
//	bool m_isDone;
//};
//
//// == PIXEL SAMPLER ===============================================================================
//
//class PixelSampler: public PixelIterator
//{
//public:
//	PixelSampler() : PixelIterator(), m_sample(0), m_samples(0) {}
//	PixelSampler(PixelArray& pixels, const int samples) : PixelIterator(pixels), m_sample(0), m_samples(samples) {}
//	virtual void const begin() { m_width = 0, m_height = 0; m_sample = 0; }
//	virtual void const next();
//
//	int const samples() { return m_samples; }
//	int const sample() { return m_sample; }
//	float const u() { return float(m_width + randomFlt()) / m_pixels.width(); }
//	float const v() { return float(m_height + randomFlt()) / m_pixels.height(); }
//
//protected:
//	const int m_samples;
//	int m_sample;
//
//};
//
//// == PROGRESSIVE PIXEL SAMPLER ===================================================================
//
//class ProgressivePixelSampler : public PixelSampler
//{
//public:
//	ProgressivePixelSampler() : PixelSampler() {}
//	ProgressivePixelSampler(PixelArray& pixels, const int samples) : PixelSampler(pixels, samples) {}
//	virtual void const next();
//
//};
//
//
//#endif ITERATORSH