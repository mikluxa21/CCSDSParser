#ifndef CCSDS_H
#define CCSDS_H

#include <bitset>
#include <string>
#include <vector>
#include <iterator>

const uint8_t LEN_BYTE_IN_BIT = 8;

//Lenghts optional frames CCSDS header
const uint8_t LEN_VERSION_CCSDS_BIT = 3;
const uint8_t LEN_TYPE_CCSDS_BIT = 1;
const uint8_t LEN_HELPER_HEADER_FLAG_CCSDS_BIT = 1;
const uint8_t LEN_APID_CCSDS_BIT = 11;
const uint8_t LEN_FRAGMENTATION_FLAG_CCSDS_BIT = 2;
const uint8_t LEN_FRAME_COUNTER_CCSDS_BIT = 14;
const uint8_t LEN_SIZE_CCSDS_BIT = 16;
const uint8_t LEN_TIME_CCSDS_BIT = 64;
const uint8_t LEN_HEADER_CCSDS_BIT = (LEN_VERSION_CCSDS_BIT + LEN_TYPE_CCSDS_BIT + LEN_HELPER_HEADER_FLAG_CCSDS_BIT + LEN_APID_CCSDS_BIT + LEN_FRAGMENTATION_FLAG_CCSDS_BIT + LEN_FRAME_COUNTER_CCSDS_BIT + LEN_SIZE_CCSDS_BIT + LEN_TIME_CCSDS_BIT);
const uint8_t LEN_HEADER_CCSDS_BYTE = (LEN_HEADER_CCSDS_BIT/LEN_BYTE_IN_BIT);


//Lenghts optional frames MDPU header
const uint8_t LEN_RESERVE_MDPU_BIT = 5;
const uint8_t LEN_OFFSET_MDPU_BIT = 11;
const uint8_t LEN_HEADER_MDPU_BIT = (LEN_RESERVE_MDPU_BIT + LEN_OFFSET_MDPU_BIT);
const uint8_t LEN_HEADER_MDPU_BYTE = (LEN_HEADER_MDPU_BIT/LEN_BYTE_IN_BIT);

//Lenghts optional frames VCDU header	
const uint8_t LEN_VERSION_VCDU_BIT = 2;
const uint8_t LEN_ObjID_VCDU_BIT = 8;
const uint8_t LEN_VCID_VCDU_BIT = 6;
const uint8_t LEN_FRAME_COUNTER_VCDU_BIT = 24;
const uint8_t LEN_REPETITION_FLAG_VSDU_BIT = 1;
const uint8_t LEN_RESERVE_VCDU_BIT = 7;
const uint8_t LEN_HEADER_VCDU_BIT = (LEN_VERSION_VCDU_BIT + LEN_ObjID_VCDU_BIT + LEN_VCID_VCDU_BIT + LEN_FRAME_COUNTER_VCDU_BIT + LEN_REPETITION_FLAG_VSDU_BIT + LEN_RESERVE_VCDU_BIT);
const uint8_t LEN_HEADER_VCDU_BYTE = (LEN_HEADER_VCDU_BIT/LEN_BYTE_IN_BIT);

class ParentCCSDS
{
public:	
	virtual std::vector<uint8_t> getPayload() {return std::vector<uint8_t>();}
	virtual size_t getCountUsedByte() { return 0;}
	virtual uint32_t getToUlongVersion() { return 0;}
	virtual uint32_t getToUlongType() { return 0;}
	virtual uint32_t getToUlongHelpersHeaderFlag() { return 0;}
	virtual uint32_t getToUlongAPID() { return 0;}
	virtual uint32_t getToUlongFragmentationFlag() { return 0;}
	virtual uint32_t getToUlongFrameCounter() { return 0;}
	virtual uint32_t getToUlongSize() { return 0;}
	virtual std::bitset<64> getToBitsetTime() { return std::bitset<64>(0);}
};

template <class TypeCCSDS>
class CCSDS: public ParentCCSDS
{

public:
	CCSDS(TypeCCSDS&, size_t, size_t);
	
	
public:
	TypeCCSDS getPayload() override;
	size_t getCountUsedByte() override;
	
	uint32_t getToUlongVersion() override;
	uint32_t getToUlongType() override;
	uint32_t getToUlongHelpersHeaderFlag() override;
	uint32_t getToUlongAPID() override;
	uint32_t getToUlongFragmentationFlag() override;
	uint32_t getToUlongFrameCounter() override;
	uint32_t getToUlongSize() override;
	std::bitset<64> getToBitsetTime();
	
	
private:
	TypeCCSDS payload;
	size_t countUsedByte;
	
	std::bitset<LEN_VERSION_CCSDS_BIT> version;
	std::bitset<LEN_TYPE_CCSDS_BIT> type;
	std::bitset<LEN_HELPER_HEADER_FLAG_CCSDS_BIT> helperHeaderFlag;
	std::bitset<LEN_APID_CCSDS_BIT> APID;
	std::bitset<LEN_FRAGMENTATION_FLAG_CCSDS_BIT> fragmentationFlag;
	std::bitset<LEN_FRAME_COUNTER_CCSDS_BIT> frameCounter;
	std::bitset<LEN_SIZE_CCSDS_BIT> size;
	
	std::bitset<LEN_TIME_CCSDS_BIT> time;  //Ошибка в постановке задачи
};

template class CCSDS<std::vector<uint8_t>>;

#endif

