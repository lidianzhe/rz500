/**************************************************************************************************\

	Author:		Ralph
	Created:	03.04.2014

---------------------------------------------------------------------------------------------------

	Copyright (c) 2014 Smartsensors Ltd.

\**************************************************************************************************/

#ifndef __DATA_ACCESS_H__
#define __DATA_ACCESS_H__

#include <string> //EF-45(unklee88)-20 : moved DataCache -> umxNetLib/DataAccess/

class DataAccess
{
public:
    enum {MAGIC_ID = (u_int32_t)(0xCDC3C9C6)}; //EF-45(unklee88)-20 : moved DataCache -> umxNetLib/DataAccess/

    DataAccess();
    virtual ~DataAccess();
};

#endif // __DATA_ACCESS_H__
