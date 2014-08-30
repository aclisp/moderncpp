/*
 * Processor.cpp
 *
 *  Created on: Aug 23, 2014
 *      Author: homer
 */

#include "Processor.h"
#include <iostream>
#include <thread>
#include <chrono>


namespace clx
{


using namespace std;


void Processor::process()
{
	//cout << "Processor start" << endl;
	for (;;) {
		Packet packet = _input.read();
		if (packet._type == SYS_EXIT._type) {
			break;
		}
		//cout << "process: " << packet.dump() << endl;

		packet._payload += 10000;
		this_thread::sleep_for(chrono::milliseconds(nextProcessingDelay()));

		if (!_output.write(packet)) {
			cerr << "Processor output overflow: drop " << packet.dump() << endl;
		}
	}
	//cout << "Processor quit" << endl;
}


int Processor::nextProcessingDelay()
{
	return _processingDelay(_randomGenerator);
}


Processor::Processor(int meanProcessingDelay)
	: _disp(*this)
	, _randomGenerator(_randomDevice())
	, _processingDelay(meanProcessingDelay - 100, meanProcessingDelay + 100)
{
	_thread = thread(&Processor::process, this);
}

Processor::~Processor()
{
	while (!_output.write(SYS_EXIT)) {
		cerr << "Processor quit: can not end output!" << endl;
		this_thread::sleep_for(chrono::milliseconds(10));
	}
	while (!_input.write(SYS_EXIT)) {
		cerr << "Processor quit: can not end input!" << endl;
		this_thread::sleep_for(chrono::milliseconds(10));
	}
	_thread.join();
}

bool Processor::sendInput(const Packet& packet)
{
	if (!_input.write(packet)) {
		cerr << "Processor overload: ignore " << packet.dump() << endl;
		return false;
	}
	else {
		return true;
	}
}

Dispatcher& Processor::dispatcher()
{
	return _disp;
}

} /* namespace clx */
