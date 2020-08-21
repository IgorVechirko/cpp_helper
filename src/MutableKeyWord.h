#ifndef MutableKeyWord_H
#define MutableKeyWord_H

#include "CommonInclude.h"
#include <vector>

namespace MutableKeyWord
{
	float squareCalculation( const std::vector<float>& vertices )
	{
		//hard complex computing
		return 1.0f;
	}

	class Polygon
	{
		std::vector<float> _vertices;

		mutable float _cachedSquare{0.0f};

	public:

		void addVertice( float vertice )
		{
			_vertices.push_back( 1.0 );
			_cachedSquare = 0.0f;
		}

		float getSquare() const 
		{
			if ( abs(_cachedSquare) <= FLT_EPSILON )
			{
				_cachedSquare = squareCalculation( _vertices );//change mutable variable in const method
			}

			return _cachedSquare;
		}
	};

	void example()
	{
		Polygon polygon;
		polygon.addVertice( 1.0f );
		polygon.addVertice( 1.0f );
		polygon.addVertice( 1.0f );

		std::cout << "polygon square = " << polygon.getSquare() << std::endl;
	}

}


#endif