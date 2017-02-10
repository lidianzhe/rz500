/**************************************************************************************************\

	Author:		Ralph
	Created:	28.04.2014

---------------------------------------------------------------------------------------------------

	Copyright (c) 2014 Smartsensors Ltd.

\**************************************************************************************************/

#ifndef __JSON_HELPER_H__
#define __JSON_HELPER_H__

#include <iostream>
#include "umxCommonLib/cjson/cJSONpp.h"

template <typename T>
T get(cjsonpp::JSONObject obj, const char* name, const T defaultValue)
{
    T value = defaultValue;
    try
    {
        value = obj.get<T>(name);
    }
    catch(const cjsonpp::JSONError&)
    {
        //std::cout << "Caught JSONError for name " << name << std::endl;
    }
}

#endif // __JSON_HELPER_H__
