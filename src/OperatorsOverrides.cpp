#include "OperatorsOverrides.h"

#include "CommonInclude.h"
#include <chrono>

namespace OperatorsOverrides
{
	template<typename T, typename Y>
	std::ostream& operator<< ( std::ostream& os, const std::chrono::duration<T,Y>& duration )
	{
		os << "[ " << duration.count() << " of " << Y::num << "/" << Y::den << " ]";
		return os;
	}

	ComplexNum::ComplexNum( int real, int img )
		: _realNum(real)
		, _imgNum(img)
	{
	}

	int ComplexNum::getReal() const { return _realNum; };
	int ComplexNum::getImg() const { return _imgNum; };

	std::ostream& operator<< ( std::ostream& os,  const ComplexNum& obj )
	{
		LOGOUT_FUNC
		os << obj._realNum << " + i" << obj._imgNum;
		return os;
	}

	ComplexNum::operator int()
	{
		LOGOUT_FUNC
		return _realNum;
	}

	bool ComplexNum::operator==(const ComplexNum& obj )
	{
		LOGOUT_FUNC
		return _realNum == obj._realNum && _imgNum == obj._imgNum;
	}
		

	

	void example()
	{
		ComplexNum cmplNum( 3, 4 );
		std::cout << cmplNum << std::endl;
		int num = cmplNum;
		if( cmplNum == ComplexNum(4,3) );

		std::cout << std::chrono::nanoseconds(3) << std::endl;
	}

}