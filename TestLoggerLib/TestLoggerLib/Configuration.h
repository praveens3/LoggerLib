/*
Name		:	Configuration.h
Author		:	Praveen S
Description	:	custom configurable variables
*/

#ifndef Configuration_h
#define Configuration_h

//#include "Logger.h"
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

#define DEFAULT_LOGLEVEL LOGLEVEL::TRACE
#define DEFAULT_LOG_NAME "LOG"
#define DEFAULT_LOG_SIZE_IN_MB 10
#define DEFAULT_ROTATE_BY_DAY true
#define DEFAULT_ROTATE_BY_SIZE true
#define EMPTY_STRING ""

enum LOGLEVEL {
	OFF = 0,
	CRITICAL = 700,
	ERROR = 600,
	WARN = 500,
	DEBUG = 400,
	INFO = 300,
	TRACE = 200,
	ALL = 100
};

class CONFIG {
private:
	struct CONFIGP {
		string logName;
		unsigned int logSize;
		bool rotateBySize;
		bool rotateByDay;
		LOGLEVEL logLevel;
	};
public:
	CONFIG();
	CONFIGP cParams;

private:

	void loadDefaults();

	void readConfigFile();

	LOGLEVEL getLogLevel(string level);

	void validateLoadData(string data);

	//common split string return vector
	std::vector<string> splitstring(string ival, char delimiter );
};

#endif //Configutration_h