/*
The MIT License (MIT)
Copyright (c) 2021-2023 Thomas Krüger
See full details in LICENSE.txt file.
*/

struct DynamicTextList {
    struct DynamicTextListElement* element;

    /* Function pointers for pseudo OOP in C. */
    int (*countElements)(struct DynamicTextList** list, int* errorNumber, char* filename, int lineNumber);
    void (*free)(struct DynamicTextList** list, int* errorNumber, char* filename, int lineNumber);
    struct DynamicText* (*getElementByIndex)(struct DynamicTextList** list, int index, int* errorNumber, char* filename, int lineNumber);
    int (*isEmpty)(struct DynamicTextList** list, int* errorNumber, char* filename, int lineNumber);
    void (*push)(struct DynamicTextList** list, char* text, int* errorNumber, char* filename, int lineNumber);
};

struct DynamicTextListElement {
    struct DynamicText* item;
    struct DynamicTextListElement* next;
};


int countElementsInDynamicTextList(struct DynamicTextList** list, int* errorNumber, char* filename, int lineNumber);
void freeDynamicTextList(struct DynamicTextList** list, int* errorNumber, char* filename, int lineNumber);
struct DynamicText* getElementByIndexFromDynamicTextList(struct DynamicTextList** list, int index, int* errorNumber, char* filename, int lineNumber);
int isEmptyForDynamicTextList(struct DynamicTextList** list, int* errorNumber, char* filename, int lineNumber);
void pushElementInDynamicTextList(struct DynamicTextList** list, char* text, int* errorNumber, char* filename, int lineNumber);


struct DynamicTextList*
allocateDynamicTextList(int* errorNumber, char* filename, int lineNumber)
{
    struct DynamicTextList* list = customMalloc(sizeof(struct DynamicTextList));

    if (NULL == list)
    {
        appendMessageToErrorLog("NULL pointer as return value from function malloc()!", __func__, filename, lineNumber);
        *errorNumber = 1000;

        return NULL;
    }

    list->element = NULL;

    /* Function pointers for pseudo OOP in C. */
    list->countElements = &countElementsInDynamicTextList;
    list->free = &freeDynamicTextList;
    list->getElementByIndex = &getElementByIndexFromDynamicTextList;
    list->isEmpty = &isEmptyForDynamicTextList;
    list->push = &pushElementInDynamicTextList;

    *errorNumber = 0;

    return list;
}


int
countElementsInDynamicTextList(struct DynamicTextList** list, int* errorNumber, char* filename, int lineNumber)
{
    if (NULL == list)
    {
        appendMessageToErrorLog("Parameter \"list\" is NULL!", __func__, filename, lineNumber);
        *errorNumber = 2000;

        return -1;
    }

    if (NULL == (*list))
    {
        appendMessageToErrorLog("Dereferenced Parameter \"list\" is NULL!", __func__, filename, lineNumber);
        *errorNumber = 2010;

        return -1;
    }

    struct DynamicTextListElement* bufferElement = (*list)->element;
    int counter = 0;
    while (NULL != bufferElement)
    {
        bufferElement = bufferElement->next;
        counter++;
    }

    *errorNumber = 0;

    return counter;
}


void
freeDynamicTextList(struct DynamicTextList** list, int* errorNumber, char* filename, int lineNumber)
{
    if (NULL == list)
    {
        appendMessageToErrorLog("Parameter \"list\" is NULL!", __func__, filename, lineNumber);
        *errorNumber = 3000;

        return;
    }

    if (NULL == (*list))
    {
        appendMessageToErrorLog("Double free on parameter \"list\" !", __func__, filename, lineNumber);
        *errorNumber = 3010;

        return;
    }

    struct DynamicTextListElement* bufferElement = (*list)->element;

    while (NULL != bufferElement)
    {
        struct DynamicTextListElement* element = bufferElement;
        struct DynamicText* text = element->item;

        text->free(&text, errorNumber, filename, lineNumber);
        text = NULL;

        bufferElement = bufferElement->next;

        customFree(element, sizeof(struct DynamicTextListElement));
        element = NULL;
    }

    customFree((*list), sizeof(struct DynamicTextList));
    *list = NULL;

    *errorNumber = 0;
}


struct DynamicText*
getElementByIndexFromDynamicTextList(struct DynamicTextList** list, int index, int* errorNumber, char* filename, int lineNumber)
{
    if (NULL == list)
    {
        appendMessageToErrorLog("Parameter \"list\" is NULL!", __func__, filename, lineNumber);
        *errorNumber = 4000;

        return NULL;
    }

    if (NULL == (*list))
    {
        appendMessageToErrorLog("Dereferenced parameter \"list\" is NULL!", __func__, filename, lineNumber);
        *errorNumber = 4010;

        return NULL;
    }

    if (index < 0)
    {
        appendMessageToErrorLog("Parameter \"index\" is less than 0!", __func__, filename, lineNumber);
        *errorNumber = 4020;

        return NULL;
    }

    if (index >= (*list)->countElements(list, errorNumber, filename, lineNumber))
    {
        appendMessageToErrorLog("Parameter \"index\" is greater than amount of elements!", __func__, filename, lineNumber);
        *errorNumber = 4030;

        return NULL;
    }

    struct DynamicTextListElement* bufferElement = (*list)->element;

    int counter = 0;

    do
    {
        if (counter == index)
        {
            break;
        }

        bufferElement = bufferElement->next;
        counter++;
    }
    while (NULL != bufferElement);

    *errorNumber = 0;

    return bufferElement->item;
}


int
isEmptyForDynamicTextList(struct DynamicTextList** list, int* errorNumber, char* filename, int lineNumber)
{
    if (NULL == list)
    {
        appendMessageToErrorLog("Parameter \"list\" is NULL!", __func__, filename, lineNumber);
        *errorNumber = 5000;

        return -1;
    }

    if (NULL == (*list))
    {
        appendMessageToErrorLog("Dereferenced parameter \"list\" is NULL!", __func__, filename, lineNumber);
        *errorNumber = 5010;

        return -1;
    }

    if (NULL == (*list)->element)
    {
        *errorNumber = 0;

        return 1;
    }

    *errorNumber = 0;

    return 0;
}


void
pushElementInDynamicTextList(struct DynamicTextList** list, char* text, int* errorNumber, char* filename, int lineNumber)
{
    if (NULL == list)
    {
        appendMessageToErrorLog("Parameter \"list\" is NULL!", __func__, filename, lineNumber);
        *errorNumber = 6000;

        return;
    }

    if (NULL == (*list))
    {
        appendMessageToErrorLog("Dereferenced parameter \"list\" is NULL!", __func__, filename, lineNumber);
        *errorNumber = 6010;

        return;
    }

    if (NULL == text)
    {
        appendMessageToErrorLog("Parameter \"text\" is NULL!", __func__, filename, lineNumber);
        *errorNumber = 6020;

        return;
    }

    struct DynamicTextListElement** lastElement = NULL;

    if (NULL == (*list)->element)
    {
        lastElement = &((*list)->element);
    }
    else
    {
        struct DynamicTextListElement* bufferElement = (*list)->element;

        while (NULL != bufferElement->next)
        {
            bufferElement = bufferElement->next;
        }

        lastElement = &(bufferElement->next);
    }

    struct DynamicTextListElement* listElement = customMalloc(sizeof(struct DynamicTextListElement));

    if (NULL == listElement)
    {
        appendMessageToErrorLog("NULL pointer from malloc() on last empty element!", __func__, filename, lineNumber);
        *errorNumber = 6040;

        return;
    }

    struct DynamicText* buffer = allocateDynamicText(errorNumber, filename, lineNumber);
    buffer->set(&buffer, text, errorNumber, filename, lineNumber);

    listElement->item = buffer;
    listElement->next = NULL;

    (*lastElement) = listElement;

    *errorNumber = 0;
}


/*
void
printDynamicTextList(struct DynamicTextList** list, char* filename, int lineNumber)
{
    if (NULL == list)
    {
        appendMessageToErrorLog("List variable is NULL!", __func__, filename, lineNumber);
        customExit(EXIT_FAILURE);
    }

    if (NULL == (*list))
    {
        appendMessageToErrorLog("List pointer is NULL!", __func__, filename, lineNumber);
        customExit(EXIT_FAILURE);
    }

    if (NULL == (*list)->element)
    {
        printf("List is empty!\n");

        return;
    }

    struct DynamicTextListElement* bufferElement = (*list)->element;

    int counter = 1;
    while (NULL != bufferElement)
    {
        struct DynamicText* element = bufferElement->item;
        printf("List-Element #%i: \"%s\"\n", counter, element->bytes);
        bufferElement = bufferElement->next;
        counter++;
    }
}
*/
