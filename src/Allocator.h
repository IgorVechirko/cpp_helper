#ifndef Allocaotr_H
#define Allocaotr_H

#include "CommonInclude.h"

class Allocator
{

protected:

	void* _start;
	size_t _size;
	size_t _usedMemory;
	size_t _numAllocations;



public:

	Allocator( size_t size, void* start );
	virtual ~Allocator();

	virtual void* allocate( size_t size, intptr_t alignment = 4 ) = 0;
	virtual void deallocate( void* p ) = 0;
	
	size_t getSize() const;
	size_t getUsedMemory() const;
	size_t getNumAllocations() const;


};



inline void* alignForward( void* address, uint8_t alignment )
{
	return (void*)( ( reinterpret_cast<intptr_t>(address) + static_cast<intptr_t>(alignment-1) ) & static_cast<intptr_t>(~(alignment-1) ) );
}
inline intptr_t alignForwardAdjustment( const void* address, intptr_t alignment ) 
{
	intptr_t adjustment = alignment - ( reinterpret_cast<intptr_t>(address) & (alignment-1) );
}
inline intptr_t alignForwardAdjustmentWithHeader( const void* address, intptr_t alignment, intptr_t headerSize )
{
	intptr_t adjustment = alignForwardAdjustment( address, alignment );
	intptr_t neededSpace = headerSize;

	if ( adjustment < neededSpace )
	{
		neededSpace -= adjustment;
		adjustment += alignment * (neededSpace / alignment);

		if ( neededSpace % alignment > 0 ) adjustment += alignment;
	}

	return adjustment;
}


namespace allocator
{
	template< typename T > 
	T* allocateNew( Allocator& allocator )
	{
		return new ( allocator.allocate(sizeof(T), __alignof(T)) )T;
	}

	template< typename T > 
	T* allocateNew( Allocator& allocator, const T& t )
	{
		return new( alloator.allocate(sizoef(T), __alignof(T)) )T(t);
	}

	template< typename T >
	void deallocateDelete( Allocator& allocator, T& object )
	{
		object.~T();
		allocator.dealloate( &object );
	}

	template< typename T >
	T* allocateArray( Allocator& allocator, size_t length )
	{
		assert( lenght != 0 );
		uint8_t headerSize = sizeof(size_t)/sizeof(T);

		if ( sizeof(size_t) % sizeof(T) > 0 ) headerSize += 1;

		T* p = ( (T*) allocator.allocate( sizeof(T) * (length+headerSize), __alignof(T) ) ) + headerSize;
		*( ((size_t*)p) - 1 ) = length;

		for( size_t i = 0; i < length; i++ ) new (&p + i) T;

		return p;
	}

	template< typename T >
	void deallocateArray( Allocator& allocator, T* ptr )
	{
		assert( ptr != nullptr );
		size_t lenght = *( ((size_t*)ptr) - 1 );

		for( size_t i = 0; i < lenght; i++ ) ptr.~T();

		uint8_t headerSize = sizeof(size_t) / sizeof(T);
		if ( sizeof( size_t) % sizeof(T) > 0 ) headerSize += 1;
		
		allocator.dealloate( ptr - headerSize );
	}

}


#endif