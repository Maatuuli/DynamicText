
int globaleAmountOfAllocatedMemoryInBytes = 0;
int globaleAmountOfAllocations = 0;
int globaleAmountOfFrees = 0;
int globaleAmountOfReallocations = 0;
int globaleDisableErrorLogging = 0;
int globaleMaxAmountOfAllocatedMemoryInBytes = 384 * 1024 * 1024;
int globalePeakOfAllocatedMemoryInBytes = 0;

void
customExit(int status)
{
    exit(status);
}


void
appendMessageToErrorLog(const char* message, const char* functionName, char* filename, int lineNumber)
{
    if (1 == globaleDisableErrorLogging)
    {
        return;
    }

    char textForCurrentTimestamp[256];
    time_t currentTime;
    struct tm localTimeObject;

    // @TODO: Custom-Funktion fehlt!
    currentTime = time(NULL);

    // @TODO: Custom-Funktion fehlt!
    if (NULL == localtime_r(&currentTime, &localTimeObject))
    {
        printf("[ERROR] Error during logging because localtime is NULL!");
        customExit(EXIT_FAILURE);
    }

    // @TODO: Custom-Funktion fehlt!
    if (0 == strftime(textForCurrentTimestamp, 256, "%Y-%m-%d %H:%M:%S", &localTimeObject))
    {
        printf("[ERROR] Error during writing into text with strftime and result is 0!");
        customExit(EXIT_FAILURE);
    }

    FILE* pointerForTextFile = fopen("./error.log", "a");

    if (NULL == pointerForTextFile)
    {
        printf("[ERROR] Error log does not work or exist!");
        customExit(EXIT_FAILURE);
    }

    fprintf(pointerForTextFile, "%s [ERROR] %s\n", textForCurrentTimestamp, message);
    fprintf(pointerForTextFile, "%s [ERROR] In function \"%s\".\n", textForCurrentTimestamp, functionName);
    fprintf(pointerForTextFile, "%s [ERROR] Starting point was file \"%s\" on line %i!\n", textForCurrentTimestamp, filename, lineNumber);

    if (0 != fclose(pointerForTextFile))
    {
        printf("[ERROR] Error during closing of the error logging file!");
        customExit(EXIT_FAILURE);
    }

    pointerForTextFile = NULL;
}

/*
size_t
customStrnlen(const char* str, size_t maxlen, int* errorNumber)
{
    if ('\0' != str[maxlen])
    {
        appendMessageToErrorLog("Last index in text is not terminated!", __func__, __FILE__, __LINE__);
        *errorNumber = 100010;

        return -1;
    }

    return strnlen(str, maxlen);
}
*/


size_t
// customStrlen(const char* str, int* errorNumber, char* filename, int lineNumber)
customStrlen(const char* str, int* errorNumber)
{
    if (NULL == str)
    {
        // appendMessageToErrorLog("Parameter str is NULL!", __func__, filename, lineNumber);
        appendMessageToErrorLog("Parameter str is NULL!", __func__, __FILE__, __LINE__);
        *errorNumber = 110000;

        return -1;
    }

    *errorNumber = 0;

    return strlen(str);
}


char*
customStrncpy(char* restrict destination, const char* restrict source, size_t num)
{
    strncpy(destination, source, num);
    return destination;
}


char*
customStrncat(char* restrict destination, const char* restrict source, size_t num)
{
    return strncat(destination, source, num);
}


struct timespec clockStartForFree;
struct timespec clockEndForFree;
long double runtimeInMilliSecondsForFree = 0.0;

void
customFree(void* pointer, size_t size)
{
    // @TODO: Custom-Funktion fehlt!
    if (-1 == clock_gettime(CLOCK_REALTIME, &clockStartForFree))
    {
        // @TODO: Custom-Funktion fehlt!
        perror("clock_gettime // end");
        exit(EXIT_FAILURE);
    }

    globaleAmountOfAllocatedMemoryInBytes -= size;

    if (NULL == pointer)
    {
        // @TODO: We need specific parameters for file and linenumber!
        appendMessageToErrorLog("Double free!", __func__, __FILE__, __LINE__);
        customExit(EXIT_FAILURE);
    }

    free(pointer);

    globaleAmountOfFrees++;

    // @TODO: Custom-Funktion fehlt!
    if (-1 == clock_gettime(CLOCK_REALTIME, &clockEndForFree))
    {
        // @TODO: Custom-Funktion fehlt!
        perror("clock_gettime // end");
        exit(EXIT_FAILURE);
    }

    long double runtimeInMilliSeconds = ((long double) clockEndForFree.tv_nsec / 1000000.0L) + (((long double) clockEndForFree.tv_sec - (long double) clockStartForFree.tv_sec) * 1000.0L);
    runtimeInMilliSeconds -= ((long double) clockStartForFree.tv_nsec / 1000000.0L);

    runtimeInMilliSecondsForFree += runtimeInMilliSeconds;
}


char*
customGetenv(char const* name)
{
    return getenv(name);
}


void*
customMemset(void* str, int c, size_t n)
{
    return memset(str, c, n);
}


void*
customMemcpy(void* to, const void* from, size_t numBytes)
{
    return memcpy(to, from, numBytes);
}


int
customMemcmp(const void* ptr1, const void* ptr2, size_t num)
{
    return memcmp(ptr1, ptr2, num);
}

void*
customMemmove(void* to, const void* from, size_t numBytes)
{
    return memmove(to, from, numBytes);
}

int
customStrncmp(const char* str1, const char* str2, size_t num)
{
    return strncmp(str1, str2, num);
}


long int
customStrtol(const char* str, char** endptr, int base)
{
    return strtol(str, endptr, base);
}


char*
customFgets(char* str, int n, FILE* stream)
{
    return fgets(str, n, stream);
}
