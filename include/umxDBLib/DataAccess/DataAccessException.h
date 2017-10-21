/**************************************************************************************************\

	Author:		Ralph
	Created:	08.04.2014

---------------------------------------------------------------------------------------------------

	Copyright (c) 2014 Smartsensors Ltd.

\**************************************************************************************************/

#ifndef __DATA_ACCESS_EXCEPTION_H__
#define __DATA_ACCESS_EXCEPTION_H__

#include <exception>
#include <string>

class DataAccessException : public std::exception
{
public:
    DataAccessException(const std::string& exception) throw()
        : _exception(exception){};
    virtual ~DataAccessException() throw(){};
    virtual const char* what() const throw()
    {
        return _exception.c_str();
    };
private:
    DataAccessException() throw(){};
    std::string _exception;
};

#endif // __DATA_ACCESS_EXCEPTION_H__
