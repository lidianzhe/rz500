#include "utilshelper.h"
#include "Poco/Base64Decoder.h"
#include "Poco/Base64Encoder.h"
#include <iostream>
utilsHelper::utilsHelper()
{

}

std::string utilsHelper::BuildJSON()
{
    return "{\"Id\":3,\"UUId\":2,\"Info\":\"IrisOk\"}";
}

std::string utilsHelper::toBase64(const std::string &source)
{
    std::istringstream in(source);
    std::ostringstream out;
    Poco::Base64Encoder b64out(out);

    std::copy(std::istreambuf_iterator<char>(in),
              std::istreambuf_iterator<char>(),
              std::ostreambuf_iterator<char>(b64out));
    b64out.close(); // always call this at the end!

    return out.str();
}

std::string utilsHelper::fromBase64(const std::string &source)
{
    std::istringstream in(source);
    std::ostringstream out;
    Poco::Base64Decoder b64in(in);

    std::copy(std::istreambuf_iterator<char>(b64in),
              std::istreambuf_iterator<char>(),
              std::ostreambuf_iterator<char>(out));

    return out.str();
}
