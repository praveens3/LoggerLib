/*
Name		:	RotateLog.h
Author		:	Praveen S
Description	:	Create log name, Rotate name with respect to size and time
*/
#include <string>
#include <fstream>
#include <vector>
#include <time.h>

using namespace std;

#define EMPTY_STRING ""
#define LOG_NAME "LOG"
#define LOG_EXTEN ".txt"
#define ROTATE_EXTEN "_"
#define ALN_NAME "Aln.dat"

//RotateLog class for rotating logname by size and time interval
class ROTATELOG {
	string logName;
	string coreName;
	unsigned int itt;
	bool T_stop;

	void Init();
	//manages active linformations of logname, log itterator, and datetime
	vector<string> Get_ALN();
	void Set_ALN(string, int);

	string Get_Date();
	string Get_ValidLogName(string);
	void RotateName();
	bool Is_LogFileSize_Valid();
	bool Is_LogTimeInterval_Valid();
	bool Is_ValidLogName(string);

	//Thread function to rotate log
	void __RotateLogName();

public:
	ROTATELOG() {
		Init();
	}

	~ROTATELOG() {
		T_stop = false;
	}

	string get_logName() {
		__RotateLogName();
		return logName;
	}
};