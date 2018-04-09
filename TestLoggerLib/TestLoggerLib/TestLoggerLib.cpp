// TestLoggerLib.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Log.h"
#include <thread>

void __ThreadFun() {
	//LOGGER::Log().write(LOGLEVEL::ERROR, "test msg log 1");
	//LOGGER::Log().write(LOGLEVEL::ERROR, "test msg log 2");
	//LOGGER::Log().write(LOGLEVEL::ERROR, "test msg log 3");
	LOG::getLogger().write(LOGLEVEL::INFO, "fsdfdsfds");
	LOG::getLogger().write(LOGLEVEL::INFO, "thread data write....");
}

int _tmain(int argc, _TCHAR* argv[])
{
	
	LOG::getLogger().write("write log info");
	LOG::getLogger().write( "");
	//Log.write(LOGLEVEL::INFO, "", "head2" "loger");

	std::thread t1(__ThreadFun);
	std::thread t2(__ThreadFun);
	t1.join();
	t2.join();

	//int size = LOGGER::Log().getdatasize();
	//size = LOGGER::Log().gettotallines();
	
	//int s1 = clock();
	//LOGGER::Log().Close();
	int s2 = clock();
	//int s = s2-s1;
	
	LOG::getLogger().close();
	//std::this_thread::sleep_for(std::chrono::seconds(10));
	return 0;
}

