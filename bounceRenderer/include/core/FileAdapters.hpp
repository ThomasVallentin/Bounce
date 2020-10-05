#ifndef FILEADAPTERH
#define FILEADAPTERH

#include "Color.hpp"

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

class FileAdapter
{
public:
	FileAdapter() = default;
	virtual bool write(const std::string& outpath, const unsigned int& width, const unsigned int& height, const float* pixels) const = 0;

//protected:
//    RayTracer* m_tracer{};
};




#endif // FILEADAPTERH