/*
 * Packet.h
 *
 *  Created on: Aug 23, 2014
 *      Author: homer
 */

#ifndef PACKET_H_
#define PACKET_H_


#include <string>


namespace clx
{

class Packet
{
public:
	enum class Type {
		DEFAULT,
		EXIT,
	};
	Packet(int userId, long long payload)
		: _userId(userId), _type(Type::DEFAULT), _payload(payload)
	{}
	Packet() {}
	std::string dump() const;

	int _userId = -1;
	Type _type = Type::EXIT;
	long long _payload = 0;
};


extern const Packet SYS_EXIT;


} /* namespace clx */

#endif /* PACKET_H_ */
