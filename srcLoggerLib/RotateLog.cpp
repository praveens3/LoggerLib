/*
Name		:	RotateLog.h
Author		:	Praveen S
Description	:	Create log name, Rotate name with respect to size and time
*/
#include "RotateLog.h"
#include "Configuration.h"

//init the thread
void ROTATELOG::Init() {
	logName = coreName = LOG_NAME;
	if(config.cParams.logName != EMPTY_STRING)
		logName = coreName = config.cParams.logName;
	itt = 0;
	vector<string> aln = Get_ALN();
	if(logName != EMPTY_STRING && aln.size() > 3) {
		if(logName != aln[0] || (aln[2] == "0" && logName != aln[1]))
			Set_ALN(logName, itt);
		else {
			logName = aln[0];
			if(aln[2] == "0")
				logName = aln[1];
		}
	}
	T_stop = true;
}

//Thread function to rotate log
void ROTATELOG::__RotateLogName() {
	if(!Is_LogFileSize_Valid() || !Is_LogTimeInterval_Valid()) {
		RotateName();
	}
}

//Get the active log name data
vector<string> ROTATELOG::Get_ALN() {
	vector<string> aln;
	string line = EMPTY_STRING;
	ifstream f_read(ALN_NAME);
	vector<string> name;
	if(f_read.is_open()){
		while(getline(f_read, line)) {
			name.push_back(line);
			if(name.size() == 3) break;
		}
		f_read.close();
	} else {
		f_read.close();
		Set_ALN(logName, itt);
	}


	if(name.size() == 3 && name[0] != EMPTY_STRING) {
		aln.push_back(name[0] + ROTATE_EXTEN + name[1]);
		aln.push_back(name[0]); //logName
		aln.push_back(name[1]); //counter
		aln.push_back(name[2]); //datetime
	} else {
		Set_ALN(logName, itt);
	}

	return aln;
}

//Write active log name file with rotated log file name
void ROTATELOG::Set_ALN(string lName, int itter) {
	logName = lName;
	itt = itter;
	ofstream w_file(ALN_NAME, ios::out);
	if(w_file.is_open()) {
		w_file<<coreName<<std::endl;
		w_file<<std::to_string(itt)<<endl;
		w_file<<Get_Date();
	}
	w_file.close();
}

//get date
string ROTATELOG::Get_Date() {
	string dt = EMPTY_STRING;
	time_t rawtime;
	time(&rawtime);
	char t_buff[10];
	strftime(t_buff, 10, "%x", localtime(&rawtime));
	return t_buff;
}

//check the log file size and compare with logsize limit
bool ROTATELOG::Is_LogFileSize_Valid() {
	if(!config.cParams.rotateBySize)
		return true;

	//get size of logName
	std::ifstream f_read(logName + LOG_EXTEN, std::ifstream::ate | std::ifstream::binary);
	double logFileSize = f_read.tellg();
	f_read.close();

	//compare with LOG_FILE_SIZE_LIMIT in mb
	if(logFileSize > config.cParams.logSizeinmb * 1024 * 1024)
		return false;

	return true;
}

//check the log time interval exceed with limit
bool ROTATELOG::Is_LogTimeInterval_Valid() {
	if(!config.cParams.rotateByDay)
		return true;

	//get log file logName properties
	vector<string> vec = Get_ALN();

	if(vec.size() == 4) {
		//compare with get_cln datetime
		if(vec[3].compare(Get_Date()) != 0)
			return false;
	}

	return true;
}

//Change the Log file name
void ROTATELOG::RotateName() {
	string rName = EMPTY_STRING;
	int itter;

	vector<string> aln = Get_ALN();
	if(aln.size() == 4) {
		if(aln[0] == logName || (aln[2] == "0" && aln[1] == logName)) {
			itter = atoi(aln[2].c_str()) + 1;
			coreName = aln[1];
			rName = coreName + ROTATE_EXTEN + std::to_string(itter);
		}
	}

	if(rName != EMPTY_STRING) {
		Set_ALN(rName, itter);
	}
}

//get a valid log anem with respect to size and time
string Get_ValidLogName(string lname) {

	return EMPTY_STRING;
}