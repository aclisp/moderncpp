#ifndef DISPATCHER_H_
#define DISPATCHER_H_

#include "Packet.h"
#include <thread>
#include <map>
#include <future>

namespace clx
{

class Processor;

class Dispatcher
{
public:
	Dispatcher(Processor& processor);
	~Dispatcher();
	Dispatcher& operator=(const Dispatcher&) = delete;
	Dispatcher(const Dispatcher&) = delete;
	Dispatcher& operator=(Dispatcher&&) = delete;
	Dispatcher(Dispatcher&&) = delete;

protected:
	void dispatch();

	Processor& _processor;
	std::thread _thread;
	std::map<int, std::promise<Packet>> _cache;
};


} /* namespace clx */

#endif /* DISPATCHER_H_ */
