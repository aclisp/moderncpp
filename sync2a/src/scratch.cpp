//============================================================================
// Name        : scratch.cpp
// Author      : Homer Huang
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include "gtest/gtest.h"
#include "Processor.h"
#include "Packet.h"


using namespace clx;
using namespace std;


int main(int argc, char **argv)
{
	//::testing::InitGoogleTest(&argc, argv);
	//return RUN_ALL_TESTS();

	vector<Packet> packets;
	const int MAX = 260;
	for (int i=0; i<MAX; ++i) {
		packets.emplace_back(i, i);
	}

	Processor processor;
	for (const Packet& packet : packets) {
		processor.sendInput(packet);
	}

	return 0;
}
