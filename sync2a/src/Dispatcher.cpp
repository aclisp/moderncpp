#include "Dispatcher.h"
#include "Packet.h"
#include "Processor.h"
#include <iostream>
#include <chrono>

namespace clx
{

using namespace std;

Dispatcher::Dispatcher(Processor& processor)
	: _processor(processor)
{
	_thread = thread(&Dispatcher::dispatch, this);
}


Dispatcher::~Dispatcher()
{
	_thread.join();
}


void Dispatcher::dispatch()
{
	for (;;) {
		Packet packet = _processor._output.read();
		if (packet._type == SYS_EXIT._type) {
			break;
		}

		//cout << "Dispatch user [" << packet._userId << "]" << endl;
		unique_lock<mutex> lock(_dispTableMutex);
		auto search = _dispTable.find(packet._userId);
		if (search != _dispTable.end()) {
			search->second.set_value(packet);
			_dispTable.erase(search);
		}
		else {
			cerr << "ERROR DISP: User ID NOT FOUND: " << packet._userId << endl;
		}

		//cout << "DEBUG: dispTable size=" << _dispTable.size() << endl;
	}
}


void Dispatcher::dumpDispTable()
{
	unique_lock<mutex> lock(_dispTableMutex);
	for (const auto& pair : _dispTable) {
		int userId = pair.first;
		cout << "DISP TABLE: User ID: " << userId << endl;
	}
}


future<Packet> Dispatcher::getFuture(int userId)
{
	promise<Packet> promise;
	future<Packet> future = promise.get_future();
	unique_lock<mutex> lock(_dispTableMutex);
	_dispTable[userId] = move(promise);
	lock.unlock();
	return move(future);
}

} /* namespace clx */
