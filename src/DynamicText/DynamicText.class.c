/*
The MIT License (MIT)
Copyright (c) 2021-2023 Thomas Krüger
See full details in LICENSE.txt file.
*/

struct DynamicText {
    int32_t amountOfBytes;
    char* bytes;
    int32_t minAmountOfBytes;
    int32_t maxAmountOfBytes;

    /* Function pointers for pseudo OOP in C. */
    void (*append)(struct DynamicText** element, char* text, int* errorNumber, char* filename, int lineNumber);
    void (*free)(struct DynamicText** element, int* errorNumber, char* filename, int lineNumber);
    char* (*getBytesPointer)(struct DynamicText** element, int* errorNumber);
    int (*getLength)(struct DynamicText** element, int* errorNumber, char* filename, int lineNumber);
    void (*resize)(struct DynamicText** element, int newSize, int* errorNumber, char* filename, int lineNumber);
    void (*set)(struct DynamicText** element, char* text, int* errorNumber, char* filename, int lineNumber);
};


void appendDynamicText(struct DynamicText** element, char* text, int* errorNumber, char* filename, int lineNumber);
void freeDynamicText(struct DynamicText** element, int* errorNumber, char* filename, int lineNumber);
char* getBytesPointerFromDynamicText(struct DynamicText** element, int* errorNumber);
int getLengthFromDynamicText(struct DynamicText** element, int* errorNumber, char* filename, int lineNumber);
void resizeDynamicText(struct DynamicText** element, int newSize, int* errorNumber, char* filename, int lineNumber);
void setDynamicText(struct DynamicText** element, char* text, int* errorNumber, char* filename, int lineNumber);


struct DynamicText*
allocateDynamicText(int* errorNumber, char* filename, int lineNumber)
{
    struct DynamicText* element = customMalloc(sizeof(struct DynamicText));

    if (NULL == element)
    {
        appendMessageToErrorLog("NULL pointer as return value from function malloc()!", __func__, filename, lineNumber);
        *errorNumber = 1000;

        return NULL;
    }

    element->minAmountOfBytes = 64;
    element->maxAmountOfBytes = 5 * 1024 * 1024;
    element->amountOfBytes = element->minAmountOfBytes;
    element->bytes = customMalloc(element->amountOfBytes * sizeof(char));

    /* Resolve lazy page allocation with memory clearing. */
    customMemset(element->bytes, '\0', element->amountOfBytes * sizeof(char));

    /* Function pointers for pseudo OOP in C. */
    element->append = &appendDynamicText;
    element->free = &freeDynamicText;
    element->getBytesPointer = &getBytesPointerFromDynamicText;
    element->getLength = &getLengthFromDynamicText;
    element->resize = &resizeDynamicText;
    element->set = &setDynamicText;

    *errorNumber = 0;

    return element;
}


void
appendDynamicText(struct DynamicText** element, char* text, int* errorNumber, char* filename, int lineNumber)
{
    if (NULL == element)
    {
        appendMessageToErrorLog("Parameter \"element\" is NULL!", __func__, filename, lineNumber);
        *errorNumber = 2000;

        return;
    }

    if (NULL == (*element))
    {
        appendMessageToErrorLog("Pointer \"element\" is NULL!", __func__, filename, lineNumber);
        *errorNumber = 2010;

        return;
    }

    if (NULL == text)
    {
        appendMessageToErrorLog("Parameter \"text\" is NULL!", __func__, filename, lineNumber);
        *errorNumber = 2020;

        return;
    }

    int32_t maxLengthForCopy = customStrlen((*element)->bytes, errorNumber);
    maxLengthForCopy += customStrlen(text, errorNumber);
    maxLengthForCopy += 1;

    if (maxLengthForCopy > (*element)->amountOfBytes)
    {
        int amountOfAdditionalBytes = maxLengthForCopy / 2;

        /* Increase amount of needed memory by an extra amount, to avoid inefficent byte by byte reallocations. */
        int minimumAdditionalSizeForReallocation = (*element)->minAmountOfBytes;
        if (amountOfAdditionalBytes < minimumAdditionalSizeForReallocation)
        {
            amountOfAdditionalBytes = minimumAdditionalSizeForReallocation;
        }

        maxLengthForCopy += amountOfAdditionalBytes;

        /* There is a limit for maximum amount of allocated text. */
        if (maxLengthForCopy > (*element)->maxAmountOfBytes)
        {
            appendMessageToErrorLog("New amount for dynamic text would be greater than the allowed maximum amount of bytes!", __func__, filename, lineNumber);
            *errorNumber = 2030;

            return;
        }

        (*element)->resize(element, maxLengthForCopy, errorNumber, filename, lineNumber);
    }

    customStrncat((*element)->bytes, text, (*element)->amountOfBytes - customStrlen((*element)->bytes, errorNumber));

    (*element)->bytes[(*element)->amountOfBytes - 1] = '\0';

    *errorNumber = 0;
}


void
freeDynamicText(struct DynamicText** element, int* errorNumber, char* filename, int lineNumber)
{
    if (NULL == element)
    {
        appendMessageToErrorLog("Parameter \"element\" is NULL!", __func__, filename, lineNumber);
        *errorNumber = 3000;

        return;
    }

    if (NULL == (*element))
    {
        appendMessageToErrorLog("Double free on parameter \"element\"!", __func__, filename, lineNumber);
        *errorNumber = 3010;

        return;
    }

    if (NULL != (*element)->bytes)
    {
        /* Security: Clear complete memory before freeing. */
        customMemset((*element)->bytes, '\0', (*element)->amountOfBytes);

        customFree((*element)->bytes, (*element)->amountOfBytes);
        (*element)->bytes = NULL;
    }

    (*element)->amountOfBytes = 0;

    /* Security: Clear complete memory before freeing. */
    customMemset((*element), '\0', sizeof(*element));

    customFree((*element), sizeof(struct DynamicText));
    *element = NULL;

    *errorNumber = 0;
}


char*
getBytesPointerFromDynamicText(struct DynamicText** element, int* errorNumber)
{
    if (NULL == element)
    {
        appendMessageToErrorLog("Parameter \"element\" is NULL!", __func__, __FILE__, __LINE__);
        *errorNumber = 7000;

        return NULL;
    }

    if (NULL == (*element))
    {
        appendMessageToErrorLog("Pointer \"element\" is NULL!", __func__, __FILE__, __LINE__);
        *errorNumber = 7010;

        return NULL;
    }

    *errorNumber = 0;

    return (*element)->bytes;
}


int
getLengthFromDynamicText(struct DynamicText** element, int* errorNumber, char* filename, int lineNumber)
{
    if (NULL == element)
    {
        appendMessageToErrorLog("Parameter \"element\" is NULL!", __func__, filename, lineNumber);
        *errorNumber = 4000;

        return -1;
    }

    if (NULL == (*element))
    {
        appendMessageToErrorLog("Pointer \"element\" is NULL!", __func__, filename, lineNumber);
        *errorNumber = 4010;

        return -1;
    }

    *errorNumber = 0;

    return customStrlen((*element)->bytes, errorNumber);
}


void
resizeDynamicText(struct DynamicText** element, int newSize, int* errorNumber, char* filename, int lineNumber)
{
    if (NULL == element)
    {
        appendMessageToErrorLog("Parameter \"element\" is NULL!", __func__, filename, lineNumber);
        *errorNumber = 5000;

        return;
    }

    if (NULL == (*element))
    {
        appendMessageToErrorLog("Pointer \"element\" is NULL!", __func__, filename, lineNumber);
        *errorNumber = 5010;

        return;
    }

    if (newSize < (*element)->amountOfBytes)
    {
        appendMessageToErrorLog("New size is smaller than current size!", __func__, filename, lineNumber);
        *errorNumber = 5020;

        return;
    }

    if (newSize == (*element)->amountOfBytes)
    {
        appendMessageToErrorLog("New size is equal to current size!", __func__, filename, lineNumber);
        *errorNumber = 5030;

        return;
    }

    char* pointer = customRealloc((*element)->bytes, newSize * sizeof(char), (*element)->amountOfBytes);

    if (NULL == pointer)
    {
        appendMessageToErrorLog("NULL pointer was returned from realloc()!", __func__, filename, lineNumber);
        *errorNumber = 5040;

        return;
    }

    (*element)->bytes = pointer;

    /* Initialise additional bytes from new pointer with termination sign. */
    for (int i = ((*element)->amountOfBytes - 1); i < newSize; i++)
    {
        (*element)->bytes[i] = '\0';
    }

    (*element)->amountOfBytes = newSize;

    (*element)->bytes[(*element)->amountOfBytes - 1] = '\0';

    *errorNumber = 0;
}


void
setDynamicText(struct DynamicText** element, char* text, int* errorNumber, char* filename, int lineNumber)
{
    if (NULL == element)
    {
        appendMessageToErrorLog("Parameter \"element\" is NULL!", __func__, filename, lineNumber);
        *errorNumber = 6000;

        return;
    }

    if (NULL == (*element))
    {
        appendMessageToErrorLog("Pointer \"element\" is NULL!", __func__, filename, lineNumber);
        *errorNumber = 6010;

        return;
    }

    if (NULL == text)
    {
        appendMessageToErrorLog("Parameter \"text\" is NULL!", __func__, filename, lineNumber);
        *errorNumber = 6020;

        return;
    }

    int maxLengthForCopy = customStrlen(text, errorNumber);
    maxLengthForCopy += 1;

    if (maxLengthForCopy > (*element)->amountOfBytes)
    {
        int amountOfAdditionalBytes = (*element)->amountOfBytes / 2;

        /* Increase amount of needed memory by an extra amount, to avoid inefficent byte by byte reallocations. */
        int minimumAdditionalSizeForReallocation = (*element)->minAmountOfBytes;
        if (amountOfAdditionalBytes < minimumAdditionalSizeForReallocation)
        {
            amountOfAdditionalBytes = minimumAdditionalSizeForReallocation;
        }

        maxLengthForCopy += amountOfAdditionalBytes;

        /* We want to set up a maximum amount of allocated text. */
        if (maxLengthForCopy > (*element)->maxAmountOfBytes)
        {
            appendMessageToErrorLog("New amount for dynamic text would be greater than the allowed maximum amount of bytes!", __func__, filename, lineNumber);
            *errorNumber = 6030;

            return;
        }

        (*element)->resize(element, maxLengthForCopy, errorNumber, filename, lineNumber);
    }

    /* Security: Again clearing allocated memory for next usage. */
    customMemset((*element)->bytes, '\0', (*element)->amountOfBytes);

    customStrncpy((*element)->bytes, text, (*element)->amountOfBytes - 1);

    (*element)->bytes[(*element)->amountOfBytes - 1] = '\0';

    *errorNumber = 0;
}
