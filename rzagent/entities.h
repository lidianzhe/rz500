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

struct Staff{
    std::string name;
    std::string card_no;
    std::string password;
    std::string face_feature;
    std::string left_feature;
    std::string right_feature;
    std::string create_time;
    std::string expired_time;
    std::string staff_no;
    int is_admin;
    int enable_flag;
    int verify_type;
    int bypasscard;
};

#endif // ENTITIES_H
