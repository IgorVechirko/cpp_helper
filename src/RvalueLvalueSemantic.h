#ifndef RvalueLvalueSemantic_H
#define RvalueLvalueSemantic_H

#include "CommonInclude.h"
#include <string>
#include <vector>
#include <iterator>

namespace RvalueLvalueSemantic
{
	
	class CopyableClass
	{
		std::string* member = nullptr;
		
		
		public:
		
			CopyableClass();
			CopyableClass( const CopyableClass& copyable );
			CopyableClass( CopyableClass&& copyable ); //Fix 26439
			//when use custom move-assign operator it's necessary use custom assign operator too
			//because when executing move semantics uniform-ref can call assign or move-assing operator
			CopyableClass& operator= ( const CopyableClass& copyable );
			CopyableClass& operator= ( CopyableClass&& copyable );//Fix 26439

			virtual ~CopyableClass();
		
			void showMember() const;
	};

	void example();

}


#endif
