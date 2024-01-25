#include <Interface.h>

template <class TypeInterface>
Interface<TypeInterface>::Interface()
{
	for(size_t i = 0; i <=31; i++)
		{
			std::vector<uint8_t> vec;
			vecResult.push_back(vec);
		}
}

template <class TypeInterface>
void Interface<TypeInterface>::addVCDU(TypeInterface& networkPackage, size_t packageLen)
{
	ParentVCDU* parentVCDU = new VCDU<TypeInterface>(networkPackage, packageLen);
	if(this->prevFrameCounter == -1)
		this->prevFrameCounter = parentVCDU->getToUlongFrameCounter();
	else
	{
		if((parentVCDU->getToUlongFrameCounter() - this->prevFrameCounter) != 1)
			throw std::runtime_error("violation of personnel order");
		this->prevFrameCounter = parentVCDU->getToUlongFrameCounter();
	}
	
	std::vector<uint8_t> lastCCSDSPackage = parentVCDU->getLastCCSDSPacksge();
	if(lastCCSDSPackage.size() != 0)
		{
			if(this->lastAPID == -1)
				throw std::runtime_error("undefined end of CCSDS package");
			else
			{
				this->vecResult[this->lastAPID].insert(vecResult[this->lastAPID].end(), lastCCSDSPackage.begin(), lastCCSDSPackage.end());
			}
		}
	
	if(parentVCDU->getToUlongVCID() != 63)
		{
			for(auto ccsds: parentVCDU->getCCSDSVector())
				{
					if(ccsds->getToUlongAPID() <= 31)
					{
						this->lastAPID = ccsds->getToUlongAPID();
						auto resEndIter = this->vecResult[this->lastAPID].end();
						std::vector<uint8_t> payloadVCDU = ccsds->getPayload();
						auto ccsdsBeginIter = payloadVCDU.begin();
						auto ccsdsEndIter = payloadVCDU.end();
						this->vecResult[this->lastAPID].insert(resEndIter, ccsdsBeginIter, ccsdsEndIter);
					}
				}
		}
	delete parentVCDU;
}

template <class TypeInterface>
std::vector<std::vector<uint8_t>> Interface<TypeInterface>::getCCSDSPackages() 
{
	if(this->prevFrameCounter == -1)
		throw std::runtime_error("Empty vecResilt");
	return this->vecResult;
}
