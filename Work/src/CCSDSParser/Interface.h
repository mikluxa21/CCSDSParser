#ifndef INTERFACE_H
#define INTERFACE_H

#include <CCSDSParser/VCDU.h>


template <class TypeInterface>
class Interface
{
public:
	Interface();
	
	void addVCDU(TypeInterface& , size_t );
public:
	std::vector<std::vector<uint8_t>> getCCSDSPackages();
private:
	size_t prevFrameCounter = -1;
	size_t lastAPID = -1;
	std::vector<std::vector<uint8_t>> vecResult;	
};
template class Interface<std::vector<uint8_t>>;

#endif
