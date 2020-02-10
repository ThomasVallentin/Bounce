//#ifndef FILEADAPTERH
//#define FILEADAPTERH
//
//#include <string>
//#include "Iterators.h"
//
//using namespace std;
//
//class AbstractFileAdapter
//{
//public:
//	AbstractFileAdapter(const PixelArray& pixels) : m_pixels(pixels) {}
//	virtual bool write(const string path) const = 0;
//
//	const string extension() { return m_extension; }
//
//protected:
//	const PixelArray m_pixels;
//	string m_extension;
//};
//
//class PPMAdapter : public AbstractFileAdapter
//{
//public:
//	PPMAdapter(const PixelArray& pixels) : AbstractFileAdapter(pixels), m_extension(".ppm") {}
//	virtual bool write(const string path);
//
//protected:
//	string m_extension;
//};
//
//#endif FILEADAPTERH