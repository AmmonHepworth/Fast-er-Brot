#include"ThreadPool.h"
#include <iostream>

	ThreadPool::ThreadPool(int numThreads):pool(numThreads),q(),hasItem(),itemMutex(),shouldContinue(true),postCount(0)
{ for(auto && t:pool)
	{
		t = std::thread([=](){this->run();});
	}
}

ThreadPool::~ThreadPool()
{
	hasItem.notify_all();
	for (auto && t:pool)
	{
		t.join();
	}
}

void ThreadPool::run()
{
	while(shouldContinue)
	{ 
		func task;
		while(!q.try_dequeue(task) && shouldContinue && postCount)
		{
			std::unique_lock<std::mutex> l(itemMutex);
			//	std::cout << "Thread waiting... shouldContiue is: " << shouldContinue <<", count is : " << postCount << std::endl;
				if(!shouldContinue) return;
			hasItem.wait(l,
				[this]{return !this->shouldContinue || !this->q.empty(); });
			//	std::cout << "Thread resumed... shouldContinue: " << shouldContinue << std::endl;
			if(!shouldContinue) return;
		}
		if(task) {
			{
				std::lock_guard<std::mutex> lock( std::mutex);
			--postCount;
			}
			//	std::cout << "Pre task run, decrement post count, postCount:" << postCount << std::endl;
			task();
			if(!shouldContinue) return;
		}
	}
}

void ThreadPool::post(func f)
{
	q.enqueue(f); 
	++postCount; 
	hasItem.notify_one(); 
	//	std::cout << "Enqueued, increment PC, and notify" << std::endl;
}


void ThreadPool::stop() {

	shouldContinue = false; 

	std::cout << "Image generated, writing..." << std::endl;
	hasItem.notify_all();
}

bool ThreadPool::queueEmpty()
{
	return q.empty();
}


