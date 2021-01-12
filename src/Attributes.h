#ifndef Attributes_H
#define Attributes_H

#include "CommonInclude.h"

namespace Attributes
{
    [[ deprecated ]] void deprecatedFunc();
    [[deprecated( "reasone because deprecated" ) ]] void deprecatedFuncWithReasone();
    [[maybe_unused]] int funcWithUnusedVars();

    void example();

}

#endif