#include <chrono>
#include <vector>
#include <numeric>
#include <cmath>


class Timer{
	public:
	template<typename FOwner, void(FOwner::*func)()>
	double timeTask(FOwner *f)
	{
		auto start = std::chrono::steady_clock::now();
		(f->*func)();
		auto end = std::chrono::steady_clock::now();

		timeList.push_back(std::chrono::duration <double, std::milli>(end-start).count());
		return std::chrono::duration <double,std::milli>(end-start).count();
	}

	void deleteTime(int index) {timeList.begin() = timeList.erase(timeList.begin()+index);}
double getAverageTime() 
	{
		return std::accumulate(timeList.begin(), timeList.end(),0) / (double)timeList.size();
	}
	
	//This is actually the population standard deviation. Regular std Dev is over n-1 instead of n
	double getStdDev()
	{
		double avg = getAverageTime();
		std::vector<double> deviations;
		for(auto&& t: timeList)
		{
			deviations.push_back(abs(pow(t-avg,2)));
		}
		return sqrt(std::accumulate(deviations.begin(),deviations.end(),0) / (double)deviations.size());
	}


	private:
	std::vector<double> timeList;


};
