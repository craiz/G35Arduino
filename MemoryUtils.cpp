
#include <Arduino.h>
#include <MemoryUtils.h>
#include <SerialPrintf.h>

#if 0

uint8_t * heapptr, * stackptr;
void check_mem()
{
  stackptr = (uint8_t *)malloc(4);          // use stackptr temporarily
  heapptr = stackptr;                     // save value of heap pointer
  free(stackptr);      // free up the memory again (sets stackptr to 0)
  stackptr =  (uint8_t *)(SP);           // save value of stack pointer
}

void printf_mem()
{
    SerialPrintf("Heap: 0x%04x\n", heapptr);
    SerialPrintf("Stack: 0x%04x\n", stackptr);
}

void memCheck()
{
    check_mem();
    printf_mem();
    SerialPrintf("Free: 0x%04x\n", freeMemory());
}

extern unsigned int __heap_start;
extern void *__brkval;

/* 
 * The free list structure as maintained by the
 * avr-libc memory allocation routines.
 */
struct __freelist {
    size_t sz;
    struct __freelist *nx;
};

/* The head of the free list structure */
extern struct __freelist *__flp;

/* Calculates the size of the free list */
int freeListSize()
{
    struct __freelist* current;
    int total = 0;
    for (current = __flp; current; current = current->nx)
    {
        total += 2; /* Add two bytes for the memory block's header  */
        total += (int) current->sz;
    }
    return total;
}

int freeMemory()
{
    int free_memory;
    if ((int)__brkval == 0)
    {
        free_memory = ((int)&free_memory) - ((int)&__heap_start);
    } 
    else
    {
        free_memory = ((int)&free_memory) - ((int)__brkval);
        free_memory += freeListSize();
    }
    return free_memory;
}

#endif

