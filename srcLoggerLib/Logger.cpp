/*
Name		:	Logger.h
Author		:	Praveen S
Description	:	Managages thread for LogWritter, Receives data from clients
*/

#include "Logger.h"

//concontinating loglevel, Thread Id and input data
string LOGGER::MakeData(LOGLEVEL level, string msg, vector<string> headings) {
	string md = EMPTY_STRING;
	string head_join = _SEP_;
	for_each(headings.begin(), headings.end(), [&head_join](string h) {
		head_join += _SEP_OPEN_;
		head_join += h;
		head_join += _SEP_CLOSE_;
		head_join += _SEP_;
	});
	md = GetDatetime() + _SEP_ + GetThreadID() + _SEP_ + GetLogLevel(level) + head_join + msg;
	return md;
}

//returns datetime
string LOGGER::GetDatetime() {
	string dt = EMPTY_STRING;
	time_t rawtime;
	time(&rawtime);
	//dt = ctime(&rawtime); //Mon Aug 15 18:37:43 2016
	//dt.resize(dt.size()-1);
	char t_buff[20];
	strftime(t_buff, 20, "%x %X", localtime(&rawtime)); //08/15/16 18:53:48
	dt = t_buff;
	return dt;
}

//returns current thred ID
string LOGGER::GetThreadID() {
	string id = EMPTY_STRING;
	std::stringstream ss;
	ss<<this_thread::get_id();
	if(ss != nullptr && ss.str()!= EMPTY_STRING )
		id = _SEP_OPEN_ + ss.str() + _SEP_CLOSE_;
	return id;
}

//returns string of loglevel
string LOGGER::GetLogLevel(LOGLEVEL level) {
	switch(level) {
		case LOGLEVEL::ALL:
			return "ALL";
		case LOGLEVEL::CRITICAL:
			return "CRITICAL";
		case LOGLEVEL::ERROR:
			return "ERROR";
		case LOGLEVEL::WARN:
			return "WARN";
		case LOGLEVEL::DEBUG:
			return "DEBUG";
		case LOGLEVEL::INFO:
			return "INFO";
		case LOGLEVEL::TRACE:
			return "TRACE";
		default:
			return EMPTY_STRING;
	}
}

//Core write
void LOGGER::write(LOGLEVEL level, string msg, vector<string> headings) {
	if(level == LOGLEVEL::DEFAULT)
		level = config.cParams.logLevel;
	if(level >= config.cParams.logLevel) {
		{
			std::lock_guard<mutex> push_gaurd(logWritter.mu_deque_data);
			logWritter.data.push_back(MakeData(level, msg, headings));
		}
	}
}

//write overload 1
void LOGGER::write(LOGLEVEL level, string msg) {
	vector<string> EMPTY_VECTOR;
	write(level, msg, EMPTY_VECTOR);
}

//write overload 2
void LOGGER::write(LOGLEVEL level, string heading1, string msg) {
	vector<string> v;v.push_back(heading1);
	write(level, msg, v);
}

//write overload 3
void LOGGER::write(LOGLEVEL level, string heading1, string heading2, string msg) {
	vector<string> v;
	v.push_back(heading1);
	v.push_back(heading2);
	write(level, msg, v);
}

//write overload 4
void LOGGER::write(LOGLEVEL level, vector<string> headings) {
	if(headings.size() <= 0)
		return;
	if(headings.size() == 1)
		write(level, headings[0]);
	if(headings.size() >1) {
		string msg = headings.back();
		headings.pop_back();
		write(level, msg, headings);
	}
}

//logger shold exit if all data are flushed to log file
void LOGGER::Close() {
	unsigned int wait_sec = 1;
	//wait for 4169 max m_sec
	while(wait_sec < 200) {
		if(!LOGGER::getdatasize())
			return;
		std::this_thread::sleep_for(std::chrono::milliseconds(wait_sec));
		wait_sec += 5;
	}
}

//perfomance data, returns vector data size
int LOGGER::getdatasize() {
	{
		std::lock_guard<mutex> size_gaurd(logWritter.mu_deque_data);
		return logWritter.data.size();
	}
}