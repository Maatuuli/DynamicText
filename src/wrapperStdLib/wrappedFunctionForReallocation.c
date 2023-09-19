
struct timespec clockStartForReallocation;
struct timespec clockEndForReallocation;
long double runtimeInMilliSecondsForReallocations = 0.0;

void*
customRealloc(void *ptr, size_t newSize, size_t oldSize)
{
	// @TODO: Custom-Funktion fehlt!
	if (-1 == clock_gettime(CLOCK_REALTIME, &clockStartForReallocation))
	{
	    // @TODO: Custom-Funktion fehlt!
	    perror("clock_gettime // end");
	    exit(EXIT_FAILURE);
	}

    globaleAmountOfReallocations++;

    globaleAmountOfAllocatedMemoryInBytes -= oldSize;
    globaleAmountOfAllocatedMemoryInBytes += newSize;

    if (globaleAmountOfAllocatedMemoryInBytes > globalePeakOfAllocatedMemoryInBytes)
    {
        globalePeakOfAllocatedMemoryInBytes = globaleAmountOfAllocatedMemoryInBytes;
    }

	void* result = realloc(ptr, newSize);

	// @TODO: Custom-Funktion fehlt!
	if (-1 == clock_gettime(CLOCK_REALTIME, &clockEndForReallocation))
	{
	    // @TODO: Custom-Funktion fehlt!
	    perror("clock_gettime // end");
	    exit(EXIT_FAILURE);
	}
	
	long double runtimeInMilliSeconds = ((long double) clockEndForReallocation.tv_nsec / 1000000.0L) + (((long double) clockEndForReallocation.tv_sec - (long double) clockStartForReallocation.tv_sec) * 1000.0L);
	runtimeInMilliSeconds -= ((long double) clockStartForReallocation.tv_nsec / 1000000.0L);
	
	runtimeInMilliSecondsForReallocations += runtimeInMilliSeconds;

    return result;
}

