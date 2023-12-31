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
    int (*getByteLength)(struct DynamicText** element, int* errorNumber, char* filename, int lineNumber);
    int64_t (*getUtf8Length)(struct DynamicText** element, int* errorNumber, char* filename, int lineNumber);
    void (*resize)(struct DynamicText** element, int newSize, int* errorNumber, char* filename, int lineNumber);
    void (*set)(struct DynamicText** element, char* text, int* errorNumber, char* filename, int lineNumber);
};


void appendDynamicText(struct DynamicText** element, char* text, int* errorNumber, char* filename, int lineNumber);
void freeDynamicText(struct DynamicText** element, int* errorNumber, char* filename, int lineNumber);
char* getBytesPointerFromDynamicText(struct DynamicText** element, int* errorNumber);
int getByteLengthFromDynamicText(struct DynamicText** element, int* errorNumber, char* filename, int lineNumber);
int64_t getUtf8LengthFromDynamicText(struct DynamicText** element, int* errorNumber, char* filename, int lineNumber);
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
    element->getByteLength = &getByteLengthFromDynamicText;
    element->getUtf8Length = &getUtf8LengthFromDynamicText;
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
        maxLengthForCopy += maxLengthForCopy / 2;

        /* There is a limit for maximum amount of allocated text. */
        if (maxLengthForCopy > (*element)->maxAmountOfBytes)
        {
            appendMessageToErrorLog("New amount for dynamic text would be greater than the allowed maximum amount of bytes!", __func__, filename, lineNumber);
            *errorNumber = 2030;

            return;
        }

        (*element)->resize(element, maxLengthForCopy, errorNumber, filename, lineNumber);
    }

    customStrncat((*element)->bytes, text, customStrlen(text, errorNumber));

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
        (*element)->set(element, "", errorNumber, filename, lineNumber);

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
getByteLengthFromDynamicText(struct DynamicText** element, int* errorNumber, char* filename, int lineNumber)
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

    int64_t length = customStrlen((*element)->bytes, errorNumber);

    if (*errorNumber)
    {
        appendMessageToErrorLog("Problem with text length from strlen function!", __func__, filename, lineNumber);
        *errorNumber = 4020;

        return -1;
    }

    *errorNumber = 0;

    return length;
}


int64_t
getUtf8LengthFromDynamicText(struct DynamicText** element, int* errorNumber, char* filename, int lineNumber)
{
    if (NULL == element)
    {
        appendMessageToErrorLog("Parameter \"element\" is NULL!", __func__, filename, lineNumber);
        *errorNumber = 8000;

        return -1;
    }

    if (NULL == (*element))
    {
        appendMessageToErrorLog("Pointer \"element\" is NULL!", __func__, filename, lineNumber);
        *errorNumber = 8010;

        return -1;
    }

    int64_t counter = 0;
    int64_t length = (*element)->getByteLength(element, errorNumber, filename, lineNumber);
    char* text = (*element)->bytes;

    for (int i = 0; i < length; i++)
    {
        if (((text[i]) & 0xC0) != 0x80)
        {
            counter++;
        }
    }

    *errorNumber = 0;

    return counter;
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
    int64_t startIndex = (*element)->getByteLength(element, errorNumber, filename, lineNumber);
    for (int i = startIndex; i < newSize; i++)
    {
        (*element)->bytes[i] = '\0';
    }

    (*element)->amountOfBytes = newSize;

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
        maxLengthForCopy += (maxLengthForCopy / 2);

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
