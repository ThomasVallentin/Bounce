#ifndef FILEADAPTERH
#define FILEADAPTERH

#include "RayTracer.hpp"
#include "Iterators.h"
#include "Color.hpp"

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

class RayTracer;

class AbstractFileAdapter
{
public:
	AbstractFileAdapter() = default;
	virtual bool write(RayTracer& tracer) const = 0;

//protected:
//    RayTracer* m_tracer{};
};


class PPMAdapter : public AbstractFileAdapter
{
public:
    PPMAdapter() : AbstractFileAdapter() {}
    bool write(RayTracer& tracer) const override;

};

#endif // FILEADAPTERH