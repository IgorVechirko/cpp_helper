#ifndef Lambdas_H
#define Lambdas_H

#include "CommonInclude.h"

namespace Lambdas
{
	void example()
	{
		std::string capturedVal = "captured val";
		std::string otherVal = "other val";

		auto lambdaWithCapturedByValue = [=,&capturedVal](){
			LOGOUT_FUNC
			std::cout << "capturedVal = " << capturedVal << std::endl;
			std::cout << "other val = " << otherVal << std::endl;
		};

		auto lambdaWithCapturedByRef = [&,capturedVal](){
			LOGOUT_FUNC
			std::cout << "capturedVal = " << capturedVal << std::endl;
			std::cout << "other val = " << otherVal << std::endl;
		};

		capturedVal = "new captured val";
		otherVal = "new other val";

		lambdaWithCapturedByValue();
		lambdaWithCapturedByRef();

		auto lambdaWithArgsAndReturnType = []( auto argToReturn ) -> auto { return argToReturn; };
		std::cout << lambdaWithArgsAndReturnType( "lambdaWithArgsAndReturnType" ) << std::endl;
	}
};

#endif