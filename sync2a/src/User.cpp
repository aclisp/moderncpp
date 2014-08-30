#include "User.h"
#include "Packet.h"
#include "Processor.h"
#include <iostream>
#include <functional>


namespace clx
{

using namespace std;


UserGenerator::UserGenerator(double arrivalRate)
	: _randomGenerator(_randomDevice())
	, _arrivalInterval(arrivalRate)
{

}


double UserGenerator::nextArrivalInterval()
{
	return _arrivalInterval(_randomGenerator);
}


double UserGenerator::elapsedSeconds()
{
	chrono::duration<double> elapsed = chrono::system_clock::now() - _startTimePoint;
	return elapsed.count();
}


void UserGenerator::newUser(Processor& processor)
{
	double intervalSeconds = nextArrivalInterval();
	long long microSeconds = long long (intervalSeconds * 1000 * 1000);
	this_thread::sleep_for(chrono::microseconds(microSeconds));

	int newUserId = ++_idGenerator;
	if (_idGenerator >= 99) _idGenerator = 0;
	cout << "User [" << newUserId << "] spawned at " << elapsedSeconds() 
		 << "s (" << intervalSeconds << ")" << endl;

	User user(newUserId, processor);
	user.detach();
}


User::User(int id, Processor& processor)
	: _id(id)
	, _processor(processor)
{
	_thread = thread(&User::process, _id, ref(_processor));
}


void User::detach()
{
	_thread.detach();
}


void User::process(int id, Processor& processor)
{
	Packet request(id, 10000 + id);
	processor.sendInput(request);

	auto future = processor.dispatcher().getFuture(id); 
	Packet response = future.get();
	cout << "User [" << id << "] got response: " << response.dump() << endl;
}


} /* namespace clx */
