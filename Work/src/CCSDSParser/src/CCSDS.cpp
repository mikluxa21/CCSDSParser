#include "../CCSDS.h"


template <class TypeCCSDS>
CCSDS<TypeCCSDS>::CCSDS(TypeCCSDS& packageCCSDS, size_t packageLen, size_t packageChanged)
{
	if(packageLen < LEN_HEADER_CCSDS_BYTE)
		throw std::invalid_argument("Len shorted len of headr");
	
	
	size_t changedBitHeader = 0;
	/*Fill CCSDS frames*/
	//create string bits header CCSDS
	std::string strBitHeader = "";
	for(size_t i = packageChanged; i < packageChanged + LEN_HEADER_CCSDS_BYTE; i++)
		strBitHeader += std::bitset<LEN_BYTE_IN_BIT>(packageCCSDS[i]).to_string();
	//version
	for(size_t i = 0; i < LEN_VERSION_CCSDS_BIT; i++)
		this->version[LEN_VERSION_CCSDS_BIT - i - 1] = std::bitset<1>(strBitHeader[i + changedBitHeader])[0];
	changedBitHeader += LEN_VERSION_CCSDS_BIT;
	//type
	for(size_t i = 0; i < LEN_TYPE_CCSDS_BIT; i++)
		this->type[LEN_TYPE_CCSDS_BIT - i - 1] = std::bitset<1>(strBitHeader[i + changedBitHeader])[0];
	changedBitHeader += LEN_TYPE_CCSDS_BIT;
	//helpersHeaderFlag
	for(size_t i = 0; i < LEN_HELPER_HEADER_FLAG_CCSDS_BIT; i++)
		this->helperHeaderFlag[LEN_HELPER_HEADER_FLAG_CCSDS_BIT - i - 1] = std::bitset<1>(strBitHeader[i + changedBitHeader])[0];
	changedBitHeader += LEN_HELPER_HEADER_FLAG_CCSDS_BIT;
	//APID
	for(size_t i = 0; i < LEN_APID_CCSDS_BIT; i++)
		this->APID[LEN_APID_CCSDS_BIT - i - 1] = std::bitset<1>(strBitHeader[i + changedBitHeader])[0];
	changedBitHeader += LEN_APID_CCSDS_BIT;
	//fragmentationFlag
	for(size_t i = 0; i < LEN_FRAGMENTATION_FLAG_CCSDS_BIT; i++)
		this->fragmentationFlag[LEN_FRAGMENTATION_FLAG_CCSDS_BIT - i - 1] = std::bitset<1>(strBitHeader[i + changedBitHeader])[0];
	changedBitHeader += LEN_FRAGMENTATION_FLAG_CCSDS_BIT;
	//frameCounter
	for(size_t i = 0; i < LEN_FRAME_COUNTER_CCSDS_BIT; i++)
		this->frameCounter[LEN_FRAME_COUNTER_CCSDS_BIT - i - 1] = std::bitset<1>(strBitHeader[i + changedBitHeader])[0];
	changedBitHeader += LEN_FRAME_COUNTER_CCSDS_BIT;
	//size
	for(size_t i = 0; i < LEN_SIZE_CCSDS_BIT; i++)
		this->size[LEN_SIZE_CCSDS_BIT - i - 1] = std::bitset<1>(strBitHeader[i + changedBitHeader])[0];
	changedBitHeader += LEN_SIZE_CCSDS_BIT;
	//time
	for(size_t i = 0; i < LEN_TIME_CCSDS_BIT; i++)
		this->time[LEN_TIME_CCSDS_BIT - i - 1] = std::bitset<1>(strBitHeader[i + changedBitHeader])[0];
	changedBitHeader += LEN_TIME_CCSDS_BIT;
	
	/*Fill frames: payload | countUsedByte*/
	size_t changedByteHeader = changedBitHeader / LEN_BYTE_IN_BIT;
	size_t size;
	switch(this->fragmentationFlag.to_ulong())  //01-frirst | 00-midle | 10-last | 11-one package
	{
		case 2:          //if last or midle
			size = packageLen;
			break;
		case 3:          //if last or midle
			size = packageLen;
			break;
		default:
			size = this->size.to_ulong() + packageChanged + changedByteHeader;
			break;
	}
	for(size_t i = packageChanged + changedByteHeader; i < size; i++)
		this->payload.push_back(packageCCSDS[i]);
	this->countUsedByte = size - packageChanged;
	
}


template<class TypeCCSDS>
TypeCCSDS CCSDS<TypeCCSDS>::getPayload() { return this->payload;}

template<class TypeCCSDS>
size_t CCSDS<TypeCCSDS>::getCountUsedByte() { return this->countUsedByte;}

template<class TypeCCSDS>
uint32_t CCSDS<TypeCCSDS>::getToUlongVersion(){ return this->version.to_ulong();}

template<class TypeCCSDS>
uint32_t CCSDS<TypeCCSDS>::getToUlongType(){ return this->type.to_ulong();}

template<class TypeCCSDS>
uint32_t CCSDS<TypeCCSDS>::getToUlongHelpersHeaderFlag() { return this->helperHeaderFlag.to_ulong();}

template<class TypeCCSDS>
uint32_t CCSDS<TypeCCSDS>::getToUlongAPID() { return this->APID.to_ulong();}

template<class TypeCCSDS>
uint32_t CCSDS<TypeCCSDS>::getToUlongFragmentationFlag(){ return this->fragmentationFlag.to_ulong();}

template<class TypeCCSDS>
uint32_t CCSDS<TypeCCSDS>::getToUlongFrameCounter(){ return this->frameCounter.to_ulong();}

template<class TypeCCSDS>
uint32_t CCSDS<TypeCCSDS>::getToUlongSize() { return this->size.to_ulong();}

template<class TypeCCSDS>
std::bitset<64> CCSDS<TypeCCSDS>::getToBitsetTime() { return this->time;}


