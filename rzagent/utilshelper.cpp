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

QByteArray utilsHelper::QString2Hex(QString str)
{
    QByteArray senddata;
  int hexdata,lowhexdata;
    int hexdatalen = 0;
         int len = str.length();
   senddata.resize(len/2);
     char lstr,hstr;
   for(int i=0; i<len; )
   {
      hstr=str[i].toAscii();
     if(hstr == ' ')
     {
       i++;
       continue;
     }
     i++;
     if(i >= len)
         break;
     lstr = str[i].toAscii();
      hexdata = ConvertHexChar(hstr);
     lowhexdata = ConvertHexChar(lstr);
      if((hexdata == 16) || (lowhexdata == 16))
        break;
     else
       hexdata = hexdata*16+lowhexdata;
      i++;
      senddata[hexdatalen] = (char)hexdata;
      hexdatalen++;
   }
    senddata.resize(hexdatalen);
      return senddata;
}


char utilsHelper::ConvertHexChar(char ch)
{
  if((ch >= '0') && (ch <= '9'))
      return ch-0x30;
 else if((ch >= 'A') && (ch <= 'F'))
   return ch-'A'+10;
 else if((ch >= 'a') && (ch <= 'f'))
   return ch-'a'+10;
  else return (-1);
}
