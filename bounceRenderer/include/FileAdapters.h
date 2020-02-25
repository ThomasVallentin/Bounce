#ifndef FILEADAPTERH
#define FILEADAPTERH

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "Iterators.h"
#include "vector3.h"

class RayTracer;

class AbstractFileAdapter
{
public:
	explicit AbstractFileAdapter() {}
	virtual bool write(const std::string& path,
                       const unsigned int& width,
                       const unsigned int& height,
                       std::vector<float>& pixels) const = 0;

//protected:
//    RayTracer* m_tracer{};
};


class PPMAdapter : public AbstractFileAdapter
{
public:
    explicit PPMAdapter() : AbstractFileAdapter() {}
    bool write(const std::string& path,
               const unsigned int& width,
               const unsigned int& height,
               std::vector<float>& pixels) const override;

};

#endif // FILEADAPTERH