
static void
abortTestWithErrorMessage(char* titleFromTest, const char* functionName, char* filename, int lineNumber)
{
    printf("[FAILED] %s\n", titleFromTest);
    printf("globaleAmountOfAllocations: %d\n", globaleAmountOfAllocations);
    printf("globaleAmountOfReallocations: %d\n", globaleAmountOfReallocations);
    printf("globaleAmountOfFrees: %d\n", globaleAmountOfFrees);
    printf("ABORTED in function \"%s\" in file: \"%s\" on line: %d!\n", functionName, filename, lineNumber);

    customExit(EXIT_FAILURE);
}


void
checkIfUnusedMemoryIsSetUpAsZero(char* titleFromTest, struct DynamicText** text, char* filename, int lineNumber)
{
    int errorNumber = 0;

    int valueForStart = (*text)->getByteLength(text, &errorNumber, filename, lineNumber);

    for (int i = valueForStart; i <= ((*text)->amountOfBytes - 1); i++)
    {
        if ('\0' == (*text)->bytes[i])
        {
            continue;
        }

        abortTestWithErrorMessage(titleFromTest, __func__, filename, lineNumber);
    }
}

