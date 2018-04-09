# LoggerLib
A Logger lib build in C++, platform independent, thread safe

# srcLoggerLib consist the src code.
- Implemented a logger in C++ which will be consumed by platform independent application.
- Supports multithreads/ thread safe API's
- Supports log file rotation by filesize/ by timelapse
- Configuration by custamized '='parser
 # Tester
  - LoggerTester.cpp will do load test
  - Used for testing Logger directly (not as lib.)
  - this will calculate and show the perfomance data dynamically with respect to load

# Targets
- design review
- code review
- cout and printf system operator overloading 
- lib exportor
- supports to linux and win dll
- optimization
- improve the load tester
- improve the library tester

# betaReleases/06_Sep_2016
- contains release LoggerLib.lib
- supports windows

# TestLoggerLib
- A C++ test console project to test the LoggetLib.lib
