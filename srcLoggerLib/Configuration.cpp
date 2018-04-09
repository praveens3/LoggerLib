/*
Name		:	Configuration.cpp
Author		:	Praveen S
Description	:	custom configurable variables
*/
#include "Configuration.h"

CONFIG::CONFIG() {
	loadDefaults();
	readConfigFile();
}

 void CONFIG::loadDefaults() {
	cParams.logName = DEFAULT_LOG_NAME;
	cParams.logSizeinmb = DEFAULT_LOG_SIZE_IN_MB;
	cParams.logLevel = DEFAULT_LOGLEVEL;
	cParams.rotateBySize = DEFAULT_ROTATE_BY_SIZE;
	cParams.rotateByDay = DEFAULT_ROTATE_BY_DAY;
}

void CONFIG::readConfigFile() {
	try {
		ifstream fRead(CONFIG_FILE, ios::in);
		string data;
		if(fRead.is_open()) {
			while(getline(fRead, data)) {
				validateLoadData(data);
			}
		}
		fRead.close();
	} catch(std::exception ex) {}
}

LOGLEVEL CONFIG::getLogLevel(string level) {
	std::transform(level.begin(), level.end(), level.begin(), ::toupper);

	if(level == "ALL")
		return LOGLEVEL::ALL;
	else if(level == "CRITICAL")
		return LOGLEVEL::CRITICAL;
	else if(level == "ERROR")
		return LOGLEVEL::ERROR;
	else if(level == "WARN")
		return LOGLEVEL::WARN;
	else if(level == "DEBUG")
		return LOGLEVEL::DEBUG;
	else if(level == "INFO")
		return LOGLEVEL::INFO;
	else if(level == "TRACE")
		return LOGLEVEL::TRACE;
	else 
		return DEFAULT_LOGLEVEL;
}

void CONFIG::validateLoadData(string data) {
	std::transform(data.begin(), data.end(), data.begin(), ::tolower);
	if(data.find("=") != string::npos) {
	vector<string> vData = splitstring(data, '=');
	if(vData[0] == "logname") {
		if(vData[1] != EMPTY_STRING)
			cParams.logName = vData[1];
	} else if(vData[0] == "logsize") {
		try {
			unsigned int val = atoi(vData[1].c_str());
			if(val >= 1 && val <= 1024)
				cParams.logSizeinmb = val;
		}catch(std::exception ex){}
	} else if(vData[0] == "loglevel") {
		if(vData[1] != EMPTY_STRING)
			cParams.logLevel = getLogLevel(vData[1]);
	} else if(vData[0] == "rotatebysize") {
		if(vData[1] == "false" || vData[1] == "0")
			cParams.rotateBySize = false;
	} else if(vData[0] == "rotatebyday") {
		if(vData[1] == "false" || vData[1] == "0")
			cParams.rotateByDay = false;
	}
}
}

//common split string return vector
std::vector<string> CONFIG::splitstring(string ival, char delimiter ) {

	std::vector<string> vec_ret;
	string str1 = EMPTY_STRING;

	for(int i=0; i<ival.length()+1; i++) {
		if(ival[i] == delimiter || ival[i] =='\0') { 
			vec_ret.push_back(str1);
			str1 = EMPTY_STRING;
		} else {
			str1+=ival[i];
		}
	}
	return vec_ret;
}
