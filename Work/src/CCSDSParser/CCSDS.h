#ifndef CCSDS_H
#define CCSDS_H
#include <bitset>
#include <string>
#include <vector>
#include <iterator>

#define LEN_BYTE_IN_BIT  8

//Lenghts optional frames CCSDS header
#define LEN_VERSION_CCSDS_BIT  3
#define LEN_TYPE_CCSDS_BIT  1
#define LEN_HELPER_HEADER_FLAG_CCSDS_BIT 1
#define LEN_APID_CCSDS_BIT  11
#define LEN_FRAGMENTATION_FLAG_CCSDS_BIT  2
#define LEN_FRAME_COUNTER_CCSDS_BIT  14
#define LEN_SIZE_CCSDS_BIT  16
#define LEN_TIME_CCSDS_BIT  64
#define LEN_HEADER_CCSDS_BIT  (LEN_VERSION_CCSDS_BIT + LEN_TYPE_CCSDS_BIT + LEN_HELPER_HEADER_FLAG_CCSDS_BIT + LEN_APID_CCSDS_BIT + LEN_FRAGMENTATION_FLAG_CCSDS_BIT + LEN_FRAME_COUNTER_CCSDS_BIT + LEN_SIZE_CCSDS_BIT + LEN_TIME_CCSDS_BIT)
#define LEN_HEADER_CCSDS_BYTE  (LEN_HEADER_CCSDS_BIT/LEN_BYTE_IN_BIT)


//Lenghts optional frames MDPU header
#define LEN_RESERVE_MDPU_BIT  5
#define LEN_OFFSET_MDPU_BIT  11
#define LEN_HEADER_MDPU_BIT  (LEN_RESERVE_MDPU_BIT + LEN_OFFSET_MDPU_BIT)
#define LEN_HEADER_MDPU_BYTE  (LEN_HEADER_MDPU_BIT/LEN_BYTE_IN_BIT)

//Lenghts optional frames VCDU header	
#define LEN_VERSION_VCDU_BIT  2
#define LEN_ObjID_VCDU_BIT  8
#define LEN_VCID_VCDU_BIT  6
#define LEN_FRAME_COUNTER_VCDU_BIT  24
#define LEN_REPETITION_FLAG_VSDU_BIT  1
#define LEN_RESERVE_VCDU_BIT  7
#define LEN_HEADER_VCDU_BIT  (LEN_VERSION_VCDU_BIT + LEN_ObjID_VCDU_BIT + LEN_VCID_VCDU_BIT + LEN_FRAME_COUNTER_VCDU_BIT + LEN_REPETITION_FLAG_VSDU_BIT + LEN_RESERVE_VCDU_BIT)
#define LEN_HEADER_VCDU_BYTE  (LEN_HEADER_VCDU_BIT/LEN_BYTE_IN_BIT)

class ParentCCSDS
{
public:	
	virtual std::vector<unsigned char> getPayload() {return std::vector<unsigned char>();}
	virtual size_t getCountUsedByte() { return 0;}
	virtual unsigned int getToUlongVersion() { return 0;}
	virtual unsigned int getToUlongType() { return 0;}
	virtual unsigned int getToUlongHelpersHeaderFlag() { return 0;}
	virtual unsigned int getToUlongAPID() { return 0;}
	virtual unsigned int getToUlongFragmentationFlag() { return 0;}
	virtual unsigned int getToUlongFrameCounter() { return 0;}
	virtual unsigned int getToUlongSize() { return 0;}
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
	
	unsigned int getToUlongVersion() override;
	unsigned int getToUlongType() override;
	unsigned int getToUlongHelpersHeaderFlag() override;
	unsigned int getToUlongAPID() override;
	unsigned int getToUlongFragmentationFlag() override;
	unsigned int getToUlongFrameCounter() override;
	unsigned int getToUlongSize() override;
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

template class CCSDS<std::vector<unsigned char>>;

#endif

