/*
Name		:	Log.h
Author		:	Praveen S
Description	:	Manages public header for Logger lib
*/

#include "Log.h"
#include "Logger.h"


LOG& LOG::impl__() {
	static LOG Log;
	return Log;
}

LOG::~LOG() {
	//should not call/delete close, leads to access after LOGGER destroyed.
	//close();
}

void LOG::close() {
	LOGGER::Log().Close();
}

//core write
void LOG::write(LOGLEVEL level, string msg, vector<string> headings) {
	LOGGER::Log().write(level, msg, headings);
}

//write overload 1
void LOG::write(LOGLEVEL level, string msg) {
	LOGGER::Log().write(level, msg);
}

//write overload 2
void LOG::write(LOGLEVEL level, string heading1, string msg) {
	LOGGER::Log().write(level, heading1, msg);
}

//write overload 3
void LOG::write(LOGLEVEL level, string heading1, string heading2, string msg) {
	LOGGER::Log().write(level, heading1, heading2, msg);
}

//write overload 4
void LOG::write(LOGLEVEL level, vector<string> headings) {
	LOGGER::Log().write(level, headings);
}

//without LOGLEVEL , assuming LOGLEVEL as configured/ default level

//core write
void LOG::write(string msg, vector<string> headings) {
	write(LOGLEVEL::DEFAULT, msg, headings);
}

//write overload 1
void LOG::write(string msg) {
	write(LOGLEVEL::DEFAULT, msg);
}

//write overload 2
void LOG::write(string heading1, string msg) {
	write(LOGLEVEL::DEFAULT, heading1, msg);
}

//write overload 3
void LOG::write(string heading1, string heading2, string msg) {
	write(LOGLEVEL::DEFAULT, heading1, heading2, msg);
}

//write overload 4
void LOG::write(vector<string> headings) {
	write(LOGLEVEL::DEFAULT, headings);
}