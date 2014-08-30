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

class Processor
{
public:
	Processor();
	~Processor();
	Processor& operator=(const Processor&) = delete;
	Processor(const Processor&) = delete;
	Processor& operator=(Processor&&) = delete;
	Processor(Processor&&) = delete;

	void sendInput(const Packet& packet);
	Packet recvOutput();

protected:
	void process();

	Channel<Packet> _input;
	Channel<Packet> _output;
	std::thread _thread;
};

} /* namespace clx */

#endif /* PROCESSOR_H_ */
