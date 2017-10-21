/**************************************************************************************************\

	Author:		Ralph
	Created:	03.03.2014

---------------------------------------------------------------------------------------------------

	Copyright (c) 2014 Smartsensors Ltd.

\**************************************************************************************************/

#ifndef __LOCKER_H__
#define __LOCKER_H__

#include <string>

#include "../../DataTypes/Lock.h"

class Locker
{
public:
    Lock TryLock()
    {
        if (!_lock._locked)
        {
            _lock = Lock::CreateLock();
            return _lock;
        }
        return Lock();
    }

    Lock StealLock()
    {
        _lock = Lock::CreateLock();
        return _lock;
    }

    bool Unlock(const std::string& lockUID)
    {
        bool ok = false;
        if (_lock._locked && _lock._lockUID == lockUID)
        {
            _lock._locked = false;
            ok = true;
        }
        return ok;
    }

    const bool IsLocked(const std::string& query) const
    {
        const std::string queryName = "lock_uid=";
        auto beg = query.find(queryName);
        if (beg != std::string::npos)
        {
            beg += queryName.length();
            auto end = query.find("&", beg + 1);
            std::string lockUID = query.substr(beg, end - beg);
            return _lock._locked && _lock._lockUID == lockUID;
        }
        return false;
    };
private:
    Lock _lock;
};

#endif //__LOCKER_H__
