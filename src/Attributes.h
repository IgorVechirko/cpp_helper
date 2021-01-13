#ifndef Attributes_H
#define Attributes_H

namespace Attributes
{
    [[ deprecated ]] void deprecatedFunc();
    [[deprecated( "reasone because deprecated" ) ]] void deprecatedFuncWithReasone();
    [[maybe_unused]] int funcWithUnusedVars();

    void example();

}

#endif