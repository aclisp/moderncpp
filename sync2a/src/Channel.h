/*
 * Channel.h
 *
 *  Created on: Aug 20, 2014
 *      Author: homer
 */

#ifndef CHANNEL_H_
#define CHANNEL_H_


#include <deque>
#include <mutex>
#include <condition_variable>


namespace clx
{

template<typename T>
class Channel
{
public:
	void setBlockWriteOnFull(bool block) { _blockWriteOnFull = block; }
	void setCapacity(std::size_t cap) { _capacity = cap; }
	bool write(const T&);
	T read();

protected:
	bool _blockWriteOnFull = true;
	std::size_t _capacity = 20;
	std::deque<T> _buffer;
	std::mutex _mutex;
	std::condition_variable _readable;
	std::condition_variable _writable;
};


template<typename T>
bool Channel<T>::write(const T& obj)
{
	std::unique_lock<std::mutex> lock(_mutex);

	if (_blockWriteOnFull) {
		_writable.wait(lock, [this] { return _buffer.size() < _capacity; });
	} 
	else if (_buffer.size() >= _capacity) {
		return false;
	}

	_buffer.emplace_front(obj);
	lock.unlock();
	_readable.notify_one();
	return true;
}


template<typename T>
T Channel<T>::read()
{
	std::unique_lock<std::mutex> lock(_mutex);
	_readable.wait(lock, [this] { return !_buffer.empty(); });
	T obj(_buffer.back());
	_buffer.pop_back();
	lock.unlock();

	if (_blockWriteOnFull) {
		_writable.notify_one();
	}
	return obj;
}


} /* namespace clx */

#endif /* CHANNEL_H_ */
