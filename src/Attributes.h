#ifndef Attributes_H
#define Attributes_H

#include "CommonInclude.h"

namespace Attributes
{

    [[ deprecated ]] void deprecatedFunc()
    {
        LOGOUT_FUNC
    }

    [[depracated( "reasone because deprecated" ) ]] void deprecatedFuncWithReasone()
    {
        LOGOUT_FUNC
    }

    [[maybe_unused]] int funcWithUnusedVars()
    {
        int a = 1; 
        int b = 2;
        int unusedVar = a+b;
        int d = b-a;
        return d;
    }


    void example()
    {
        deprecatedFunc();
        deprecatedFuncWithReasone();
        funcWithUnusedVars();
    }

}



#endif