/*
Name		:	LoggerTester.cpp
Author		:	Praveen S
Description	:	Used for testing Logger directly (not as lib.)
*/


#include "Log.h"
#include <thread>

//for testing
void T1(string id, int duration) {
	for(int i=0; i<100; i++) {
		LOG::getLogger().write(LOGLEVEL::ERROR, "string test msg: "+std::to_string(i));
		_sleep(duration);
	}
}

int main() {

	int s1 = clock();
	
	vector<thread> vt;
	for(int i=0; i<500; i++) {
		//vt.push_back(thread(T1, "\t"+std::to_string(i)+"\t", (i%2)?(i*2):0));
	}

	for(auto i = 0; i< vt.size(); i++) {
		//vt[i].join();
	}
	//for_each(vt.begin(), vt.end(), [=](thread t) {
	//	t.join();
	//});

	//std::thread t1(T1, "\tA\t", 100);
	//std::thread t2(T1, "\tB2\t", 200);
	//std::thread t3(T1, "\tC3\t",300);
	//std::thread t4(T1, "\tD5\t", 500);
	//std::thread t5(T1, "\tE7\t", 0);
	//t5.join();
	//t4.join();
	//t3.join();
	//t2.join();
	//t1.join();
	//while(LOG::getLogger().getdatasize() > 0) {
	//	_sleep(2000);
	//}
	
	LOG::getLogger().write(LOGLEVEL::INFO, "data size: ");
	LOG::getLogger().write(LOGLEVEL::INFO, "data size: ");
//	LOG::getLogger().write(LOGLEVEL::INFO, "data size: " , std::to_string(LOG::getLogger().getdatasize()));
//	LOG::getLogger().write(LOGLEVEL::DEBUG, "max data size: " ,"head2", std::to_string(LOG::getLogger().get_maxdatasize()));
//	LOG::getLogger().write(LOGLEVEL::ERROR, "Total lines: " + std::to_string(LOG::getLogger().gettotallines()));
	int s2 = clock();
	int s = s2-s1;
	LOG::getLogger().write(LOGLEVEL::INFO, "Time consumed: " + std::to_string(s));
	
	LOG::getLogger().close();
	
	//}
	return 0;
}
//end testing
