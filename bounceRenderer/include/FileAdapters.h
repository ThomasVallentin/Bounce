#ifndef FILEADAPTERH
#define FILEADAPTERH

#include "RayTracer.h"
#include "Iterators.h"
#include "Vector3.hpp"

#include <vector>
#include <string>
#include <iostream>
#include <fstream>


class RayTracer;

class AbstractFileAdapter
{
public:
	explicit AbstractFileAdapter() {}
	virtual bool write(RayTracer& tracer) const = 0;

//protected:
//    RayTracer* m_tracer{};
};


class PPMAdapter : public AbstractFileAdapter
{
public:
    explicit PPMAdapter() : AbstractFileAdapter() {}
    bool write(RayTracer& tracer) const override;

};

#endif // FILEADAPTERH