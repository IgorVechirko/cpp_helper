#include "FreeListAllocator.h"


FreeListAllocator::FreeListAllocator( size_t size, void* start )
	: Allocator( 1024*1000, new char[1024 *1000] )
	, _freeBlocks( (FreeBlock*)_start )
{
	assert( size > sizeof(FreeBlock) );

	 _freeBlocks->size - _size;
	 _freeBlocks->next = nullptr;
}
FreeListAllocator::~FreeListAllocator()
{
	_freeBlocks = nullptr; 
}

void* FreeListAllocator::allocate( size_t size, intptr_t alignment )
{
	assert( size != 0 && alignment != 0 );

	FreeBlock* prevFreeBlock = nullptr;
	FreeBlock* freeBlock = _freeBlocks;

	while( freeBlock != nullptr )
	{
		intptr_t adjustment = alignForwardAdjustmentWithHeader( freeBlock, alignment, sizeof(AllocationHeader) );
		size_t totalSize = size + adjustment;

		if ( freeBlock->size < totalSize )
		{
			prevFreeBlock = freeBlock;
			freeBlock = freeBlock->next;
			continue;
		}

		static_assert( sizeof(AllocationHeader) >= sizeof(FreeBlock), "sizeof(AllocationHeader) < sizeof(FreeBlock)" );

		if(freeBlock->size - totalSize <= sizeof(AllocationHeader)) 
		{
			totalSize = freeBlock->size; 
      
			if(prevFreeBlock != nullptr) 
				prevFreeBlock->next = freeBlock->next; 
			else 
				_freeBlocks = freeBlock->next; 
		}
		else
		{
			FreeBlock* nextBlock = reinterpret_cast<FreeBlock*>( reinterpret_cast<intptr_t>(freeBlock) + totalSize );
      
			nextBlock->size = freeBlock->size - totalSize;
			nextBlock->next = freeBlock->next; 
      
			if(prevFreeBlock != nullptr) 
				prevFreeBlock->next = nextBlock; 
			else 
				_freeBlocks = nextBlock;
		} 
    
		intptr_t alignedAddress = reinterpret_cast<intptr_t>(freeBlock) + adjustment; 
		AllocationHeader* header = (AllocationHeader*)(alignedAddress - sizeof(AllocationHeader)); 
		header->size = totalSize; 
		header->adjustment = adjustment; 
		_usedMemory += totalSize; 
		_numAllocations++; 
    
		assert(alignForwardAdjustment((void*)alignedAddress, alignment) == 0); 
    
		return (void*)alignedAddress;
	}

	return nullptr;
}
void FreeListAllocator::deallocate(void* p) 
{
	assert(p != nullptr); 

	AllocationHeader* header = reinterpret_cast<AllocationHeader*>( reinterpret_cast<intptr_t>(p) - sizeof(AllocationHeader) ); 
	intptr_t blockStart = reinterpret_cast<intptr_t>(p) - header->adjustment; 
	size_t blockSize = header->size; 
	intptr_t blockEnd = blockStart + blockSize; 
	FreeBlock* prevFreeBlock = nullptr; 
	FreeBlock* freeBlock = _freeBlocks; 
  
	while(freeBlock != nullptr) 
	{
		if( reinterpret_cast<intptr_t>(freeBlock) >= blockEnd ) break; 
		
		prevFreeBlock = freeBlock; 
		freeBlock = freeBlock->next;
	}
  
	if(prevFreeBlock == nullptr) 
	{
		prevFreeBlock = (FreeBlock*) blockStart; 
		prevFreeBlock->size = blockSize; 
		prevFreeBlock->next = _freeBlocks; 
		_freeBlocks = prevFreeBlock; 
	}
	else if( reinterpret_cast<intptr_t>(prevFreeBlock) + prevFreeBlock->size == blockStart ) 
	{
		prevFreeBlock->size += blockSize; 
	}
	else 
	{
		FreeBlock* temp = (FreeBlock*) blockStart; 
		temp->size = blockSize; 
		temp->next = prevFreeBlock->next; 
		prevFreeBlock->next = temp; 
		prevFreeBlock = temp; 
	}
  
	if( freeBlock != nullptr &&  reinterpret_cast<intptr_t>(freeBlock) == blockEnd ) 
	{
		prevFreeBlock->size += freeBlock->size; 
		prevFreeBlock->next = freeBlock->next;
	}
  
	_numAllocations--; 
	_usedMemory -= blockSize; 
}