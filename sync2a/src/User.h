#ifndef USER_H_
#define USER_H_


#include <thread>
#include <random>
#include <chrono>
#include <atomic>


namespace clx
{


class Processor;


class User
{
public:
	User(int id, Processor& processor);
	~User() {}
	User& operator=(const User&) = delete;
	User(const User&) = delete;
	User& operator=(User&&) = delete;
	User(User&&) = delete;

	void detach();

protected:
	static void process(int id, Processor& processor);
	static std::atomic_int _payloadGenerator;

	int _id;
	Processor& _processor;
	std::thread _thread;
};


class UserGenerator
{
public:
	UserGenerator(double arrivalRate);
	~UserGenerator() {}
	UserGenerator& operator=(const UserGenerator&) = delete;
	UserGenerator(const UserGenerator&) = delete;
	UserGenerator& operator=(UserGenerator&&) = delete;
	UserGenerator(UserGenerator&&) = delete;

	void newUser(Processor& processor);

protected:
	double nextArrivalInterval();
	double elapsedSeconds();

	int _idGenerator{ 0 };  // User ID generator
	std::chrono::time_point<std::chrono::system_clock> _startTimePoint{ std::chrono::system_clock::now() };
	std::random_device _randomDevice;
	std::mt19937 _randomGenerator;
	std::exponential_distribution<double> _arrivalInterval;  // User arrival interval
};


}//namespace clx


#endif//USER_H_
