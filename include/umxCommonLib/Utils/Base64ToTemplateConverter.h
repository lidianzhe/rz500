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
    inline void ConvertToTemplateVector( const std::string& base64Template, std::vector<unsigned char>& lTemplate )
    {
#ifndef ANDROID // need to fix - Base64Decoder
        std::istringstream is(base64Template);
        Poco::Base64Decoder decoder(is);
        std::istreambuf_iterator<char> isIt(decoder);
        int cnt = 0;
        while(isIt != std::istreambuf_iterator<char>())
        {
            lTemplate.push_back( static_cast<unsigned char>(*isIt) );
            ++isIt;
            ++cnt;
            if(cnt >= 2048) break;
        }
#endif
    }

    inline void ConvertToTemplateVectorForFace( const std::string& base64Template, std::vector<unsigned char>& lTemplate )
    {
#ifndef ANDROID // need to fix - Base64Decoder
        std::istringstream is(base64Template);
        Poco::Base64Decoder decoder(is);
        std::istreambuf_iterator<char> isIt(decoder);
        int cnt = 0;
        while(isIt != std::istreambuf_iterator<char>())
        {
            lTemplate.push_back( static_cast<unsigned char>(*isIt) );
            ++isIt;
            ++cnt;
            if(cnt >= 4096) break;
        }
#endif
    }

    inline void ConvertToTemplate( const std::string& base64Template, unsigned char* pTemplate )
    {
#ifndef ANDROID // need to fix - Base64Decoder
        std::istringstream is(base64Template);
        Poco::Base64Decoder decoder(is);
        std::istreambuf_iterator<char> isIt(decoder);
        unsigned char* pTemplateIt = pTemplate;
        std::copy(isIt, std::istreambuf_iterator<char>(), pTemplateIt);
#endif
    }

    inline void ConvertToImage( const std::string& base64Template, std::vector<unsigned char>& image )
    {
#ifndef ANDROID // need to fix - Base64Decoder
        std::istringstream is(base64Template);
        Poco::Base64Decoder decoder(is);
        std::istreambuf_iterator<char> isIt(decoder);
        while(isIt != std::istreambuf_iterator<char>())
        {
            image.push_back( static_cast<unsigned char>(*isIt) );
            ++isIt;
        }
#endif
    }
}

#endif // __BASE64_TO_TEMPLATE_CONVERTER_H__
