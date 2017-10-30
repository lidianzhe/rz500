#ifndef ENTITIES_H
#define ENTITIES_H
#include <iostream>
#include "umxCommonLib/umxCommonGlobal.h"

using namespace std;
class Entities
{
public:
    Entities();
};

struct Person{
    std::string Id;
    std::string Name;
    std::string Card;
    int LeftEyeScore;
    int RightEyeScore;
};

#endif // ENTITIES_H
