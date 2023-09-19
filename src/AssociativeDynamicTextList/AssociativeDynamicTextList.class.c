
struct AssociativeDynamicTextList {
    struct associativeDynamicTextListElement* element;

    /* Function pointers for pseudo OOP in C. */
    void (*addElement)(struct AssociativeDynamicTextList** list, char* textForKey, char* textForValue, int* errorNumber, char* filename, int lineNumber);
    int (*countElements)(struct AssociativeDynamicTextList** list, int* errorNumber, char* filename, int lineNumber);
    void (*free)(struct AssociativeDynamicTextList** list, int* errorNumber, char* filename, int lineNumber);
    struct AssociativeDynamicText* (*getElement)(struct AssociativeDynamicTextList** list, char* key, int* errorNumber, char* filename, int lineNumber);
    int (*isEmpty)(struct AssociativeDynamicTextList** list, int* errorNumber, char* filename, int lineNumber);
    int (*isKeyExisting)(struct AssociativeDynamicTextList** list, char* textForKey, int* errorNumber, char* filename, int lineNumber);
};

struct associativeDynamicTextListElement {
    struct AssociativeDynamicText* item;
    struct associativeDynamicTextListElement* next;
};


void addElementByKeyInAssociativeDynamicTextList(struct AssociativeDynamicTextList** list, char* textForKey, char* textForValue, int* errorNumber, char* filename, int lineNumber);
int countElementsInAssociativeDynamicTextList(struct AssociativeDynamicTextList** list, int* errorNumber, char* filename, int lineNumber);
void freeAssociativeDynamicTextList(struct AssociativeDynamicTextList** list, int* errorNumber, char* filename, int lineNumber);
struct AssociativeDynamicText* getElementByKeyFromAssociativeDynamicTextList(struct AssociativeDynamicTextList** list, char* key, int* errorNumber, char* filename, int lineNumber);
int isEmptyForAssociativeDynamicTextList(struct AssociativeDynamicTextList** list, int* errorNumber, char* filename, int lineNumber);
int isKeyExistingInAssociativeDynamicTextList(struct AssociativeDynamicTextList** list, char* textForKey, int* errorNumber, char* filename, int lineNumber);


struct AssociativeDynamicTextList*
allocateAssociativeDynamicTextList(int* errorNumber, char* filename, int lineNumber)
{
    struct AssociativeDynamicTextList* list = customMalloc(1 * sizeof(struct AssociativeDynamicTextList));

    if (NULL == list)
    {
        appendMessageToErrorLog("NULL pointer as return value from function malloc()!", __func__, filename, lineNumber);
        *errorNumber = 1000;

        return NULL;
    }

    list->element = NULL;

    /* Function pointers for pseudo OOP in C. */
    list->addElement = &addElementByKeyInAssociativeDynamicTextList;
    list->free = &freeAssociativeDynamicTextList;
    list->countElements = &countElementsInAssociativeDynamicTextList;
    list->getElement = &getElementByKeyFromAssociativeDynamicTextList;
    list->isEmpty = &isEmptyForAssociativeDynamicTextList;
    list->isKeyExisting = &isKeyExistingInAssociativeDynamicTextList;

    *errorNumber = 0;

    return list;
}


void
addElementByKeyInAssociativeDynamicTextList(
    struct AssociativeDynamicTextList** list,
    char* textForKey,
    char* textForValue,
    int* errorNumber,
    char* filename,
    int lineNumber
)
{
    if (NULL == list)
    {
        appendMessageToErrorLog("List variable is NULL!", __func__, filename, lineNumber);
        *errorNumber = 2000;

        return;
    }

    if (NULL == (*list))
    {
        appendMessageToErrorLog("List pointer is NULL!", __func__, filename, lineNumber);
        *errorNumber = 2010;

        return;
    }

    if (NULL == textForKey)
    {
        appendMessageToErrorLog("Pointer for key is NULL!", __func__, filename, lineNumber);
        *errorNumber = 2020;

        return;
    }

    if (0 == customStrlen(textForKey, errorNumber))
    {
        appendMessageToErrorLog("Key variable is empty!", __func__, filename, lineNumber);
        *errorNumber = 2030;

        return;
    }

    if (NULL == textForValue)
    {
        appendMessageToErrorLog("Pointer for value is NULL!", __func__, filename, lineNumber);
        *errorNumber = 2040;

        return;
    }

    if (NULL == (*list)->element)
    {
        struct associativeDynamicTextListElement* listElement = customMalloc(1 * sizeof(struct associativeDynamicTextListElement));

        if (NULL == listElement)
        {
            appendMessageToErrorLog("NULL pointer from malloc() on empty list()!", __func__, filename, lineNumber);
            *errorNumber = 2050;

            return;
        }

        struct AssociativeDynamicText* item = allocateAssociativeDynamicTextByKey(textForKey, errorNumber, filename, lineNumber);

        item->set(&item, textForValue, errorNumber, filename, lineNumber);

        listElement->item = item;
        listElement->next = NULL;

        (*list)->element = listElement;

        *errorNumber = 0;

        return;
    }

    if (1 == (*list)->isKeyExisting(list, textForKey, errorNumber, filename, lineNumber))
    {
        appendMessageToErrorLog("Key exists and would not be unique in the list anymore!", __func__, filename, lineNumber);
        *errorNumber = 2060;

        return;
    }

    struct associativeDynamicTextListElement* bufferList = (*list)->element;

    while (NULL != bufferList->next)
    {
        bufferList = bufferList->next;
    }

    struct associativeDynamicTextListElement* listElement = customMalloc(1 * sizeof(struct associativeDynamicTextListElement));

    if (NULL == listElement)
    {
        appendMessageToErrorLog("NULL pointer from malloc() on last empty element!", __func__, filename, lineNumber);
        *errorNumber = 2070;

        return;
    }

    struct AssociativeDynamicText* item = allocateAssociativeDynamicTextByKey(textForKey, errorNumber, filename, lineNumber);

    item->set(&item, textForValue, errorNumber, filename, lineNumber);

    listElement->item = item;
    listElement->next = NULL;

    bufferList->next = listElement;

    *errorNumber = 0;
}


int
countElementsInAssociativeDynamicTextList(struct AssociativeDynamicTextList** list, int* errorNumber, char* filename, int lineNumber)
{
    if (NULL == list)
    {
        appendMessageToErrorLog("List variable is NULL!", __func__, filename, lineNumber);
        *errorNumber = 3000;

        return -1;
    }

    if (NULL == (*list))
    {
        appendMessageToErrorLog("List pointer is NULL!", __func__, filename, lineNumber);
        *errorNumber = 3010;

        return -1;
    }

    if (NULL == (*list)->element)
    {
        *errorNumber = 0;

        return 0;
    }

    struct associativeDynamicTextListElement* bufferElement = (*list)->element;

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
freeAssociativeDynamicTextList(struct AssociativeDynamicTextList** list, int* errorNumber, char* filename, int lineNumber)
{
    if (NULL == list)
    {
        appendMessageToErrorLog("List is NULL!", __func__, filename, lineNumber);
        *errorNumber = 4000;

        return;
    }

    if (NULL == (*list))
    {
        appendMessageToErrorLog("Double free on list!", __func__, filename, lineNumber);
        *errorNumber = 4010;

        return;
    }

    struct associativeDynamicTextListElement* bufferList = (*list)->element;

    while (NULL != bufferList)
    {
        struct associativeDynamicTextListElement* element = bufferList;
        struct AssociativeDynamicText* text = element->item;

        text->free(&text, errorNumber, filename, lineNumber);
        text = NULL;

        bufferList = bufferList->next;

        customFree(element, sizeof(struct associativeDynamicTextListElement));
        element = NULL;
    }

    customFree((*list), sizeof(struct AssociativeDynamicTextList));
    *list = NULL;

    *errorNumber = 0;
}


struct AssociativeDynamicText*
getElementByKeyFromAssociativeDynamicTextList(struct AssociativeDynamicTextList** list, char* key, int* errorNumber, char* filename, int lineNumber)
{
    if (NULL == list)
    {
        appendMessageToErrorLog("List variable is NULL!", __func__, filename, lineNumber);
        *errorNumber = 5000;

        return NULL;
    }

    if (NULL == (*list))
    {
        appendMessageToErrorLog("Pointer for list is NULL!", __func__, filename, lineNumber);
        *errorNumber = 5010;

        return NULL;
    }

    if (NULL == key)
    {
        appendMessageToErrorLog("Key variable is NULL!", __func__, filename, lineNumber);
        *errorNumber = 5020;

        return NULL;
    }

    if (0 == customStrlen(key, errorNumber))
    {
        appendMessageToErrorLog("Key variable is empty!", __func__, filename, lineNumber);
        *errorNumber = 5030;

        return NULL;
    }

    struct associativeDynamicTextListElement* element = (*list)->element;

    while (NULL != element)
    {
        struct AssociativeDynamicText* item = element->item;
        struct DynamicText* buffer = item->internalKey;
        char* keyFromElement = buffer->getBytesPointer(&buffer, errorNumber);

        if (isExactTextMatch(keyFromElement, key, filename, lineNumber))
        {
            break;
        }

        element = element->next;
    }

    if (NULL == element)
    {
        appendMessageToErrorLog("Key does not exists in list!", __func__, filename, lineNumber);
        *errorNumber = 5040;

        return NULL;
    }

    *errorNumber = 0;

    return element->item;
}


int
isEmptyForAssociativeDynamicTextList(struct AssociativeDynamicTextList** list, int* errorNumber, char* filename, int lineNumber)
{
    if (NULL == list)
    {
        appendMessageToErrorLog("List variable is NULL!", __func__, filename, lineNumber);
        *errorNumber = 6000;

        return -1;
    }

    if (NULL == (*list))
    {
        appendMessageToErrorLog("List pointer is NULL!", __func__, filename, lineNumber);
        *errorNumber = 6010;

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


int
isKeyExistingInAssociativeDynamicTextList(struct AssociativeDynamicTextList** list, char* textForKey, int* errorNumber, char* filename, int lineNumber)
{
    if (NULL == list)
    {
        appendMessageToErrorLog("List variable is NULL!", __func__, filename, lineNumber);
        *errorNumber = 7000;

        return -1;
    }

    if (NULL == (*list))
    {
        appendMessageToErrorLog("List pointer is NULL!", __func__, filename, lineNumber);
        *errorNumber = 7010;

        return -1;
    }

    if (NULL == textForKey)
    {
        appendMessageToErrorLog("Pointer for key is NULL!", __func__, filename, lineNumber);
        *errorNumber = 7020;

        return -1;
    }

    if (0 == customStrlen(textForKey, errorNumber))
    {
        appendMessageToErrorLog("Key variable is empty!", __func__, filename, lineNumber);
        *errorNumber = 7030;

        return -1;
    }

    if (NULL == (*list)->element)
    {
        *errorNumber = 0;

        return 0;
    }

    struct associativeDynamicTextListElement* bufferList = (*list)->element;

    while (NULL != bufferList)
    {
        struct AssociativeDynamicText* element = bufferList->item;
        struct DynamicText* text = element->internalKey;

        if (isExactTextMatch(textForKey, text->bytes, filename, lineNumber))
        {
            *errorNumber = 0;

            return 1;
        }

        bufferList = bufferList->next;
    }

    *errorNumber = 0;

    return 0;
}


/*
void
printAssociativeDynamicTextList(struct AssociativeDynamicTextList** list, int* errorNumber, char* filename, int lineNumber)
{
    if (NULL == list)
    {
        appendMessageToErrorLog("List variable is NULL!", __func__, filename, lineNumber);
        customExit(EXIT_FAILURE);
    }

    if (NULL == (*list))
    {
        printf("List is empty!\n");

        return;
    }

    struct associativeDynamicTextListElement* bufferList = (*list)->element;

    int counter = 1;
    while (NULL != bufferList)
    {
        struct AssociativeDynamicText* element = bufferList->item;
        printf("Key #%i: %s\n", counter, (*element->internalKey).bytes);
        printf("Value #%i: %s\n", counter, (*element->internalValue).bytes);
        bufferList = bufferList->next;
        counter++;
    }
}
*/
