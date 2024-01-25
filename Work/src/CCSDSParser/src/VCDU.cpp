#include <VCDU.h>
template<class TypeVCDU>
VCDU<TypeVCDU>::VCDU(TypeVCDU& packageVCDU, size_t packageLen)
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

template<class TypeVCDU>
VCDU<TypeVCDU>::~VCDU()
{
	for(auto i: this->vecCCSDS)
		delete i;
	this->vecCCSDS.clear();
}
template<class TypeVCDU>
std::vector<uint8_t> VCDU<TypeVCDU>::getLastCCSDSPacksge(){return this->lastCCSDSPackage;};

template<class TypeVCDU>
std::vector<ParentCCSDS*> VCDU<TypeVCDU>::getCCSDSVector(){return this->vecCCSDS;}

template<class TypeVCDU>
uint32_t VCDU<TypeVCDU>::getToUlongVersion(){ return this->version.to_ulong();}

template<class TypeVCDU>
uint32_t VCDU<TypeVCDU>::getToUlongObjID(){ return this->ObjID.to_ulong();}

template<class TypeVCDU>
uint32_t VCDU<TypeVCDU>::getToUlongVCID(){ return this->VCID.to_ulong();}

template<class TypeVCDU>
uint32_t VCDU<TypeVCDU>::getToUlongFrameCounter() { return this->frameCounter.to_ulong();}

template<class TypeVCDU>
uint32_t VCDU<TypeVCDU>::getToUlongRepetitionFlag() { return this->repetitionFlag.to_ulong();}

template<class TypeVCDU>
uint32_t VCDU<TypeVCDU>::getToUlongReserve() { return this->reserve.to_ulong();}

template<class TypeVCDU>
uint32_t VCDU<TypeVCDU>::getToUlongReservedBitMDPU() { return this->reserveBitMDPU.to_ulong();}

template<class TypeVCDU>
uint32_t VCDU<TypeVCDU>::getToUlongOffsetBitMDPU() {return this->offsetBitMDPU.to_ulong();} 
	
