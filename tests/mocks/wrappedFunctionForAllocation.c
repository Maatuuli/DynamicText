
int globaleTestingFlagForNullAllocation = 0;

void*
customMalloc(int32_t size)
{
    if (1 == globaleTestingFlagForNullAllocation)
    {
        return NULL;
    }

    globaleAmountOfAllocations++;
    globaleAmountOfAllocatedMemoryInBytes += size;

    if (globaleAmountOfAllocatedMemoryInBytes > globalePeakOfAllocatedMemoryInBytes)
    {
        globalePeakOfAllocatedMemoryInBytes = globaleAmountOfAllocatedMemoryInBytes;
    }

    return malloc(size);
}

