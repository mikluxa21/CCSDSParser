#include <interface.h>
#include <gtest/gtest.h>
#include "Help/Test_Helpers.h"





TEST(Interface, SomePackage)
{
	std::vector<unsigned char> header = createVCDU(3, 25, 20, 16776, 1, 12, 0, 0);
	
	std::vector<unsigned char> headerCCSDS_1 = createCCSDSHeader(3, 1, 1, 0, 1, 16383, 632);
	std::vector<unsigned char> payloadCCSDS_1 = createCCSDSBody(632);
	headerCCSDS_1.insert(headerCCSDS_1.end(), payloadCCSDS_1.begin(), payloadCCSDS_1.end());
	header.insert(header.end(), headerCCSDS_1.begin(), headerCCSDS_1.end());
	
	std::vector<unsigned char> headerCCSDS_2 = createCCSDSHeader(3, 1, 1, 1, 2, 16383, 632);
	std::vector<unsigned char> payloadCCSDS_2 = createCCSDSBody(632);
	headerCCSDS_2.insert(headerCCSDS_2.end(), payloadCCSDS_2.begin(), payloadCCSDS_2.begin() + 200);
	header.insert(header.end(), headerCCSDS_2.begin(), headerCCSDS_2.end());
	
	Interface<std::vector<unsigned char>> interface;
	interface.addVCDU(header, header.size());
	
	std::vector<unsigned char> header_1 = createVCDU(3, 25, 20, 16777, 1, 12, 0, 432);
	header_1.insert(header_1.end(), payloadCCSDS_2.begin() + 200, payloadCCSDS_2.end());
	
	std::vector<unsigned char> headerCCSDS_11 = createCCSDSHeader(3, 1, 1, 0, 1, 16383, 632);
	std::vector<unsigned char> payloadCCSDS_11 = createCCSDSBody(632);
	headerCCSDS_11.insert(headerCCSDS_11.end(), payloadCCSDS_11.begin(), payloadCCSDS_11.end());
	header_1.insert(header_1.end(), headerCCSDS_11.begin(), headerCCSDS_11.end());
	
	std::vector<unsigned char> headerCCSDS_12 = createCCSDSHeader(3, 1, 1, 1, 2, 16383, 632);
	std::vector<unsigned char> payloadCCSDS_12 = createCCSDSBody(632);
	headerCCSDS_12.insert(headerCCSDS_12.end(), payloadCCSDS_12.begin(), payloadCCSDS_12.end());
	header_1.insert(header_1.end(), headerCCSDS_12.begin(), headerCCSDS_12.end());
	
	interface.addVCDU(header_1, header_1.size());
	payloadCCSDS_1.insert(payloadCCSDS_1.end(), payloadCCSDS_11.begin(), payloadCCSDS_11.end());
	EXPECT_EQ(interface.getCCSDSPackages()[0].size(), payloadCCSDS_1.size());
	payloadCCSDS_2.insert(payloadCCSDS_2.end(), payloadCCSDS_12.begin(), payloadCCSDS_12.end());
	EXPECT_EQ(interface.getCCSDSPackages()[1].size(), payloadCCSDS_2.size());
}




TEST(Interface, SomeVCDUPackge)
{
	std::vector<unsigned char> header = createVCDU(3, 25, 20, 16776, 1, 12, 0, 0);
	
	std::vector<unsigned char> headerCCSDS_1 = createCCSDSHeader(3, 1, 1, 0, 1, 16383, 632);
	std::vector<unsigned char> payloadCCSDS_1 = createCCSDSBody(632);
	headerCCSDS_1.insert(headerCCSDS_1.end(), payloadCCSDS_1.begin(), payloadCCSDS_1.end());
	header.insert(header.end(), headerCCSDS_1.begin(), headerCCSDS_1.end());
	
	std::vector<unsigned char> headerCCSDS_2 = createCCSDSHeader(3, 1, 1, 1, 2, 16383, 632);
	std::vector<unsigned char> payloadCCSDS_2 = createCCSDSBody(632);
	headerCCSDS_2.insert(headerCCSDS_2.end(), payloadCCSDS_2.begin(), payloadCCSDS_2.end());
	header.insert(header.end(), headerCCSDS_2.begin(), headerCCSDS_2.end());
	
	Interface<std::vector<unsigned char>> interface;
	interface.addVCDU(header, header.size());
	
	std::vector<unsigned char> header_1 = createVCDU(3, 25, 20, 16777, 1, 12, 0, 0);
	
	std::vector<unsigned char> headerCCSDS_11 = createCCSDSHeader(3, 1, 1, 0, 1, 16383, 632);
	std::vector<unsigned char> payloadCCSDS_11 = createCCSDSBody(632);
	headerCCSDS_11.insert(headerCCSDS_11.end(), payloadCCSDS_11.begin(), payloadCCSDS_11.end());
	header_1.insert(header_1.end(), headerCCSDS_11.begin(), headerCCSDS_11.end());
	
	std::vector<unsigned char> headerCCSDS_12 = createCCSDSHeader(3, 1, 1, 1, 2, 16383, 632);
	std::vector<unsigned char> payloadCCSDS_12 = createCCSDSBody(632);
	headerCCSDS_12.insert(headerCCSDS_12.end(), payloadCCSDS_12.begin(), payloadCCSDS_12.end());
	header_1.insert(header_1.end(), headerCCSDS_12.begin(), headerCCSDS_12.end());
	
	interface.addVCDU(header_1, header_1.size());
	payloadCCSDS_1.insert(payloadCCSDS_1.end(), payloadCCSDS_11.begin(), payloadCCSDS_11.end());
	EXPECT_EQ(interface.getCCSDSPackages()[0], payloadCCSDS_1);
	payloadCCSDS_2.insert(payloadCCSDS_2.end(), payloadCCSDS_12.begin(), payloadCCSDS_12.end());
	EXPECT_EQ(interface.getCCSDSPackages()[1], payloadCCSDS_2);
}


TEST(Interface, SomeDifAPIDPackage)
{
	std::vector<unsigned char> header = createVCDUHeader(3, 25, 20, 16777, 1, 12);
	std::vector<unsigned char> headerMDPU = createMDPUHeader(0, 0);
	header.insert(header.end(), headerMDPU.begin(), headerMDPU.end());
	
	std::vector<unsigned char> headerCCSDS = createCCSDSHeader(3, 1, 1, 0, 1, 16383, 657);
	std::vector<unsigned char> payloadCCSDS = createCCSDSBody(657);
	headerCCSDS.insert(headerCCSDS.end(), std::make_move_iterator(payloadCCSDS.begin()), std::make_move_iterator(payloadCCSDS.end()));
	
	std::vector<unsigned char> resPayloadCCSDS;
	resPayloadCCSDS.insert(resPayloadCCSDS.end(), payloadCCSDS.begin(), payloadCCSDS.end());
	header.insert(header.end(), headerCCSDS.begin(), headerCCSDS.end());
	
	headerCCSDS = createCCSDSHeader(3, 1, 1, 31, 0, 16383, 1000);
	payloadCCSDS = createCCSDSBody(1000);
	headerCCSDS.insert(headerCCSDS.end(), std::make_move_iterator(payloadCCSDS.begin()), std::make_move_iterator(payloadCCSDS.end()));
	header.insert(header.end(), headerCCSDS.begin(), headerCCSDS.end());
	
	headerCCSDS = createCCSDSHeader(3, 1, 1, 63, 2, 16383, 1657);
	//payloadCCSDS = createCCSDSBody(1657);
	headerCCSDS.insert(headerCCSDS.end(), std::make_move_iterator(payloadCCSDS.begin()), std::make_move_iterator(payloadCCSDS.end()));
	
	header.insert(header.end(), headerCCSDS.begin(), headerCCSDS.end());
	
	Interface<std::vector<unsigned char>> interface;
	interface.addVCDU(header, header.size());
	EXPECT_EQ(interface.getCCSDSPackages()[0],  resPayloadCCSDS);
	EXPECT_EQ(interface.getCCSDSPackages()[31],  payloadCCSDS);
}


TEST(Interface, SomeCCSDSPackages)
{
	std::vector<unsigned char> header = createVCDUHeader(3, 25, 10, 16777, 1, 12);
	std::vector<unsigned char> headerMDPU = createMDPUHeader(0, 0);
	header.insert(header.end(), headerMDPU.begin(), headerMDPU.end());
	
	std::vector<unsigned char> headerCCSDS = createCCSDSHeader(3, 1, 1, 0, 1, 16383, 657);
	std::vector<unsigned char> payloadCCSDS = createCCSDSBody(657);
	headerCCSDS.insert(headerCCSDS.end(), std::make_move_iterator(payloadCCSDS.begin()), std::make_move_iterator(payloadCCSDS.end()));
	header.insert(header.end(), headerCCSDS.begin(), headerCCSDS.end());
	
	headerCCSDS = createCCSDSHeader(3, 1, 1, 0, 0, 16383, 657);
	headerCCSDS.insert(headerCCSDS.end(), std::make_move_iterator(payloadCCSDS.begin()), std::make_move_iterator(payloadCCSDS.end()));
	header.insert(header.end(), headerCCSDS.begin(), headerCCSDS.end());
	
	headerCCSDS = createCCSDSHeader(3, 1, 1, 0, 2, 16383, 657);
	headerCCSDS.insert(headerCCSDS.end(), std::make_move_iterator(payloadCCSDS.begin()), std::make_move_iterator(payloadCCSDS.end()));
	
	header.insert(header.end(), headerCCSDS.begin(), headerCCSDS.end());
	
	std::vector<unsigned char> resPayloadCCSDS;
	for(size_t i = 0; i < 3; i++)
		resPayloadCCSDS.insert(resPayloadCCSDS.begin(), payloadCCSDS.begin(), payloadCCSDS.end());
	Interface<std::vector<unsigned char>> interface;
	interface.addVCDU(header, header.size());
	EXPECT_EQ(interface.getCCSDSPackages()[0],  resPayloadCCSDS);
}



TEST(Interface, OnePackageCCSDSThrow)
{
	std::vector<unsigned char> header = createVCDUHeader(3, 25, 20, 16777, 1, 12);
	std::vector<unsigned char> headerMDPU = createMDPUHeader(0, 0);
	header.insert(header.end(), headerMDPU.begin(), headerMDPU.end());
	
	std::vector<unsigned char> headerCCSDS = createCCSDSHeader(3, 1, 1, 0, 3, 16383, 657);
	std::vector<unsigned char> payloadCCSDS = createCCSDSBody(657);
	headerCCSDS.insert(headerCCSDS.end(), std::make_move_iterator(payloadCCSDS.begin()), std::make_move_iterator(payloadCCSDS.end()));
	
	header.insert(header.end(), headerCCSDS.begin(), headerCCSDS.end());
	Interface<std::vector<unsigned char>> interface;
	interface.addVCDU(header, header.size());
	EXPECT_EQ(interface.getCCSDSPackages()[0],  payloadCCSDS);
	
}

TEST(Interface, FrameCounterThrow)
{
	std::vector<unsigned char> header = createVCDUHeader(3, 25, 20, 16777, 1, 12);
	std::vector<unsigned char> headerMDPU = createMDPUHeader(0, 0);
	header.insert(header.end(), headerMDPU.begin(), headerMDPU.end());
	
	std::vector<unsigned char> headerCCSDS = createCCSDSHeader(3, 1, 1, 2047, 3, 16383, 657);
	std::vector<unsigned char> payloadCCSDS = createCCSDSBody(657);
	headerCCSDS.insert(headerCCSDS.end(), std::make_move_iterator(payloadCCSDS.begin()), std::make_move_iterator(payloadCCSDS.end()));
	
	header.insert(header.end(), headerCCSDS.begin(), headerCCSDS.end());
	
	Interface<std::vector<unsigned char>> interface;
	interface.addVCDU(header, header.size());
	EXPECT_THROW(interface.addVCDU(header, header.size()), std::runtime_error);
}


TEST(Interface, FirstMDPUOffsetThrow)
{
	Interface<std::vector<unsigned char>> interface;
	std::vector<unsigned char> header = createVCDUHeader(3, 25, 63, 16777, 2, 12);
	std::vector<unsigned char> headerMDPU = createMDPUHeader(0, 10);
	header.insert(header.end(), headerMDPU.begin(), headerMDPU.end());
	EXPECT_THROW(interface.addVCDU(header, header.size()), std::runtime_error);
}


TEST(Interface, EmptyThrow)
{
	Interface<std::vector<unsigned char>> interface;
	EXPECT_THROW(interface.getCCSDSPackages(), std::runtime_error);
}


TEST(VCDU, OffsetVCDU)
{
	std::vector<unsigned char> header = createVCDUHeader(3, 25, 63, 16777, 1, 12);
	std::vector<unsigned char> offset = createCCSDSBody(243);
	std::vector<unsigned char> headerMDPU = createMDPUHeader(0, offset.size());
	header.insert(header.end(), headerMDPU.begin(), headerMDPU.end());
	
	header.insert(header.end(), std::make_move_iterator(offset.begin()), std::make_move_iterator(offset.end()));
	
	std::vector<unsigned char> headerCCSDS = createCCSDSHeader(3, 1, 1, 2047, 3, 16383, 657);
	std::vector<unsigned char> payloadCCSDS = createCCSDSBody(657);
	headerCCSDS.insert(headerCCSDS.end(), std::make_move_iterator(payloadCCSDS.begin()), std::make_move_iterator(payloadCCSDS.end()));
	
	header.insert(header.end(), headerCCSDS.begin(), headerCCSDS.end());
	
	VCDU<std::vector<unsigned char>>* vcdu = new VCDU<std::vector<unsigned char>>(header, header.size());
	
	EXPECT_EQ(vcdu->getToUlongVersion(), 3);
	EXPECT_EQ(vcdu->getToUlongObjID(), 25);
	EXPECT_EQ(vcdu->getToUlongVCID(), 63);
	EXPECT_EQ(vcdu->getToUlongFrameCounter(), 16777);
	EXPECT_EQ(vcdu->getToUlongRepetitionFlag(), 1);
	EXPECT_EQ(vcdu->getToUlongReserve(), 12);
	EXPECT_EQ(vcdu->getToUlongReservedBitMDPU(), 0);
	EXPECT_EQ(vcdu->getToUlongOffsetBitMDPU(), offset.size());
	EXPECT_EQ(vcdu->getLastCCSDSPacksge(), offset);
	
	EXPECT_EQ(vcdu->getCCSDSVector()[0]->getPayload(), payloadCCSDS);
	EXPECT_EQ(vcdu->getCCSDSVector()[0]->getCountUsedByte(), headerCCSDS.size());
	EXPECT_EQ(vcdu->getCCSDSVector()[0]->getToUlongVersion(), 3);
	EXPECT_EQ(vcdu->getCCSDSVector()[0]->getToUlongType(), 1);
	EXPECT_EQ(vcdu->getCCSDSVector()[0]->getToUlongHelpersHeaderFlag(), 1);
	EXPECT_EQ(vcdu->getCCSDSVector()[0]->getToUlongAPID(), 2047);
	EXPECT_EQ(vcdu->getCCSDSVector()[0]->getToUlongFragmentationFlag(), 3);
	EXPECT_EQ(vcdu->getCCSDSVector()[0]->getToUlongFrameCounter(), 16383);
	EXPECT_EQ(vcdu->getCCSDSVector()[0]->getToUlongSize(), 657);
	EXPECT_TRUE(vcdu->getCCSDSVector()[0]->getToBitsetTime().all());
	delete vcdu;
}



TEST(VCDU, OneFrameCCSDS)
{
	std::vector<unsigned char> header = createVCDUHeader(3, 25, 63, 16777, 1, 12);
	std::vector<unsigned char> headerMDPU = createMDPUHeader(0, 0);
	header.insert(header.end(), headerMDPU.begin(), headerMDPU.end());
	
	std::vector<unsigned char> headerCCSDS = createCCSDSHeader(3, 1, 1, 2047, 3, 16383, 657);
	std::vector<unsigned char> payloadCCSDS = createCCSDSBody(657);
	headerCCSDS.insert(headerCCSDS.end(), std::make_move_iterator(payloadCCSDS.begin()), std::make_move_iterator(payloadCCSDS.end()));
	
	header.insert(header.end(), headerCCSDS.begin(), headerCCSDS.end());
	
	VCDU<std::vector<unsigned char>>* vcdu = new VCDU<std::vector<unsigned char>>(header, header.size());
	
	EXPECT_EQ(vcdu->getToUlongVersion(), 3);
	EXPECT_EQ(vcdu->getToUlongObjID(), 25);
	EXPECT_EQ(vcdu->getToUlongVCID(), 63);
	EXPECT_EQ(vcdu->getToUlongFrameCounter(), 16777);
	EXPECT_EQ(vcdu->getToUlongRepetitionFlag(), 1);
	EXPECT_EQ(vcdu->getToUlongReserve(), 12);
	EXPECT_EQ(vcdu->getToUlongReservedBitMDPU(), 0);
	EXPECT_EQ(vcdu->getToUlongOffsetBitMDPU(), 0);
	
	EXPECT_EQ(vcdu->getCCSDSVector()[0]->getPayload(), payloadCCSDS);
	EXPECT_EQ(vcdu->getCCSDSVector()[0]->getCountUsedByte(), headerCCSDS.size());
	EXPECT_EQ(vcdu->getCCSDSVector()[0]->getToUlongVersion(), 3);
	EXPECT_EQ(vcdu->getCCSDSVector()[0]->getToUlongType(), 1);
	EXPECT_EQ(vcdu->getCCSDSVector()[0]->getToUlongHelpersHeaderFlag(), 1);
	EXPECT_EQ(vcdu->getCCSDSVector()[0]->getToUlongAPID(), 2047);
	EXPECT_EQ(vcdu->getCCSDSVector()[0]->getToUlongFragmentationFlag(), 3);
	EXPECT_EQ(vcdu->getCCSDSVector()[0]->getToUlongFrameCounter(), 16383);
	EXPECT_EQ(vcdu->getCCSDSVector()[0]->getToUlongSize(), 657);
	EXPECT_TRUE(vcdu->getCCSDSVector()[0]->getToBitsetTime().all());
	delete vcdu;
}

TEST(VCDU, SomeFrameCCSDS)
{
	std::vector<unsigned char> header = createVCDUHeader(3, 25, 63, 16777, 1, 12);
	std::vector<unsigned char> headerMDPU = createMDPUHeader(0, 0);
	header.insert(header.end(), headerMDPU.begin(), headerMDPU.end());
	
	std::vector<unsigned char> headerCCSDS = createCCSDSHeader(3, 1, 1, 2047, 1, 16383, 657);
	std::vector<unsigned char> payloadCCSDS = createCCSDSBody(657);
	headerCCSDS.insert(headerCCSDS.end(), std::make_move_iterator(payloadCCSDS.begin()), std::make_move_iterator(payloadCCSDS.end()));
	header.insert(header.end(), headerCCSDS.begin(), headerCCSDS.end());
	
	headerCCSDS = createCCSDSHeader(3, 1, 1, 2047, 0, 16383, 657);
	//payloadCCSDS = createCCSDSBody(657);
	headerCCSDS.insert(headerCCSDS.end(), std::make_move_iterator(payloadCCSDS.begin()), std::make_move_iterator(payloadCCSDS.end()));
	header.insert(header.end(), headerCCSDS.begin(), headerCCSDS.end());
	
	headerCCSDS = createCCSDSHeader(3, 1, 1, 2047, 2, 16383, 657);
	//payloadCCSDS = createCCSDSBody(657);
	headerCCSDS.insert(headerCCSDS.end(), std::make_move_iterator(payloadCCSDS.begin()), std::make_move_iterator(payloadCCSDS.end()));
	
	header.insert(header.end(), headerCCSDS.begin(), headerCCSDS.end());
	
	VCDU<std::vector<unsigned char>>* vcdu = new VCDU<std::vector<unsigned char>>(header, header.size());
	
	EXPECT_EQ(vcdu->getToUlongVersion(), 3);
	EXPECT_EQ(vcdu->getToUlongObjID(), 25);
	EXPECT_EQ(vcdu->getToUlongVCID(), 63);
	EXPECT_EQ(vcdu->getToUlongFrameCounter(), 16777);
	EXPECT_EQ(vcdu->getToUlongRepetitionFlag(), 1);
	EXPECT_EQ(vcdu->getToUlongReserve(), 12);
	EXPECT_EQ(vcdu->getToUlongReservedBitMDPU(), 0);
	EXPECT_EQ(vcdu->getToUlongOffsetBitMDPU(), 0);
	
	EXPECT_EQ(vcdu->getCCSDSVector()[0]->getPayload(), payloadCCSDS);
	EXPECT_EQ(vcdu->getCCSDSVector()[0]->getCountUsedByte(), headerCCSDS.size());
	EXPECT_EQ(vcdu->getCCSDSVector()[0]->getToUlongVersion(), 3);
	EXPECT_EQ(vcdu->getCCSDSVector()[0]->getToUlongType(), 1);
	EXPECT_EQ(vcdu->getCCSDSVector()[0]->getToUlongHelpersHeaderFlag(), 1);
	EXPECT_EQ(vcdu->getCCSDSVector()[0]->getToUlongAPID(), 2047);
	EXPECT_EQ(vcdu->getCCSDSVector()[0]->getToUlongFragmentationFlag(), 1);
	EXPECT_EQ(vcdu->getCCSDSVector()[0]->getToUlongFrameCounter(), 16383);
	EXPECT_EQ(vcdu->getCCSDSVector()[0]->getToUlongSize(), 657);
	EXPECT_TRUE(vcdu->getCCSDSVector()[0]->getToBitsetTime().all());
	
	EXPECT_EQ(vcdu->getCCSDSVector()[1]->getPayload(), payloadCCSDS);
	EXPECT_EQ(vcdu->getCCSDSVector()[1]->getCountUsedByte(), headerCCSDS.size());
	EXPECT_EQ(vcdu->getCCSDSVector()[1]->getToUlongVersion(), 3);
	EXPECT_EQ(vcdu->getCCSDSVector()[1]->getToUlongType(), 1);
	EXPECT_EQ(vcdu->getCCSDSVector()[1]->getToUlongHelpersHeaderFlag(), 1);
	EXPECT_EQ(vcdu->getCCSDSVector()[1]->getToUlongAPID(), 2047);
	EXPECT_EQ(vcdu->getCCSDSVector()[1]->getToUlongFragmentationFlag(), 0);
	EXPECT_EQ(vcdu->getCCSDSVector()[1]->getToUlongFrameCounter(), 16383);
	EXPECT_EQ(vcdu->getCCSDSVector()[1]->getToUlongSize(), 657);
	EXPECT_TRUE(vcdu->getCCSDSVector()[1]->getToBitsetTime().all());
	
	EXPECT_EQ(vcdu->getCCSDSVector()[2]->getPayload(), payloadCCSDS);
	EXPECT_EQ(vcdu->getCCSDSVector()[2]->getCountUsedByte(), headerCCSDS.size());
	EXPECT_EQ(vcdu->getCCSDSVector()[2]->getToUlongVersion(), 3);
	EXPECT_EQ(vcdu->getCCSDSVector()[2]->getToUlongType(), 1);
	EXPECT_EQ(vcdu->getCCSDSVector()[2]->getToUlongHelpersHeaderFlag(), 1);
	EXPECT_EQ(vcdu->getCCSDSVector()[2]->getToUlongAPID(), 2047);
	EXPECT_EQ(vcdu->getCCSDSVector()[2]->getToUlongFragmentationFlag(), 2);
	EXPECT_EQ(vcdu->getCCSDSVector()[2]->getToUlongFrameCounter(), 16383);
	EXPECT_EQ(vcdu->getCCSDSVector()[2]->getToUlongSize(), 657);
	EXPECT_TRUE(vcdu->getCCSDSVector()[2]->getToBitsetTime().all());
	
	delete vcdu;
}


TEST(VCDU, CorreptedLastFrameCCSDS)
{
	std::vector<unsigned char> header = createVCDUHeader(3, 25, 63, 16777, 1, 12);
	std::vector<unsigned char> headerMDPU = createMDPUHeader(0, 0);
	header.insert(header.end(), headerMDPU.begin(), headerMDPU.end());
	
	std::vector<unsigned char> headerCCSDS = createCCSDSHeader(3, 1, 1, 2047, 1, 16383, 657);
	std::vector<unsigned char> payloadCCSDS = createCCSDSBody(657);
	headerCCSDS.insert(headerCCSDS.end(), std::make_move_iterator(payloadCCSDS.begin()), std::make_move_iterator(payloadCCSDS.end()));
	header.insert(header.end(), headerCCSDS.begin(), headerCCSDS.end());
	
	headerCCSDS = createCCSDSHeader(3, 1, 1, 2047, 0, 16383, 657);
	//payloadCCSDS = createCCSDSBody(657);
	headerCCSDS.insert(headerCCSDS.end(), std::make_move_iterator(payloadCCSDS.begin()), std::make_move_iterator(payloadCCSDS.end()));
	header.insert(header.end(), headerCCSDS.begin(), headerCCSDS.end());
	
	std::vector<unsigned char> header_ = createCCSDSHeader(3, 1, 1, 2047, 2, 16383, 657);
	std::vector<unsigned char> payload_ = createCCSDSBody(657);
		std::vector<unsigned char> payloadSome;
	for(size_t i = 0; i < payload_.size() - 100; i++)
		payloadSome.push_back(payload_[i]);
	header_.insert(header_.end(), std::make_move_iterator(payloadSome.begin()), std::make_move_iterator(payloadSome.end()));
	
	header.insert(header.end(), std::make_move_iterator(header_.begin()), std::make_move_iterator(header_.end()));
	
	VCDU<std::vector<unsigned char>>* vcdu = new VCDU<std::vector<unsigned char>>(header, header.size());
	
	EXPECT_EQ(vcdu->getToUlongVersion(), 3);
	EXPECT_EQ(vcdu->getToUlongObjID(), 25);
	EXPECT_EQ(vcdu->getToUlongVCID(), 63);
	EXPECT_EQ(vcdu->getToUlongFrameCounter(), 16777);
	EXPECT_EQ(vcdu->getToUlongRepetitionFlag(), 1);
	EXPECT_EQ(vcdu->getToUlongReserve(), 12);
	EXPECT_EQ(vcdu->getToUlongReservedBitMDPU(), 0);
	EXPECT_EQ(vcdu->getToUlongOffsetBitMDPU(), 0);
	
	EXPECT_EQ(vcdu->getCCSDSVector()[0]->getPayload(), payloadCCSDS);
	EXPECT_EQ(vcdu->getCCSDSVector()[0]->getCountUsedByte(), headerCCSDS.size());
	EXPECT_EQ(vcdu->getCCSDSVector()[0]->getToUlongVersion(), 3);
	EXPECT_EQ(vcdu->getCCSDSVector()[0]->getToUlongType(), 1);
	EXPECT_EQ(vcdu->getCCSDSVector()[0]->getToUlongHelpersHeaderFlag(), 1);
	EXPECT_EQ(vcdu->getCCSDSVector()[0]->getToUlongAPID(), 2047);
	EXPECT_EQ(vcdu->getCCSDSVector()[0]->getToUlongFragmentationFlag(), 1);
	EXPECT_EQ(vcdu->getCCSDSVector()[0]->getToUlongFrameCounter(), 16383);
	EXPECT_EQ(vcdu->getCCSDSVector()[0]->getToUlongSize(), 657);
	EXPECT_TRUE(vcdu->getCCSDSVector()[0]->getToBitsetTime().all());
	
	EXPECT_EQ(vcdu->getCCSDSVector()[1]->getPayload(), payloadCCSDS);
	EXPECT_EQ(vcdu->getCCSDSVector()[1]->getCountUsedByte(), headerCCSDS.size());
	EXPECT_EQ(vcdu->getCCSDSVector()[1]->getToUlongVersion(), 3);
	EXPECT_EQ(vcdu->getCCSDSVector()[1]->getToUlongType(), 1);
	EXPECT_EQ(vcdu->getCCSDSVector()[1]->getToUlongHelpersHeaderFlag(), 1);
	EXPECT_EQ(vcdu->getCCSDSVector()[1]->getToUlongAPID(), 2047);
	EXPECT_EQ(vcdu->getCCSDSVector()[1]->getToUlongFragmentationFlag(), 0);
	EXPECT_EQ(vcdu->getCCSDSVector()[1]->getToUlongFrameCounter(), 16383);
	EXPECT_EQ(vcdu->getCCSDSVector()[1]->getToUlongSize(), 657);
	EXPECT_TRUE(vcdu->getCCSDSVector()[1]->getToBitsetTime().all());
	
	
	EXPECT_EQ(vcdu->getCCSDSVector()[2]->getPayload(), payloadSome);
	EXPECT_EQ(vcdu->getCCSDSVector()[2]->getCountUsedByte(), header_.size());
	EXPECT_EQ(vcdu->getCCSDSVector()[2]->getToUlongVersion(), 3);
	EXPECT_EQ(vcdu->getCCSDSVector()[2]->getToUlongType(), 1);
	EXPECT_EQ(vcdu->getCCSDSVector()[2]->getToUlongHelpersHeaderFlag(), 1);
	EXPECT_EQ(vcdu->getCCSDSVector()[2]->getToUlongAPID(), 2047);
	EXPECT_EQ(vcdu->getCCSDSVector()[2]->getToUlongFragmentationFlag(), 2);
	EXPECT_EQ(vcdu->getCCSDSVector()[2]->getToUlongFrameCounter(), 16383);
	EXPECT_EQ(vcdu->getCCSDSVector()[2]->getToUlongSize(), 657);
	EXPECT_TRUE(vcdu->getCCSDSVector()[2]->getToBitsetTime().all());
	
	delete vcdu;
}

TEST(VCDU, ShortLen)
{
	std::vector<unsigned char> header = createVCDUHeader(3, 255, 63, 16777215, 1, 127);
	EXPECT_THROW(VCDU<std::vector<unsigned char>>(header, 7), std::invalid_argument);
	
}

TEST(CCSDS, OneFrame)
{
	std::vector<unsigned char> header = createCCSDSHeader(3, 1, 1, 2047, 3, 16383, 657);
	std::vector<unsigned char> payload = createCCSDSBody(657);
	header.insert(header.end(), std::make_move_iterator(payload.begin()), std::make_move_iterator(payload.end()));
	CCSDS<std::vector<unsigned char>> ccsds(header, header.size(), 0);
	
	EXPECT_EQ(ccsds.getPayload(), payload);
	EXPECT_EQ(ccsds.getCountUsedByte(), header.size());
	EXPECT_EQ(ccsds.getToUlongVersion(), 3);
	EXPECT_EQ(ccsds.getToUlongType(), 1);
	EXPECT_EQ(ccsds.getToUlongHelpersHeaderFlag(), 1);
	EXPECT_EQ(ccsds.getToUlongAPID(), 2047);
	EXPECT_EQ(ccsds.getToUlongFragmentationFlag(), 3);
	EXPECT_EQ(ccsds.getToUlongFrameCounter(), 16383);
	EXPECT_EQ(ccsds.getToUlongSize(), 657);
	EXPECT_TRUE(ccsds.getToBitsetTime().all());
}

TEST(CCSDS, ShortLenThrow)
{
	std::vector<unsigned char> header = createCCSDSHeader(3, 1, 1, 2047, 3, 16383, 657);
	EXPECT_THROW(CCSDS<std::vector<unsigned char>>(header, 7, 0), std::invalid_argument);
}

TEST(CCSDS, FirstFrame)
{
	std::vector<unsigned char> header = createCCSDSHeader(3, 1, 1, 2047, 1, 16383, 657);
	std::vector<unsigned char> payload = createCCSDSBody(657);
	header.insert(header.end(), std::make_move_iterator(payload.begin()), std::make_move_iterator(payload.end()));
	
	std::vector<unsigned char> header_ = createCCSDSHeader(3, 1, 1, 2047, 2, 16383, 657);
	std::vector<unsigned char> payload_ = createCCSDSBody(657);
	header_.insert(header_.end(), std::make_move_iterator(payload_.begin()), std::make_move_iterator(payload_.end()));
	
	header.insert(header.end(), std::make_move_iterator(header_.begin()), std::make_move_iterator(header_.end()));
	CCSDS<std::vector<unsigned char>> ccsds(header, header.size(), 0);
	
	
	EXPECT_EQ(ccsds.getPayload(), payload);
	EXPECT_EQ(ccsds.getCountUsedByte(), header.size()/2);
	EXPECT_EQ(ccsds.getToUlongVersion(), 3);
	EXPECT_EQ(ccsds.getToUlongType(), 1);
	EXPECT_EQ(ccsds.getToUlongHelpersHeaderFlag(), 1);
	EXPECT_EQ(ccsds.getToUlongAPID(), 2047);
	EXPECT_EQ(ccsds.getToUlongFragmentationFlag(), 1);
	EXPECT_EQ(ccsds.getToUlongFrameCounter(), 16383);
	EXPECT_EQ(ccsds.getToUlongSize(), 657);
	EXPECT_TRUE(ccsds.getToBitsetTime().all());
	
}

TEST(CCSDS, FullLastFrame)
{
	std::vector<unsigned char> header = createCCSDSHeader(3, 1, 1, 2047, 1, 16383, 657);
	std::vector<unsigned char> payload = createCCSDSBody(657);
	header.insert(header.end(), std::make_move_iterator(payload.begin()), std::make_move_iterator(payload.end()));
	
	std::vector<unsigned char> header_ = createCCSDSHeader(3, 1, 1, 2047, 2, 16383, 657);
	std::vector<unsigned char> payload_ = createCCSDSBody(657);
	header_.insert(header_.end(), std::make_move_iterator(payload_.begin()), std::make_move_iterator(payload_.end()));
	
	header.insert(header.end(), std::make_move_iterator(header_.begin()), std::make_move_iterator(header_.end()));
	CCSDS<std::vector<unsigned char>> ccsds(header, header.size(), (header_.size()));
	
	
	
	EXPECT_EQ(ccsds.getPayload(), payload_);
	EXPECT_EQ(ccsds.getCountUsedByte(), header.size()/2);
	EXPECT_EQ(ccsds.getToUlongVersion(), 3);
	EXPECT_EQ(ccsds.getToUlongType(), 1);
	EXPECT_EQ(ccsds.getToUlongHelpersHeaderFlag(), 1);
	EXPECT_EQ(ccsds.getToUlongAPID(), 2047);
	EXPECT_EQ(ccsds.getToUlongFragmentationFlag(), 2);
	EXPECT_EQ(ccsds.getToUlongFrameCounter(), 16383);
	EXPECT_EQ(ccsds.getToUlongSize(), 657);
	EXPECT_TRUE(ccsds.getToBitsetTime().all());
	
}

TEST(CCSDS, SomeLastFrame)
{
	std::vector<unsigned char> header = createCCSDSHeader(3, 1, 1, 2047, 1, 16383, 657);
	std::vector<unsigned char> payload = createCCSDSBody(657);
	header.insert(header.end(), std::make_move_iterator(payload.begin()), std::make_move_iterator(payload.end()));
	size_t t = header.size();
	
	std::vector<unsigned char> header_ = createCCSDSHeader(3, 1, 1, 2047, 2, 16383, 657);
	std::vector<unsigned char> payload_ = createCCSDSBody(657);
		std::vector<unsigned char> payloadSome;
	for(size_t i = 0; i < payload_.size() - 100; i++)
		payloadSome.push_back(payload_[i]);
	header_.insert(header_.end(), std::make_move_iterator(payloadSome.begin()), std::make_move_iterator(payloadSome.end()));
	
	header.insert(header.end(), std::make_move_iterator(header_.begin()), std::make_move_iterator(header_.end()));
	CCSDS<std::vector<unsigned char>> ccsds(header, header.size(), t);
	
	EXPECT_EQ(ccsds.getPayload(), payloadSome);
	EXPECT_EQ(ccsds.getCountUsedByte(), header_.size());
	EXPECT_EQ(ccsds.getToUlongVersion(), 3);
	EXPECT_EQ(ccsds.getToUlongType(), 1);
	EXPECT_EQ(ccsds.getToUlongHelpersHeaderFlag(), 1);
	EXPECT_EQ(ccsds.getToUlongAPID(), 2047);
	EXPECT_EQ(ccsds.getToUlongFragmentationFlag(), 2);
	EXPECT_EQ(ccsds.getToUlongFrameCounter(), 16383);
	EXPECT_EQ(ccsds.getToUlongSize(), 657);
	EXPECT_TRUE(ccsds.getToBitsetTime().all());
	
}

TEST(CCSDS, MidleFrame)
{
	std::vector<unsigned char> header = createCCSDSHeader(3, 1, 1, 2047, 1, 16383, 657);
	std::vector<unsigned char> payload = createCCSDSBody(657);
	header.insert(header.end(), std::make_move_iterator(payload.begin()), std::make_move_iterator(payload.end()));
	
	std::vector<unsigned char> header_ = createCCSDSHeader(3, 1, 1, 2047, 0, 16383, 657);
	std::vector<unsigned char> payload_ = createCCSDSBody(657);
	header_.insert(header_.end(), std::make_move_iterator(payload_.begin()), std::make_move_iterator(payload_.end()));
	
	header.insert(header.end(), std::make_move_iterator(header_.begin()), std::make_move_iterator(header_.end()));
	header.insert(header.end(), std::make_move_iterator(header_.begin()), std::make_move_iterator(header_.end()));
	CCSDS<std::vector<unsigned char>> ccsds(header, header.size(), (header_.size()));
	
	
	
	EXPECT_EQ(ccsds.getPayload(), payload_);
	EXPECT_EQ(ccsds.getCountUsedByte(), header.size()/3);
	
	EXPECT_EQ(ccsds.getToUlongVersion(), 3);
	EXPECT_EQ(ccsds.getToUlongType(), 1);
	EXPECT_EQ(ccsds.getToUlongHelpersHeaderFlag(), 1);
	EXPECT_EQ(ccsds.getToUlongAPID(), 2047);
	EXPECT_EQ(ccsds.getToUlongFragmentationFlag(), 0);
	EXPECT_EQ(ccsds.getToUlongFrameCounter(), 16383);
	EXPECT_EQ(ccsds.getToUlongSize(), 657);
	EXPECT_TRUE(ccsds.getToBitsetTime().all());
	
}



TEST(Test_Helpers, CreateVCDUHeader_1)
{
	for(auto i: createVCDUHeader(3, 255, 63, 16777215, 1, 127))
		EXPECT_EQ((int) i, 255);
}

TEST(Test_Helpers, CreateVCDUHeader_2)
{
	std::vector<unsigned char> vec = createVCDUHeader(1, 255, 60, 4160459, 1, 126);
	EXPECT_EQ((int) vec[0], 127);
	EXPECT_EQ((int) vec[1], 252);
	EXPECT_EQ((int) vec[2], 63);
	EXPECT_EQ((int) vec[3], 123);
	EXPECT_EQ((int) vec[4], 203);
	EXPECT_EQ((int) vec[5], 254);
	
}

TEST(Test_Helpers, CreateCCSDSHeader_1)
{
	for(auto i: createCCSDSHeader(7, 1, 1, 2047, 3, 16383, 65535))
		EXPECT_EQ((int) i, 255);
}

TEST(Test_Helpers, CreateCCSDSHeader_2)
{
	std::vector<unsigned char> vec = createCCSDSHeader(0, 1, 1, 2044, 0, 16380, 65534);
	EXPECT_EQ((int) vec[0], 31);
	EXPECT_EQ((int) vec[1], 252);
	EXPECT_EQ((int) vec[2], 63);
	EXPECT_EQ((int) vec[3], 252);
	EXPECT_EQ((int) vec[4], 255);
	EXPECT_EQ((int) vec[5], 254);
	
}


TEST(Test_Helpers, createCCSDSBody)
{
	size_t size = 123456;
	EXPECT_EQ(createCCSDSBody(size).size(), size);
}
