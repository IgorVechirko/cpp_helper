#include "RvalueLvalueSemantic.h"



namespace RvalueLvalueSemantic
{
		
	CopyableClass::CopyableClass()
	{
		static int memberNum = 0;
				
		memberNum++;
		member = new std::string( "class instance " + std::to_string(memberNum) );
				
		std::cout << "CopyableClass()" << std::endl;
	};
	CopyableClass::CopyableClass( const CopyableClass& copyable )
	{
		if ( copyable.member )
			member = new std::string( (*copyable.member) );
				
		std::cout << "CopyableClass( const CopyableClass& copyable )" << std::endl;
	};
	CopyableClass::CopyableClass( CopyableClass&& copyable )
	{
		if ( copyable.member )
			member = copyable.member;
				
		copyable.member = nullptr;
				
		std::cout << "CopyableClass( CopyableClass&& copyable )" << std::endl;
	}
	//when use custom move-assign operator it's necessary use custom assign operator too
	//because when executing move semantics uniform-ref can call assign or move-assing operator
	CopyableClass& CopyableClass::operator= ( const CopyableClass& copyable )
	{
		if ( member )
		{
			delete member;
			member = nullptr;
		}
				
		if ( copyable.member )
			member = new std::string( *copyable.member );
				
				
		std::cout << "operator= ( const CopyableClass& copyable )" << std::endl;
				
		return *this;
	}
	CopyableClass& CopyableClass::operator= ( CopyableClass&& copyable )
	{
		if ( member )
		{
			delete member;
			member = nullptr;
		}
				
		if ( copyable.member )
			member = copyable.member;
				
		copyable.member = nullptr;
				
		std::cout << "operator= ( CopyableClass&& copyable )" << std::endl;
				
		return *this;
	}
	CopyableClass::~CopyableClass()
	{
		delete member;
		member = nullptr;
				
		std::cout << "~CopyableClass()" << std::endl;
	};
		
	void CopyableClass::showMember() const
	{
		if ( member )
			std::cout << (*member) << std::endl;
	}
	


	CopyableClass returnLvalueFunc()
	{
		CopyableClass inst;
		return inst;
	}


	void example()
	{
		{
			CopyableClass instance;
			CopyableClass instance2( instance );
			CopyableClass instance3( std::move( CopyableClass() ) );
			
			instance.showMember();
			instance2.showMember();
			instance3.showMember();
		}
		
		{
			std::cout << "\n move in containers algorithms \n";
			
			std::vector<CopyableClass> movableCol;
			
			movableCol.resize( 2 );
			movableCol[ 0 ] = std::move( CopyableClass() );
			movableCol[ 1 ] = std::move( CopyableClass() );
			
			std::vector<CopyableClass> receivableCol;
			std::move( movableCol.begin(), movableCol.end(), std::inserter( receivableCol, receivableCol.begin() ) );
		}
		
		{
			std::cout << "\n move in const containers \n";
			
			 
			const std::vector<CopyableClass> movableConstCol = { CopyableClass(), CopyableClass() };
			
			std::vector<CopyableClass> receivableCol;
			std::move( movableConstCol.begin(), movableConstCol.end(), std::inserter( receivableCol, receivableCol.begin() ) );
		}
	}

}