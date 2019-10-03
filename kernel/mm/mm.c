#include <os/mm.h>

ptr_t memCurr = FREEMEM;

ptr_t allocPage(int numPage)
{
    // align PAGE_SIZE
    memCurr = ROUND(memCurr, PAGE_SIZE) + numPage * PAGE_SIZE;
    return memCurr;
}

void* kmalloc(size_t size)
{
    ptr_t ret = ROUND(memCurr, 4);
    memCurr = ret + size;
    return (void*)ret;
}
