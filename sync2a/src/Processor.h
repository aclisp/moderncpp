/*
 * Processor.h
 *
 *  Created on: Aug 23, 2014
 *      Author: homer
 */

#ifndef PROCESSOR_H_
#define PROCESSOR_H_


#include "Channel.h"
#include "Packet.h"
#include "Dispatcher.h"
#include <thread>
#include <random>


namespace clx
{

class Processor
{
public:
	friend class Dispatcher;

	Processor(int meanProcessingDelay);
	~Processor();
	Processor& operator=(const Processor&) = delete;
	Processor(const Processor&) = delete;
	Processor& operator=(Processor&&) = delete;
	Processor(Processor&&) = delete;

	bool sendInput(const Packet& packet);
	Dispatcher& dispatcher();

protected:
	void process();
	int nextProcessingDelay();

	Channel<Packet> _input;
	Channel<Packet> _output;
	std::thread _thread;
	Dispatcher _disp;

	std::random_device _randomDevice;
	std::mt19937 _randomGenerator;
	std::uniform_int_distribution<int> _processingDelay;
};

} /* namespace clx */

#endif /* PROCESSOR_H_ */
