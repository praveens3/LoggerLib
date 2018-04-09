/*3
Name		:	Logger.h
Author		:	Praveen S
Description	:	Managages thread for LogWritter, Receives data from clients
*/

#ifndef Logger_h
#define Logger_h

#include <string>
#include <vector>
#include <algorithm>
#include <mutex>
#include <ctime>
#include <sstream>
#include "LogWritter.h"
#include "Configuration.h"
using namespace std;

#define EMPTY_STRING ""
#define _SEP_ "\t"
#define _SEP_OPEN_ "["
#define _SEP_CLOSE_ "]"

//LOGGER singleton class
class LOGGER {

	LOGGER() {}

	~ LOGGER() {
		logWritter.T_stop = false;
		Close();
	}

	LOGGER(const LOGGER &obj);
	LOGWRITTER logWritter;

	string MakeData(LOGLEVEL, string, vector<string>);
	string GetDatetime();
	string GetThreadID();
	string GetLogLevel(LOGLEVEL);	

public:

	//singleton static object reference
	static LOGGER& Log() {
		static LOGGER LOGGER_Obj;
		return LOGGER_Obj;
	}

	//core write
	void write(LOGLEVEL level, string msg, vector<string> headings);

	//write overload 1
	void write(LOGLEVEL level, string msg);

	//write overload 2
	void write(LOGLEVEL level, string heading1, string msg);

	//write overload 3
	void write(LOGLEVEL level, string heading1, string heading2, string msg);

	//write overload 4
	void write(LOGLEVEL level, vector<string> headings);

	//Logger can return if all data are flush to log file
	void Close();

	//Performance data analysis
	
	//returns total no of lines writen
	int gettotallines() { return logWritter.line; }

	//returns vector data size
	int getdatasize();

	//returns max no of data in a single instance
	int get_maxdatasize() { return logWritter.maxdatasize; }

};

#endif //Logger_h