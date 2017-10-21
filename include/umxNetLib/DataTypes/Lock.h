/**************************************************************************************************\

	Author:		Ralph
	Created:	29.04.2014

---------------------------------------------------------------------------------------------------

	Copyright (c) 2014 Smartsensors Ltd.

\**************************************************************************************************/

#ifndef __LOCK_H__
#define __LOCK_H__

#include <string>

struct Lock
{
    Lock();
    Lock(const std::string& lockUID);
    const std::string AsJSONString() const;
    static Lock CreateLock();

    bool _locked;
    std::string _lockUID;
};

#endif // __LOCK_H__