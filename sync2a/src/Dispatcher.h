#ifndef DISPATCHER_H_
#define DISPATCHER_H_

#include "Packet.h"
#include <thread>
#include <map>
#include <future>
#include <mutex>

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

	std::future<Packet> getFuture(int userId);

protected:
	void dispatch();

	Processor& _processor;
	std::thread _thread;
	std::map<int, std::promise<Packet>> _dispTable;
	std::mutex _dispTableMutex;
};


} /* namespace clx */

#endif /* DISPATCHER_H_ */
