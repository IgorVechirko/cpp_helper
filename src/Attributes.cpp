#include "Attributes.h"

#include "CommonInclude.h"

namespace Attributes
{

	[[ deprecated ]] void deprecatedFunc()
    {
        LOGOUT_FUNC
    }

    [[deprecated( "reasone because deprecated" ) ]] void deprecatedFuncWithReasone()
    {
        LOGOUT_FUNC
    }

    [[maybe_unused]] int funcWithUnusedVars()
    {
        int a = 1; 
        int b = 2;
        auto c = time(nullptr);
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