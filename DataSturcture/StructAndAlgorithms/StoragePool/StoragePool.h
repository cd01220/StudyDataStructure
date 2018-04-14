#ifndef _STORAGEPOOL_H_
#define _STORAGEPOOL_H_

#include <stdlib.h>
#include <malloc.h>
class StoragePool
{
public:
    virtual ~StoragePool (){;}
    virtual void* Acquire (size_t) = 0;
    virtual void Release (void*) = 0;
};

struct Tag
{
    StoragePool* pool;
};

void* operator new (size_t bytes, StoragePool& p)
{
    Tag* const tag = reinterpret_cast<Tag*> (
        p.Acquire (bytes + sizeof (Tag)));
    tag->pool = &p;
    return tag + 1;
}

void* operator new (size_t bytes)
{
    Tag* const tag = reinterpret_cast<Tag*> (std::malloc (bytes + sizeof (Tag)));
    tag->pool = 0;
    return tag + 1;
}

void operator delete (void* arg)
{
    Tag* const tag = reinterpret_cast<Tag*> (arg) - 1U;
    if (tag->pool)
        tag->pool->Release (tag);
    else
        std::free (tag);
}

class SinglyLinkedPool : public StoragePool
{
public:
    struct Header
    {
        unsigned int length;
    };
    struct Block : public Header
    {
        enum { size = 16 };
        union
        {
            Block* next;
            char userPart [size - sizeof (Header)];
        };
    };
private:
    unsigned int numberOfBlocks;
    Block* pool;
    Block& sentinel;
public:
    SinglyLinkedPool (size_t);
    ~SinglyLinkedPool ();

    void* Acquire (size_t);
    void Release (void*);
};

SinglyLinkedPool::SinglyLinkedPool (size_t n) :
numberOfBlocks ((n + sizeof (Block) - 1U) / sizeof (Block)),
pool (new Block [numberOfBlocks + 1]),
sentinel (pool [numberOfBlocks])
{
    //int a = sizeof(Block::size);
    //int b = sizeof(Header);
    Block& head = pool [0];
    head.length = numberOfBlocks;
    head.next = 0;

    sentinel.length = 0;
    sentinel.next = &head;
}

SinglyLinkedPool::~SinglyLinkedPool ()
{ 
    delete[] pool; 
}

void* SinglyLinkedPool::Acquire (size_t bytes)
{
    unsigned int const blocks =
        (bytes + sizeof (Header) + sizeof (Block) - 1U) /
        sizeof (Block);

    Block* prevPtr = &sentinel;
    Block* ptr = prevPtr->next;
    while (ptr != 0 && ptr->length < blocks)
    {
        prevPtr = ptr;
        ptr = ptr->next;
    }

    if (ptr->length > blocks)
    {
        Block& newBlock = ptr [blocks];
        newBlock.length = ptr->length - blocks;
        newBlock.next = ptr->next;
        ptr->length = blocks;
        ptr->next = &newBlock;
    }
    prevPtr->next = ptr->next;
    return ptr->userPart;
}

void SinglyLinkedPool::Release (void* arg)
{
    Block& block = *reinterpret_cast<Block*> (
        reinterpret_cast<Header*> (arg) - 1U);

    if (&block < pool || &block >= pool + numberOfBlocks)
        throw invalid_argument ("invalid block");

    Block* prevPtr = &sentinel;
    Block* ptr = prevPtr->next;
    while (ptr != 0 && ptr < &block)
    {
        prevPtr = ptr;
        ptr = ptr->next;
    }
    if (ptr != 0 && &block + block.length == ptr)
    {
        block.length += ptr->length;
        block.next = ptr->next;
    }
    else
        block.next = ptr;
    if (prevPtr + prevPtr->length == &block)
    {
        prevPtr->length += block.length;
        prevPtr->next = block.next;
    } 
    else
        prevPtr->next = &block;
}


#endif //#ifndef _STORAGEPOOL_H_