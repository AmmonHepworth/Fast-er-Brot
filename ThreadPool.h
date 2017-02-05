#ifndef THREADPOOL_H
#define THREADPOOL_H

#include<condition_variable>
#include<functional>
#include<thread>
#include<atomic>
#include<vector>
#include<mutex>
#include"TSQ.h"


class ThreadPool
{
	public:
	using func = std::function<void(void)>;
	ThreadPool(int numThreads);
	~ThreadPool();
	void post(func f);
	void stop();
	void run();
	void notify() { if(postCount) hasItem.notify_one();}
	bool queueEmpty();
	unsigned int getPostCount() { return postCount; } 

	private:
	std::vector<std::thread> pool;
	TSQ<func> q;
	std::condition_variable hasItem;
	std::mutex itemMutex;
	std::atomic<bool> shouldContinue;
	unsigned int postCount;

};


#endif
