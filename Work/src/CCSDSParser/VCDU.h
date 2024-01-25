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
	VCDU(TypeVCDU& packageVCDU, size_t packageLen)
	{	
		if(packageLen < LEN_HEADER_VCDU_BYTE + LEN_HEADER_MDPU_BYTE)
			throw std::invalid_argument("Len shorted len of headr");
		size_t changedBitHeader = 0;
		/*Fill VCDU frames*/
		//create string bits header VCDU
		std::string strBitHeader = "";
		for(size_t i = 0; i < LEN_HEADER_VCDU_BYTE + LEN_HEADER_MDPU_BYTE; i++)
			strBitHeader += std::bitset<LEN_BYTE_IN_BIT>(packageVCDU[i]).to_string();
		//version
		for(size_t i = 0; i < LEN_VERSION_VCDU_BIT; i++)
			this->version[LEN_VERSION_VCDU_BIT - i - 1] = std::bitset<1>(strBitHeader[i + changedBitHeader])[0];
		changedBitHeader += LEN_VERSION_VCDU_BIT;
		//ObjID
		for(size_t i = 0; i < LEN_ObjID_VCDU_BIT; i++)
			this->ObjID[LEN_ObjID_VCDU_BIT - i - 1] = std::bitset<1>(strBitHeader[i + changedBitHeader])[0];
		changedBitHeader += LEN_ObjID_VCDU_BIT;
		//VCID
		for(size_t i = 0; i < LEN_VCID_VCDU_BIT; i++)
			this->VCID[LEN_VCID_VCDU_BIT - i - 1] = std::bitset<1>(strBitHeader[i + changedBitHeader])[0];
		changedBitHeader += LEN_VCID_VCDU_BIT;
		//frameCounter
		for(size_t i = 0; i < LEN_FRAME_COUNTER_VCDU_BIT; i++)
			this->frameCounter[LEN_FRAME_COUNTER_VCDU_BIT - i - 1] = std::bitset<1>(strBitHeader[i + changedBitHeader])[0];
		changedBitHeader += LEN_FRAME_COUNTER_VCDU_BIT;
		//repetitionFlag
		for(size_t i = 0; i < LEN_REPETITION_FLAG_VSDU_BIT; i++)
			this->repetitionFlag[LEN_REPETITION_FLAG_VSDU_BIT - i - 1] = std::bitset<1>(strBitHeader[i + changedBitHeader])[0];
		changedBitHeader += LEN_REPETITION_FLAG_VSDU_BIT;
		//reserved
		for(size_t i = 0; i < LEN_RESERVE_VCDU_BIT; i++)
			this->reserve[LEN_RESERVE_VCDU_BIT - i - 1] = std::bitset<1>(strBitHeader[i + changedBitHeader])[0];
		changedBitHeader += LEN_RESERVE_VCDU_BIT;
		/*Fill MDPU frames*/
		//reserveBitMDPU
		for(size_t i = 0; i < LEN_RESERVE_MDPU_BIT; i++)
			this->reserveBitMDPU[LEN_RESERVE_MDPU_BIT - i - 1] = std::bitset<1>(strBitHeader[i + changedBitHeader])[0];
		changedBitHeader += LEN_RESERVE_MDPU_BIT;
		//offsetBitMDPU
		for(size_t i = 0; i < LEN_OFFSET_MDPU_BIT; i++)
			this->offsetBitMDPU[LEN_OFFSET_MDPU_BIT - i - 1] = std::bitset<1>(strBitHeader[i + changedBitHeader])[0];
		changedBitHeader += LEN_OFFSET_MDPU_BIT;
		
		/*Fill vecCCSDS*/
		size_t changedBytePackage = changedBitHeader/LEN_BYTE_IN_BIT;
		size_t sizeEndCCSDSPacckage = changedBytePackage + this->offsetBitMDPU.to_ulong();
		for(size_t i = changedBytePackage; i < sizeEndCCSDSPacckage; i++)
			lastCCSDSPackage.push_back(packageVCDU[i]);
			
		changedBytePackage = sizeEndCCSDSPacckage;
		while(changedBytePackage < packageLen)
		{
			CCSDS<TypeVCDU>* ccsds = new CCSDS<TypeVCDU>(packageVCDU, packageLen, changedBytePackage);
			this->vecCCSDS.push_back(ccsds);
			
			changedBytePackage += ccsds->getCountUsedByte();
		}
	}
	~VCDU()
	{
		for(auto i: this->vecCCSDS)
			delete i;
		this->vecCCSDS.clear();
	}
	
public:
	std::vector<unsigned char> getLastCCSDSPacksge() override {return this->lastCCSDSPackage;};
	std::vector<ParentCCSDS*> getCCSDSVector() override {return this->vecCCSDS;}
	unsigned int getToUlongVersion() override { return this->version.to_ulong();}
	unsigned int getToUlongObjID() override { return this->ObjID.to_ulong();}
	unsigned int getToUlongVCID() override { return this->VCID.to_ulong();}
	unsigned int getToUlongFrameCounter() override { return this->frameCounter.to_ulong();}
	unsigned int getToUlongRepetitionFlag() override { return this->repetitionFlag.to_ulong();}
	unsigned int getToUlongReserve() override { return this->reserve.to_ulong();}
	
	unsigned int getToUlongReservedBitMDPU() override { return this->reserveBitMDPU.to_ulong();}
	unsigned int getToUlongOffsetBitMDPU() override {return this->offsetBitMDPU.to_ulong();} 
	
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
