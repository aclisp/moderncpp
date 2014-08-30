#include "Dispatcher.h"
#include "Packet.h"
#include "Processor.h"
#include <iostream>

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

		cout << "Dispatch user [" << packet._userId << "]" << endl;
	}
}

} /* namespace clx */
