#ifndef INTERFACE_H
#define INTERFACE_H
#include <VCDU.h>


template <class TypeInterface>
class Interface
{
public:
	Interface();
	
	void addVCDU(TypeInterface& , size_t );
public:
	std::vector<std::vector<unsigned char>> getCCSDSPackages();
private:
	size_t prevFrameCounter = -1;
	size_t lastAPID = -1;
	std::vector<std::vector<unsigned char>> vecResult;	
};
template class Interface<std::vector<unsigned char>>;
#endif
