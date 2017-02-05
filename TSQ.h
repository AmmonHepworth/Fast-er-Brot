#ifndef TSQ_H
#define TSQ_H

#include<queue>
#include<mutex>

template <typename T>
class TSQ
{
	public:

	void enqueue(T t)
	{
		std::lock_guard<std::mutex> l(m);
		q.push(t);
	}

	T dequeue()
	{
		std::lock_guard<std::mutex> l(m);
		auto retVal = q.front();
		q.pop();
		return retVal;
	}

	bool try_dequeue(std::function<void(void)> &f)
	{
		std::lock_guard<std::mutex> l(m);
		if(q.empty()) return false;
		f = q.front();
		q.pop();
		return true;
	}

	bool empty()
	{
		return q.empty();
	}

	private:
	std::mutex m;
	std::queue<T> q;
};



#endif
