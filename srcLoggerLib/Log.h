/*
Name		:	Log.h
Author		:	Praveen S
Description	:	Header file for Logger lib. Used to access Logger library
*/

#ifndef Log_h
#define Log_h

#include <string>
#include <vector>
using namespace std;

//LogLevel
enum LOGLEVEL {
	CRITICAL = 700,
	ERROR = 600,
	WARN = 500,
	DEBUG = 400,
	INFO = 300,
	TRACE = 200,
	ALL = 100,
	DEFAULT = 0,
};

//Public lib class
class LOG {

	LOG(){};

	~LOG();

	LOG(const LOG & Log);
	
	static LOG& impl__();

public:
	//static pulblic function for handle
	static LOG& getLogger() {
		return impl__();
	}

	//closing all log write in queue
	void close();

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

//without LOGLEVEL , assuming LOGLEVEL as configured/ default level

	//core write
	void write(string msg, vector<string> headings);

	//write overload 1
	void write(string msg);

	//write overload 2
	void write(string heading1, string msg);

	//write overload 3
	void write(string heading1, string heading2, string msg);

	//write overload 4
	void write(vector<string> headings);
};

#endif //Log_h