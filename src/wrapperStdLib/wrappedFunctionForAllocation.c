
struct timespec clockStartForAllocation;
struct timespec clockEndForAllocation;
long double runtimeInMilliSecondsForAllocations = 0.0;

void*
customMalloc(size_t size)
{
	// @TODO: Custom-Funktion fehlt!
	if (-1 == clock_gettime(CLOCK_REALTIME, &clockStartForAllocation))
	{
	    // @TODO: Custom-Funktion fehlt!
	    perror("clock_gettime // clockStartForAllocation");
	    exit(EXIT_FAILURE);
	}

    globaleAmountOfAllocations++;
    globaleAmountOfAllocatedMemoryInBytes += size;

    if (globaleAmountOfAllocatedMemoryInBytes > globalePeakOfAllocatedMemoryInBytes)
    {
        globalePeakOfAllocatedMemoryInBytes = globaleAmountOfAllocatedMemoryInBytes;
    }

    if (globalePeakOfAllocatedMemoryInBytes > globaleMaxAmountOfAllocatedMemoryInBytes)
    {
        printf("[ERROR] Current memory peak is higher than allowed maximum of allocated bytes!");
        customExit(EXIT_FAILURE);
    }

	void* result = malloc(size);

	// @TODO: Custom-Funktion fehlt!
	if (-1 == clock_gettime(CLOCK_REALTIME, &clockEndForAllocation))
	{
	    // @TODO: Custom-Funktion fehlt!
	    perror("clock_gettime // clockEndForAllocation");
	    exit(EXIT_FAILURE);
	}
	
	long double runtimeInMilliSeconds = ((long double) clockEndForAllocation.tv_nsec / 1000000.0L) + (((long double) clockEndForAllocation.tv_sec - (long double) clockStartForAllocation.tv_sec) * 1000.0L);
	runtimeInMilliSeconds -= ((long double) clockStartForAllocation.tv_nsec / 1000000.0L);
	
	runtimeInMilliSecondsForAllocations += runtimeInMilliSeconds;

    return result;
}

