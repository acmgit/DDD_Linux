#ifndef LOG_CPP
#define LOG_CPP

#include "Logfile.h"

// --------------------------------------------------------------------------------
CLog::CLog( const char* pszFileName )
: m_clStream( pszFileName ),
m_strFileName( pszFileName )
{
m_clStream.close();
timestamp[0] = ' ';

m_clStream.open(m_strFileName.c_str(), std::ios::out | std::ios::app );
m_clStream << "Logfile Errorcodes:" << std::endl;
m_clStream << "----------------------------" << std::endl;
m_clStream << "All ok           = " << ALLOK << std::endl;
m_clStream << "File not found   = " << FILE_NOT_FOUND << std::endl;
m_clStream << "File corrupted   = " << FILE_CORRUPT << std::endl;
m_clStream << "Memory failure   = " << MEMORY_FAILURE << std::endl;
m_clStream << "Illegal access   = " << ILLEGAL_ACCESS << std::endl;
m_clStream << "Wrong function   = " << WRONG_FUNCTION << std::endl;
m_clStream << "---------------------------" << std::endl;
m_clStream.close();

}

//------------------------------------------------------------------------------
CLog& CLog::operator<< ( const char* s )
{
m_clStream.open( m_strFileName.c_str(), std::ios::out | std::ios::app );
m_clStream << s;
m_clStream.close();

return *this;
}

//------------------------------------------------------------------------------
CLog& CLog::operator<< ( char* s )
{
m_clStream.open( m_strFileName.c_str(), std::ios::out | std::ios::app );
m_clStream << s;
m_clStream.close();

return *this;
}

//------------------------------------------------------------------------------
CLog& CLog::operator<< ( char c )
{
m_clStream.open( m_strFileName.c_str(), std::ios::out | std::ios::app );
m_clStream << c;
m_clStream.close();

return *this;
}

//------------------------------------------------------------------------------
CLog& CLog::operator<< (short n)
{
m_clStream.open( m_strFileName.c_str(), std::ios::out | std::ios::app );
m_clStream << n;
m_clStream.close();

return *this;
}

//------------------------------------------------------------------------------
CLog& CLog::operator<< (unsigned short n)
{
m_clStream.open( m_strFileName.c_str(), std::ios::out | std::ios::app );
m_clStream << n;
m_clStream.close();

return *this;
}

//------------------------------------------------------------------------------
CLog& CLog::operator<< ( int n )
{
m_clStream.open( m_strFileName.c_str(), std::ios::out | std::ios::app );
m_clStream << n;
m_clStream.close();

return *this;
}

//------------------------------------------------------------------------------
CLog& CLog::operator<< ( unsigned int n )
{
m_clStream.open( m_strFileName.c_str(), std::ios::out | std::ios::app );
m_clStream << n;
m_clStream.close();

return *this;
}

//------------------------------------------------------------------------------
CLog& CLog::operator<< ( long n )
{
m_clStream.open( m_strFileName.c_str(), std::ios::out | std::ios::app );
m_clStream << n;
m_clStream.close();

return *this;
}

//------------------------------------------------------------------------------
CLog& CLog::operator<< ( unsigned long n )
{
m_clStream.open( m_strFileName.c_str(), std::ios::out | std::ios::app );
m_clStream << n;
m_clStream.close();

return *this;
}

//------------------------------------------------------------------------------
CLog& CLog::operator<< ( float n )
{
m_clStream.open( m_strFileName.c_str(), std::ios::out | std::ios::app );
m_clStream << n;
m_clStream.close();

return *this;
}

//------------------------------------------------------------------------------
CLog& CLog::operator<< ( double n )
{
m_clStream.open( m_strFileName.c_str(), std::ios::out | std::ios::app );
m_clStream << n;
m_clStream.close();

return *this;
}

//------------------------------------------------------------------------------
CLog& CLog::operator<< ( long double n )
{
m_clStream.open( m_strFileName.c_str(), std::ios::out | std::ios::app );
m_clStream << n;
m_clStream.close();

return *this;
}

//------------------------------------------------------------------------------
CLog& CLog::operator<< ( void* n )
{
m_clStream.open( m_strFileName.c_str(), std::ios::out | std::ios::app );
m_clStream << n;
m_clStream.close();

return *this;
}

void CLog::TimeStamp()
{
    m_clStream.open( m_strFileName.c_str(), std::ios::out | std::ios::app );
    now = time(0);
    strftime(timestamp, 24, "\n<%d.%m.%Y - %H:%M:%S", localtime(&now));
    m_clStream << timestamp << "> ";
    m_clStream.close();
}

#endif

