#ifndef Templates_H
#define Templates_H

#include "CommonInclude.h"
#include <vector>
#include <array>

namespace Templates
{
	//template< typename TypesPackage >
	void tempalteFunctionWithTypesPackage()
	{
		std::cout << "last function" << std::endl;
	}

	template< typename T, typename... TypesPackage >
	void tempalteFunctionWithTypesPackage(const T& firstArg, const TypesPackage&... argsPackage )
	{
		std::cout << "args count = " << sizeof...(TypesPackage) << std::endl;

		std::cout << firstArg << std::endl;
		tempalteFunctionWithTypesPackage( argsPackage... );
	}

	class BaseClass
	{
		bool _isInited{false};
		std::string _className = "BaseClass";


	protected:

		void setupClassName( const std::string& className )
		{
			_className = className;
		}

	public:

		void init()
		{
			_isInited = true;
		}

		void startUse()
		{
			if(_isInited)
			{
				std::cout << _className << " instance start used" << std::endl;
			}
		}

	};

	class ChildClass : public BaseClass
	{
		public:

			void ininWithClassName( const std::string& className )
			{
				setupClassName( "ChildClass" );
			}
	};


	template< typename ObjType, typename InitializerType, typename... InitArgsTypes >
	ObjType* createWithInitializer( InitializerType initializerPtr, const InitArgsTypes... initArgs )
	{
		ObjType* ret = new(std::nothrow) ObjType();
		
		if ( ret )
		{
			ret->init();

			if( initializerPtr )
			{
				(ret->*initializerPtr)( initArgs...);
			}
		}
		else
		{
			delete ret;
			ret = nullptr;
		}

		return ret;
	}

	

	//template alias
	template< typename T>
	class MyAllocator
	{
	};

	template<typename T>
	using MyVec = std::vector<T,MyAllocator<T>>;


	template<typename T, size_t size>
	class Vector;


	template< typename T, size_t rows, size_t columns>
	class Matrix
	{

		typedef Matrix<T,rows, columns> self_type;

		template< typename OtherType >
		using same_size_matrix = Matrix<OtherType,rows,columns>; 

		template< typename OtherType, size_t otherColumns >
		using multiplied_matrix = Matrix<OtherType,columns,otherColumns>;

	


		std::array<std::array<T,columns>, rows> _matrix;

	public:

		Matrix()
		{
		}
		Matrix( const T& initVal )
		{
			for( int i = 0; i < rows; i++ )
				for( int j = 0; j < columns; j++ )
					_matrix[i][j] = initVal;
		}
		Matrix( const self_type& other )
		{
			for( int i = 0; i < rows; i++ )
				for( int j = 0; j < columns; j++ )
					_matrix[i][j] = other._matrix[i][j];
		}
		Matrix( self_type&& other )
		{
			std::swap( _matrix, other._matrix );
		}
		virtual ~Matrix()
		{
		}

		self_type& operator=(const self_type& other )
		{
			for( int i = 0; i < rows; i++ )
				for( int j = 0; j < columns; j++ )
					_matrix[i][j] = other._matrix[i][j];

			return *this;
		}
		self_type& operator=( self_type&& other )
		{
			std::swap( _matrix, other._matrix );

			return *this;
		}
		std::array<T,columns>& operator[]( size_t rowIndx )
		{
			return _matrix[rowIndx];
		}
		const std::array<T,columns>& operator[]( size_t rowIndx ) const
		{
			return _matrix[rowIndx];
		}
		template<typename OtherType>
		self_type operator+( const same_size_matrix<OtherType>& other )
		{
			self_type result( *this );

			for( int i = 0; i < rows; i++ )
				for( int j = 0; j < columns; j++ )
					result[i][j] += other[i][j];

			return result;
		}
		template< typename OtherType, size_t otherColumns >
		Matrix<T,rows,otherColumns> operator*( const multiplied_matrix<OtherType,otherColumns>& other )
		{
			Matrix<T,rows,otherColumns> result( 0 );

			for( int i = 0; i < rows; i++ )
				for( int j = 0; j < otherColumns; j++ )
					for( int n = 0; n < columns; n++ )
						result[i][j] += _matrix[i][n]*other[n][j]; 
		

			return result;
		}
		template<typename CastedType >
		operator Matrix<CastedType,rows,columns>()
		{
			Matrix<CastedType,rows,columns> result(0);

			for( int i = 0; i < rows; i++ )
				for( int  j = 0; j > columns; j++ )
					result[i][j] = static_cast<CastedType>(_matrix[i][j]);

			return result;
		}


		template< typename OtherType, size_t vecSize >
		Matrix<T,rows,vecSize> operator*( const Vector<OtherType,vecSize>& vector )
		{
			static_assert( columns == 1 );

			Matrix<T,rows,vecSize> result( 0 );

			for( int i = 0; i < rows; i++ )
				for( int j = 0; j < vecSize; j++ )
					result[i][j] = _matrix[i][0]*vector[j]; 
		

			return result;
		}
	};



	template<typename T, size_t size>
	class Vector
	{

		typedef Vector<T,size> self_type;

		template< typename OtherType >
		using same_size_vector = Vector<OtherType, size>;

		template< typename OtherType, size_t columns>
		using multiplied_matrix = Matrix<OtherType, size, columns>;


		std::array<T,size> _vector;


	public:

		Vector()
		{
		}
		Vector( const T& initValue )
		{
			for( int i = 0; i < size; i++ )
				_vector[i] = initValue;
		}
		Vector( const self_type& other )
		{
			for( int i = 0; i < size; i++ )
				_vector[i] = other._vector[i];
		}
		Vector( self_type&& other )
		{
			std::swap( _vector, other._vector );
		}
		virtual ~Vector()
		{
		}

		self_type& operator=( const self_type& other )
		{
			for( int i = 0; i < size; i++ )
				_vector[i] = other._vector[i];

			return *this;
		}
		self_type& operator= ( self_type&& other )
		{
			std::swap( _vector, other._vector );

			return *this;
		}
		T& operator[]( size_t indx )
		{
			return _vector[indx];
		}
		const T& operator[]( size_t indx ) const
		{
			return _vector[indx];
		}
		template<typename OtherType>
		self_type operator+( const same_size_vector<OtherType>& other )
		{
			self_type result(*this);

			for( int i = 0; i < size; i++ )
				result._vector[i] += other[i];

			return result;
		}
		template<typename OtherType, size_t matrixColumns>
		Vector<T,matrixColumns> operator*( const multiplied_matrix<OtherType,matrixColumns>& matrix )
		{
			Vector<T,matrixColumns> result(0);

			for( int i = 0; i < matrixColumns; i++ )
				for( int n = 0; n < size; n++ )
					result[i] += _vector[n] * matrix[n][i];

			return result;
		}
		template<typename OtherType>
		T dot( const same_size_vector<OtherType>& other )
		{
			T result = 0;

			 for( int i = 0; i < size; i++ )
				 result += _vector[i] * other[i];

			return result;
		}
		template<typename CastedType >
		operator Vector<CastedType,size>()
		{
			Vector<CastedType,size> result(0);

			for( int i = 0; i < size; i++ )
					result[i] = static_cast<CastedType>(_vector[i]);

			return result;
		}
	};



	void example()
	{
		tempalteFunctionWithTypesPackage( "", 5, 0.054f, true );
		tempalteFunctionWithTypesPackage( 5, 0.054, true );

		auto customCreatedObj = new ChildClass();
		customCreatedObj->ininWithClassName( "ChildClass" );

		auto templateFuncCreatedObj = createWithInitializer<ChildClass>(&ChildClass::ininWithClassName, "ChildClass" );

		customCreatedObj->startUse();
		templateFuncCreatedObj->startUse();





		Matrix<int,4,4> mI(5);
		Matrix<float,4,4> mF(5);

		Matrix<long,4,4> castedMat = mI;

		auto matSum = mI + mF;
		auto matMlt = mI * mF;


		Vector<int,4> vI(4);
		Vector<float,4> vF(5);

		Vector<float,4> castedVec = vI;

		auto vecSum = vI + vF;
		auto vecMlt = vI.dot( vF );


		auto matVecMlt = vI * mF;
	
		Matrix<double,4,1> mD(4);
		auto vecMatMlt = mD * vI;
	}

};

#endif