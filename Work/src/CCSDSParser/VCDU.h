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
	virtual std::vector<uint8_t> getLastCCSDSPacksge() {return std::vector<uint8_t>();};
	virtual std::vector<ParentCCSDS*> getCCSDSVector() {return std::vector<ParentCCSDS*>();}
	
	virtual uint32_t getToUlongVersion(){ return 0;}
	virtual uint32_t getToUlongObjID(){ return 0;}
	virtual uint32_t getToUlongVCID(){ return 0;}
	virtual uint32_t getToUlongFrameCounter(){ return 0;}
	virtual uint32_t getToUlongRepetitionFlag(){ return 0;}
	virtual uint32_t getToUlongReserve(){ return 0;}
	
	virtual uint32_t getToUlongReservedBitMDPU(){ return 0;}
	virtual uint32_t getToUlongOffsetBitMDPU(){return 0;} 
};


template <class TypeVCDU>
class VCDU: public ParentVCDU
{
public:
	VCDU(TypeVCDU& , size_t );
	~VCDU();
	
public:
	std::vector<uint8_t> getLastCCSDSPacksge() override;
	std::vector<ParentCCSDS*> getCCSDSVector() override;
	uint32_t getToUlongVersion() override;
	uint32_t getToUlongObjID() override;
	uint32_t getToUlongVCID() override;
	uint32_t getToUlongFrameCounter() override;
	uint32_t getToUlongRepetitionFlag() override;
	uint32_t getToUlongReserve() override;
	
	uint32_t getToUlongReservedBitMDPU() override;
	uint32_t getToUlongOffsetBitMDPU() override; 
	
private:

	std::vector<uint8_t> lastCCSDSPackage;
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


template class VCDU<std::vector<uint8_t>>;

#endif
