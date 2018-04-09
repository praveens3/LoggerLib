/*
Name		:	LogWriter.h
Author		:	Praveen S
Description	:	de-queue the data, MakeData and WriteData
*/

#include "LogWritter.h"

//Initializing startup data, Loading ALN, Writing ALN
void LOGWRITTER::Init() {
	open();
	T_stop = true;
	line = 0;
	maxdatasize =0;
	writeCounter = 0;
	std::thread  t1(&LOGWRITTER::write, this);
	t1.detach();
}

//Thread write
void LOGWRITTER::write() {
	while(T_stop) {
		if(!writter.is_open())
			open();
		{
			std::lock_guard<mutex> pop_gaurd(mu_deque_data);
			maxdatasize = (data.size() > maxdatasize) ? data.size() : maxdatasize;
			std::for_each(data.begin(), data.end(), [=](string msg) {
				writter<< msg << ENDLINE;
				data.pop_front();
				line++;
				if(writeCounter++ > ROTATE_LOG_FOR_LINES) {
					writeCounter = 0;
					reset();
				}
			});
		}
		close();
	}
}

//close and open file, to check logname is rotated
void LOGWRITTER::reset() {
	if(writter.is_open())
		close();
	open();
}

