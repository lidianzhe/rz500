#ifndef RUNTIME_H
#define RUNTIME_H
#include "algoutils.h"
#include "umxAlgoLib/umxAlgoGlobal.h"
#include "umxDBLib/umxDBGlobal.h"
#include <iostream>
class Runtime
{
public:
    Runtime();
    AlgoUtils *algoUtils;
    UMXALGO_HANDLE umxalgo_Handle;
    UMXDB_HANDLE umxdb_Handle;
    string lock_uid;
};

extern Runtime dzrun;
#endif // RUNTIME_H
