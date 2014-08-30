/*
 * Packet.cpp
 *
 *  Created on: Aug 23, 2014
 *      Author: homer
 */

#include "Packet.h"
#include <sstream>


namespace clx
{

using namespace std;

const Packet SYS_EXIT = Packet();

string Packet::dump() const
{
	ostringstream ss;
	ss << "Packet(userId="
	   << _userId << ", payload="
	   << _payload << ")";
	return ss.str();
}


} /* namespace clx */
