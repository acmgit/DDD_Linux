#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

class CLog;
extern CLog ErrorLog;

#define Log(Message) ErrorLog.TimeStamp(); \
    ErrorLog << Message; \

// --------------------------------------------------------------------------------
class CLog
{
public:

enum LogNumber
{
    ALLOK = 0,
    FILE_NOT_FOUND,
    FILE_CORRUPT,
    MEMORY_FAILURE,
    ILLEGAL_ACCESS,
    WRONG_FUNCTION

}; // LogNumber

CLog( const char* pszFileName );

CLog& operator<< ( const char* s );
CLog& operator<< ( char* s );
CLog& operator<< ( char c );
CLog& operator<< ( short n );
CLog& operator<< ( unsigned short n);
CLog& operator<< ( int n );
CLog& operator<< ( unsigned int n );
CLog& operator<< ( long n );
CLog& operator<< ( unsigned long n );
CLog& operator<< ( float n );
CLog& operator<< ( double n );
CLog& operator<< ( long double n );
CLog& operator<< ( void* n );

void TimeStamp();

private:

    time_t now;
    char timestamp[24];

    std::ofstream m_clStream;
    std::string m_strFileName;
};

#define ENDL "\n"
#endif
