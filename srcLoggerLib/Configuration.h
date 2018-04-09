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
#include "Log.h"
using namespace std;

#define DEFAULT_LOG_NAME "LOG"
#define DEFAULT_LOG_SIZE_IN_MB 10
#define DEFAULT_LOGLEVEL LOGLEVEL::TRACE
#define DEFAULT_ROTATE_BY_DAY true
#define DEFAULT_ROTATE_BY_SIZE true
#define EMPTY_STRING ""
#define CONFIG_FILE "config.txt"

struct CONFIGP {
	string logName;
	unsigned int logSizeinmb;
	bool rotateBySize;
	bool rotateByDay;
	LOGLEVEL logLevel;
};

class CONFIG {
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

static CONFIG config;
#endif //Configutration_h