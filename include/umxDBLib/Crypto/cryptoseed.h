#ifndef CRYPTOSEED_H
#define CRYPTOSEED_H
#include <istream>
#include "KISA_SEED_CBC.h"

class CryptoSeed
{
public:
    CryptoSeed(unsigned char* pszKey);
    CryptoSeed(long maxNumOfUsers);

    const char* getIfToIP(char *ifName) const;
    const char* getIfToMacAddress(char *ifName) const;
    void Char2Hex(unsigned char ch, char* szHex);
    void Hex2Char(char const* szHex, unsigned char& rch);
    void CharStr2HexStr(unsigned char const* pucCharStr, char* pszHexStr, int iSize);
    void HexStr2CharStr(char const* pszHexStr, unsigned char* pucCharStr, int iSize);
    std::string replaceString(std::string subject, const std::string &search, const std::string &replace);

    bool checkMAC(std::string licMac);
    std::string convertDecrypt(std::string encryptedText);
    bool checkLicense(const char* lic_path);
    int convertEncrypt(unsigned char* str, unsigned char* ret);

    int convertDecrypt4(unsigned char* str, int srcSize, unsigned char* ret);
    int convertEncrypt4(unsigned char* str, int strSize, unsigned char* ret);

private:
    long _maxNumOfUsers;
};

#endif // CRYPTOSEED_H
