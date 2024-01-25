#ifndef VCDU_H
#define VCDU_H
#include <CCSDS.h>

#include <bitset>
#include <string>
#include <vector>
#include <iterator>

class ParentVCDU
{
public:
	virtual std::vector<unsigned char> getLastCCSDSPacksge() {return std::vector<unsigned char>();};
	virtual std::vector<ParentCCSDS*> getCCSDSVector() {return std::vector<ParentCCSDS*>();}
	
	virtual unsigned int getToUlongVersion(){ return 0;}
	virtual unsigned int getToUlongObjID(){ return 0;}
	virtual unsigned int getToUlongVCID(){ return 0;}
	virtual unsigned int getToUlongFrameCounter(){ return 0;}
	virtual unsigned int getToUlongRepetitionFlag(){ return 0;}
	virtual unsigned int getToUlongReserve(){ return 0;}
	
	virtual unsigned int getToUlongReservedBitMDPU(){ return 0;}
	virtual unsigned int getToUlongOffsetBitMDPU(){return 0;} 
};


template <class TypeVCDU>
class VCDU: public ParentVCDU
{
public:
	VCDU(TypeVCDU& , size_t );
	~VCDU();
	
public:
	std::vector<unsigned char> getLastCCSDSPacksge() override;
	std::vector<ParentCCSDS*> getCCSDSVector() override;
	unsigned int getToUlongVersion() override;
	unsigned int getToUlongObjID() override;
	unsigned int getToUlongVCID() override;
	unsigned int getToUlongFrameCounter() override;
	unsigned int getToUlongRepetitionFlag() override;
	unsigned int getToUlongReserve() override;
	
	unsigned int getToUlongReservedBitMDPU() override;
	unsigned int getToUlongOffsetBitMDPU() override; 
	
private:

	std::vector<unsigned char> lastCCSDSPackage;
	std::vector<ParentCCSDS*> vecCCSDS;	

	std::bitset<LEN_VERSION_VCDU_BIT> version;
	std::bitset<LEN_VCID_VCDU_BIT> ObjID;
	std::bitset<LEN_VCID_VCDU_BIT> VCID;
	std::bitset<LEN_FRAME_COUNTER_VCDU_BIT> frameCounter;
	std::bitset<LEN_REPETITION_FLAG_VSDU_BIT> repetitionFlag;
	std::bitset<LEN_RESERVE_VCDU_BIT> reserve;
	
	std::bitset<LEN_RESERVE_MDPU_BIT> reserveBitMDPU;
	std::bitset<LEN_OFFSET_MDPU_BIT> offsetBitMDPU;
	size_t resultOffset;
};


template class VCDU<std::vector<unsigned char>>;
#endif
