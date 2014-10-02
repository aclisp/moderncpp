/*
 * Channel_test.cpp
 *
 *  Created on: Aug 20, 2014
 *      Author: homer
 */

#include "Channel.h"
#include "gtest/gtest.h"
#include <thread>
#include <chrono>
#include <vector>


using namespace clx;
using namespace std;


TEST(ChannelTest, Basic) {
	Channel<int> ch;
	ch.write(0);
	ch.write(1);
	EXPECT_EQ(0, ch.read());
	EXPECT_EQ(1, ch.read());
	ch.write(5);
	ch.write(9);
	ch.write(17);
	EXPECT_EQ(5, ch.read());
	EXPECT_EQ(9, ch.read());
	EXPECT_EQ(17, ch.read());
}


TEST(ChannelTest, Thread) {
	Channel<int> ch;
	vector<int> v;
	const int MAX = 25000;
	const int END = -1;
	thread reader([=, &ch, &v]{
		int i;
		while ((i = ch.read()) != END) {
			v.push_back(i);
		}
	});
	thread writer([=, &ch]{
		for (int i=0; i<MAX; ++i) {
			while (!ch.write(i)) {
				this_thread::sleep_for(chrono::milliseconds(10));
			}
		}
	});
	writer.join();
	while (!ch.write(END)) {
		this_thread::sleep_for(chrono::milliseconds(10));
	}
	reader.join();
	EXPECT_EQ(MAX, v.size());
	for (int i=0; i<MAX; ++i) {
		EXPECT_EQ(i, v[i]);
	}
}


TEST(ChannelTest, MultiThread) {
	Channel<int> ch;
	const int MAX = 100000;
	const int NUM_READER = 10;
	const int NUM_WRITER = 4;
	const int END = -1;
	vector<int> sink[NUM_READER];
	auto read = [=, &ch](vector<int>& v) {
		int i;
		while ((i = ch.read()) != END) {
			v.push_back(i);
		}
	};
	auto write = [=, &ch]() {
		for (int i = 0; i<MAX / NUM_WRITER; ++i) {
			while (!ch.write(i)) {
				this_thread::sleep_for(chrono::milliseconds(10));
			}
		}
	};
	thread readers[NUM_READER];
	thread writers[NUM_WRITER];
	for (int i=0; i<NUM_READER; ++i) {
		readers[i] = thread(read, std::ref(sink[i]));
	}
	for (int i=0; i<NUM_WRITER; ++i) {
		writers[i] = thread(write);
	}
	for (int i=0; i<NUM_WRITER; ++i) {
		writers[i].join();
	}
	for (int i=0; i<NUM_READER; ++i) {
		while (!ch.write(END)) {
			this_thread::sleep_for(chrono::milliseconds(10));
		}
	}
	for (int i=0; i<NUM_READER; ++i) {
		readers[i].join();
	}
	size_t totalSink = 0;
	for (int i=0; i<NUM_READER; ++i) {
		totalSink += sink[i].size();
	}
	EXPECT_EQ(MAX, totalSink);
}
