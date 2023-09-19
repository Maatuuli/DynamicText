/*
The MIT License (MIT)
Copyright (c) 2021-2023 Thomas Krüger
See full details in LICENSE.txt file.
*/

struct AssociativeDynamicText {
    struct DynamicText* internalKey;
    struct DynamicText* internalValue;

    /* Function pointers for pseudo OOP in C. */
    void (*free)(struct AssociativeDynamicText** element, int* errorNumber, char* filename, int lineNumber);
    void (*set)(struct AssociativeDynamicText** element, char* text, int* errorNumber, char* filename, int lineNumber);
};


void freeAssociativeDynamicText(struct AssociativeDynamicText** element, int* errorNumber, char* filename, int lineNumber);
void setValueInAssociativeDynamicText(struct AssociativeDynamicText** element, char* text, int* errorNumber, char* filename, int lineNumber);


struct AssociativeDynamicText*
allocateAssociativeDynamicTextByKey(char* key, int* errorNumber, char* filename, int lineNumber)
{
    if (NULL == key)
    {
        appendMessageToErrorLog("Parameter \"key\" is NULL!", __func__, filename, lineNumber);
        *errorNumber = 1000;

        return NULL;
    }

    if (0 == customStrlen(key, errorNumber))
    {
        appendMessageToErrorLog("Parameter \"key\" is empty!", __func__, filename, lineNumber);
        *errorNumber = 1010;

        return NULL;
    }

    struct AssociativeDynamicText* element = customMalloc(1 * sizeof(struct AssociativeDynamicText));

    if (NULL == element)
    {
        appendMessageToErrorLog("NULL pointer as return value from function malloc()!", __func__, filename, lineNumber);
        *errorNumber = 1020;

        return NULL;
    }

    struct DynamicText* newText = allocateDynamicText(errorNumber, filename, lineNumber);
    newText->set(&newText, key, errorNumber, filename, lineNumber);
    element->internalKey = newText;

    element->internalValue = allocateDynamicText(errorNumber, filename, lineNumber);

    /* Function pointers for pseudo OOP in C. */
    element->free = &freeAssociativeDynamicText;
    element->set = &setValueInAssociativeDynamicText;

    *errorNumber = 0;

    return element;
}


void
freeAssociativeDynamicText(struct AssociativeDynamicText** element, int* errorNumber, char* filename, int lineNumber)
{
    if (NULL == element)
    {
        appendMessageToErrorLog("Parameter \"element\" is NULL!", __func__, filename, lineNumber);
        *errorNumber = 2000;

        return;
    }

    if (NULL == (*element))
    {
        appendMessageToErrorLog("Double free on Parameter \"element\"!", __func__, filename, lineNumber);
        *errorNumber = 2010;

        return;
    }

    struct DynamicText* internalKey = (*element)->internalKey;
    internalKey->free(&internalKey, errorNumber, filename, lineNumber);
    internalKey = NULL;

    struct DynamicText* internalValue = (*element)->internalValue;
    internalValue->free(&internalValue, errorNumber, filename, lineNumber);
    internalValue = NULL;

    customFree((*element), sizeof(struct AssociativeDynamicText));
    *element = NULL;

    *errorNumber = 0;
}


void
setValueInAssociativeDynamicText(struct AssociativeDynamicText** element, char* text, int* errorNumber, char* filename, int lineNumber)
{
    if (NULL == element)
    {
        appendMessageToErrorLog("Parameter \"element\" is NULL!", __func__, filename, lineNumber);
        *errorNumber = 3000;

        return;
    }

    if (NULL == (*element))
    {
        appendMessageToErrorLog("Pointer \"element\" is NULL!", __func__, filename, lineNumber);
        *errorNumber = 3010;

        return;
    }

    struct DynamicText* internalValue = (*element)->internalValue;
    internalValue->set(&internalValue, text, errorNumber, filename, lineNumber);

    *errorNumber = 0;
}
