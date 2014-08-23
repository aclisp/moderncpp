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
	thread reader([&ch, &v]{
		int i;
		while ((i = ch.read()) != END) {
			v.push_back(i);
		}
	});
	thread writer([&ch]{
		for (int i=0; i<MAX; ++i) {
			while (!ch.write(i)) {
				this_thread::sleep_for(chrono::milliseconds(10));
			}
		}
		ASSERT_TRUE(ch.write(int(END))); // indicates end
	});
	reader.join();
	writer.join();
	EXPECT_EQ(MAX, v.size());
	for (int i=0; i<MAX; ++i) {
		EXPECT_EQ(i, v[i]);
	}
}


TEST(ChannelTest, MultiThread) {
	Channel<int> ch;
	const int MAX = 100000;
	const int NUM_READER = 3;
	const int NUM_WRITER = 10;
	const int END = -1;
	vector<int> sink[NUM_READER];
	struct Read {
		Channel<int>& _ch;
		vector<int>& _v;
		Read(Channel<int>& ch, vector<int>& v)
			: _ch(ch), _v(v) {}
		void operator()() {
			int i;
			while ((i = _ch.read()) != END) {
				_v.push_back(i);
			}
		}
	};
	struct Write {
		Channel<int>& _ch;
		Write(Channel<int>& ch)
			: _ch(ch) {}
		void operator()() {
			for (int i=0; i<MAX/NUM_WRITER; ++i) {
				while (!_ch.write(i)) {
					this_thread::sleep_for(chrono::milliseconds(10));
				}
			}
		}
	};
	thread readers[NUM_READER];
	thread writers[NUM_WRITER];
	for (int i=0; i<NUM_READER; ++i) {
		readers[i] = thread(Read(ch, sink[i]));
	}
	for (int i=0; i<NUM_WRITER; ++i) {
		writers[i] = thread(Write(ch));
	}
	for (int i=0; i<NUM_WRITER; ++i) {
		writers[i].join();
	}
	for (int i=0; i<NUM_READER; ++i) {
		ch.write(END);
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
