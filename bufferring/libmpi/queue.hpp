#ifndef _QUEUE_HPP_
#define _QUEUE_HPP_

#include <condition_variable>
#include <mutex>
#include <queue>

template <typename Data>
class Queue
{
private:
	std::queue<Data> queue;
	mutable std::mutex mutex;
	std::condition_variable cv;

public:
	void push(const Data &data)
	{
		std::unique_lock<std::mutex> lock(mutex);
		queue.push(data);
		lock.unlock();
		cv.notify_one();
	}

	bool empty(void) const
	{
		std::unique_lock<std::mutex> lock(mutex);
		return queue.empty();
	}

	bool try_pop(Data &popped_value)
	{
		std::unique_lock<std::mutex> lock(mutex);
		if (queue.empty())
			return false;

		popped_value = queue.front();
		queue.pop();
		return true;
	}

	void wait_and_pop(Data &popped_value)
	{
		std::unique_lock<std::mutex> lock(mutex);
		while (queue.empty())
			cv.wait(lock);

		popped_value = queue.front();
		queue.pop();
	}
};

#endif /* _QUEUE_HPP_ */
