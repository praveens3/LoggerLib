readme

Library	:	LoggerLib
author	:	Praveen S

Windows:
1. Include Log.h to your project.
2. Add LoggerLib.lib to your project.
3. Call write function to write log.
4. Close the Logger, by calling Close function before exit.
5. Configure Log name, rotate mode, rotate size using config.txt file.

Example:

//write call is overloaded with 5 memberfunction
LOGGER::Log().write(LOGLEVEL::INFO, "started", "head2" "loger");

//must to close Logger before exit your program
LOGGER::Log().Close();