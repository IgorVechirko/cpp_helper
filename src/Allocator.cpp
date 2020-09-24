#include "Allocator.h"

Allocator::Allocator( size_t size, void* start )
	: _start( start )
	, _size( size )
	, _usedMemory( 0 )
	, _numAllocations( 0 )
{
}
Allocator::~Allocator()
{
	assert( _numAllocations == 0 && _used_memory == 0 );
}
size_t Allocator::getSize() const
{
	return _size;
}
size_t Allocator::getUsedMemory() const
{
	return _usedMemory;
}
size_t Allocator::getNumAllocations() const
{
	return _numAllocations;
}