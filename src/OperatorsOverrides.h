#ifndef OperatorsOverrides_H
#define OperatorsOverrides_H

#include <iostream>

namespace OperatorsOverrides
{
	class ComplexNum
	{
		int _realNum;
		int _imgNum;

	public:

		ComplexNum( int real, int img );

		int getReal() const;
		int getImg() const;

		friend std::ostream& operator<< ( std::ostream& os,  const ComplexNum& obj );

		operator int();

		bool operator==(const ComplexNum& obj );
		
	};



	void example();

}


#endif