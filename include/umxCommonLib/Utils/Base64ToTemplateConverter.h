/**************************************************************************************************\

	Author:		Ralph
	Created:	13.03.2014

---------------------------------------------------------------------------------------------------

	Copyright (c) 2014 Smartsensors Ltd.

\**************************************************************************************************/

#ifndef __BASE64_TO_TEMPLATE_CONVERTER_H__
#define __BASE64_TO_TEMPLATE_CONVERTER_H__

#include <iostream>
#include <sstream>
#include <vector>

#include <Poco/Base64Decoder.h>

namespace TemplateConverter
{
    inline void ConvertToTemplate( const std::string& base64Template, unsigned char* pTemplate )
    {
        std::istringstream is(base64Template);
        Poco::Base64Decoder decoder(is);
        std::istreambuf_iterator<char> isIt(decoder);
        unsigned char* pTemplateIt = pTemplate;
        std::copy(isIt, std::istreambuf_iterator<char>(), pTemplateIt);
    }

    inline void ConvertToImage( const std::string& base64Template, std::vector<unsigned char>& image )
    {
        std::istringstream is(base64Template);
        Poco::Base64Decoder decoder(is);
        std::istreambuf_iterator<char> isIt(decoder);
        while(isIt != std::istreambuf_iterator<char>())
        {
            image.push_back( static_cast<unsigned char>(*isIt) );
            ++isIt;
        }
    }
}

#endif // __BASE64_TO_TEMPLATE_CONVERTER_H__
