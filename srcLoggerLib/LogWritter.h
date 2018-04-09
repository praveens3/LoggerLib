/*
Name		:	LogWriter.h
Author		:	Praveen S
Description	:	de-queue the data, MakeData and WriteData
*/

#include <string>
#include <fstream>
#include <thread>
#include <deque>
#include <algorithm>
#include <mutex>
#include <atomic>
#include "RotateLog.h"
using namespace std;

#define ENDLINE "\n"
#define ROTATE_LOG_FOR_LINES 1000	//for every 1000 lines logname is cross checked

//Logwritter class for writting data to log file
class LOGWRITTER {
public:

	LOGWRITTER() {
		Init();
	}

	~LOGWRITTER() {
		T_stop = false;
		close();
	}

	void Init();
	deque<string> data;
	std::mutex mu_deque_data;

	//perofmance params
	unsigned int line;
	unsigned int maxdatasize;
	bool T_stop;

private:

	//RotateLog object for rotating logname	
	ROTATELOG RLOG_obj;

	ofstream writter;
	string logName;
	unsigned int writeCounter;

	void get_logname() {
		logName = RLOG_obj.get_logName();
	}

	void open() {
		get_logname();
		writter.open(logName + LOG_EXTEN, ios::app);
	}

	void close() {
		if(writter.is_open())
			writter.close();
	}

	//Thread write
	void write();

	void reset();
};