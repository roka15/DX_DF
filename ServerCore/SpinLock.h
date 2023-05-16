#pragma once
#include <thread>
#include <atomic>
using namespace std;
class SpinLock
{
public:
	SpinLock():mlimit_loop(100),msleep_time(0)
	{
	}
	~SpinLock() {}
	void lock()
	{
		bool expected = false;
		bool desired = true;
		while (mlocked.compare_exchange_strong(expected,desired)==false)
		{
			expected = false;
			if (mloop_count.load() == mlimit_loop)
				this_thread::sleep_for(100ms);
		}
	}
	void unlock()
	{
		mlocked.store(false);
	}
	void set_info(int _limit_loop, int _sleep_time)
	{
		mlimit_loop = _limit_loop;
		msleep_time = _sleep_time;
	}
private:
	int mlimit_loop;
	int msleep_time;
	atomic<int> mloop_count=0;
	atomic<bool> mlocked = false;
};

