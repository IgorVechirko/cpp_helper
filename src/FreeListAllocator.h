#ifndef FreeListAllocator_H
#define FreeListAllocator_H

#include "Allocator.h"


class FreeListAllocator : public Allocator
{

	struct AllocationHeader
	{
		size_t size;
		intptr_t adjustment;
	};

	struct FreeBlock
	{
		size_t size;
		FreeBlock* next;
	};


	FreeBlock* _freeBlocks;


public:

	FreeListAllocator( size_t size, void* start );
	virtual ~FreeListAllocator();

	virtual void* allocate( size_t size, intptr_t alignment = 4 ) override;
	virtual void deallocate( void* p ) override;



};




#endif 
