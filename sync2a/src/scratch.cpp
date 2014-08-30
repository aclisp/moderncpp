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
#include "User.h"
#include <vector>
#include <string>


using namespace clx;
using namespace std;


int main(int argc, char **argv)
{
#if 0
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
#endif

#if 0
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
#endif

#if 1
	Processor processor(200);
	UserGenerator userGenerator(5.0);

	for (int i=0; i<500; ++i) {
		userGenerator.newUser(processor);
	}

	//this_thread::sleep_for(chrono::seconds(5));
	processor.dispatcher().dumpDispTable();

	return 0;
#endif
}
