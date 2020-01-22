#ifndef FILEADAPTERH
#define FILEADAPTERH

#include <string>

using namespace std;

class AbstractFileAdapter
{
public:
	virtual bool write(const string& path) const = 0;

	const string extension() { return m_extension; }
private:
	string m_extension;
};

#endif FILEADAPTERH