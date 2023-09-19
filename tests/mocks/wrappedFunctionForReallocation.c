
int globaleTestingFlagForNullReallocation = 0;

void*
customRealloc(void *ptr, size_t newSize, size_t oldSize)
{
    if (1 == globaleTestingFlagForNullReallocation)
    {
        return NULL;
    }

    globaleAmountOfReallocations++;

    globaleAmountOfAllocatedMemoryInBytes -= oldSize;
    globaleAmountOfAllocatedMemoryInBytes += newSize;

    if (globaleAmountOfAllocatedMemoryInBytes > globalePeakOfAllocatedMemoryInBytes)
    {
        globalePeakOfAllocatedMemoryInBytes = globaleAmountOfAllocatedMemoryInBytes;
    }

    return realloc(ptr, newSize);
}
