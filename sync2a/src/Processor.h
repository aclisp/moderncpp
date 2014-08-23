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
#include <thread>


namespace clx
{

extern template class Channel<Packet>;

class Processor
{
public:
	Processor();
	~Processor();

	void sendInput(const Packet& packet);
	Packet recvOutput();

protected:
	void process();

	std::thread _thread;
	Channel<Packet> _input;
	Channel<Packet> _output;
};

} /* namespace clx */

#endif /* PROCESSOR_H_ */