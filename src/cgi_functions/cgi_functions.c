
int getNumericValueFromHexadecialLetter(unsigned char hexadecialLetter, char* filename, int lineNumber);


void
convertCgiEncodingIntoNormalText(struct DynamicText** oldText, char* filename, int lineNumber)
{
    int errorNumber = 0;

    struct DynamicText* newText = allocateDynamicText(&errorNumber, filename, lineNumber);

    if (newText->amountOfBytes < (*oldText)->amountOfBytes)
    {
        newText->resize(&newText, (*oldText)->amountOfBytes, &errorNumber, filename, lineNumber);
    }

    int index = 0;
    int delayCounter = -1;
    unsigned char letterValue = 1;
    for (int i = 0; i <= ((*oldText)->amountOfBytes - 1); i++)
    {
        if (2 == delayCounter)
        {
            delayCounter = 1;
            letterValue *= getNumericValueFromHexadecialLetter((*oldText)->bytes[i], filename, lineNumber);
            letterValue *= 16;

            continue;
        }

        if (1 == delayCounter)
        {
            letterValue += getNumericValueFromHexadecialLetter((*oldText)->bytes[i], filename, lineNumber);

            newText->bytes[index] = (unsigned char) letterValue;
            index++;
            delayCounter = -1;
            letterValue = 1;

            continue;
        }

        if ('%' == (*oldText)->bytes[i])
        {
            delayCounter = 2;
            letterValue = 1;
            continue;
        }

        if ('+' == (*oldText)->bytes[i])
        {
            newText->bytes[index] = ' ';
            index++;
            continue;
        }

        newText->bytes[index] = (*oldText)->bytes[i];
        index++;
    }

    // DEBUG // TODO // WRONG???
    // index++;
    // newText->bytes[index] = '\0';

    // @TODO: This is inefficient. How to handle better?
    (*oldText)->set(oldText, newText->bytes, &errorNumber, filename, lineNumber);
    newText->free(&newText, &errorNumber, filename, lineNumber);
    newText = NULL;
}


void
convertSpecialCharsIntoHtmlCodes(struct DynamicText** text, char* filename, int lineNumber)
{
    int errorNumber = 0;
    if (0 == (*text)->getByteLength(text, &errorNumber, __FILE__, __LINE__))
    {
        return;
    }

    struct typeForMapping {
        char* from;
        char* to;
    };

    struct typeForMapping mapping[] = {
        {.from="&",  .to="&amp;"},
        {.from="\"", .to="&quot;"},
        {.from="'",  .to="&apos;"},
        {.from="<",  .to="&lt;"},
        {.from=">",  .to="&gt;"}
    };

    int amountOfElements = sizeof(mapping) / sizeof(mapping[0]);
    for (int i = 0; i < amountOfElements; i++)
    {
        replaceDynamicText(text, mapping[i].from, mapping[i].to, filename, lineNumber);
    }
}


int
getNumericValueFromHexadecialLetter(unsigned char hexadecialLetter, char* filename, int lineNumber)
{
    struct typeForMapping {
        char from;
        int to;
    };

    struct typeForMapping mapping[] = {
        {.from='0',  .to=0},
        {.from='1',  .to=1},
        {.from='2',  .to=2},
        {.from='3',  .to=3},
        {.from='4',  .to=4},
        {.from='5',  .to=5},
        {.from='6',  .to=6},
        {.from='7',  .to=7},
        {.from='8',  .to=8},
        {.from='9',  .to=9},
        {.from='A',  .to=10},
        {.from='B',  .to=11},
        {.from='C',  .to=12},
        {.from='D',  .to=13},
        {.from='E',  .to=14},
        {.from='F',  .to=15},
    };

    int amountOfElements = sizeof(mapping) / sizeof(mapping[0]);
    for (int i = 0; i < amountOfElements; i++)
    {
        if (hexadecialLetter == mapping[i].from)
        {
            return mapping[i].to;
        }
    }

    appendMessageToErrorLog("Hexadecimal value is not known!", __func__, filename, lineNumber);
    customExit(EXIT_FAILURE);

    return 0;
}


struct DynamicText*
getPostDataFromStandardInput(char* currentRequestMethod, char* filename, int lineNumber)
{
    int errorNumber = 0;
    struct DynamicText* text = allocateDynamicText(&errorNumber, filename, lineNumber);

    if (NULL == currentRequestMethod)
    {
        return text;
    }

    // @TODO: Length is static and not dynamic!
    int maximumLength = customStrlen("POST", &errorNumber);
    int length = customStrlen(currentRequestMethod, &errorNumber);

    if (length < maximumLength)
    {
        maximumLength = length;
    }

    if (0 != customStrncmp(currentRequestMethod, "POST", maximumLength))
    {
        return text;
    }

    char* len_ = customGetenv("CONTENT_LENGTH");
    int len = customStrtol(len_, NULL, 10);
    char *postdata = customMalloc((len + 1) * sizeof(char));

    if (NULL == postdata)
    {
        appendMessageToErrorLog("NULL pointer as return value from function calloc()!", __func__, filename, lineNumber);
        customExit(EXIT_FAILURE);

        return text;
    }

    /* Resolve lazy page allocation with memory clearing. */
    customMemset(postdata, '\0', (len + 1) * sizeof(char));

    if (NULL == customFgets(postdata, len + 1, stdin))
    {
        appendMessageToErrorLog("NULL pointer as return value from function fgets()!", __func__, filename, lineNumber);
        customExit(EXIT_FAILURE);

        return text;
    }

    text->set(&text, postdata, &errorNumber, filename, lineNumber);
    customFree(postdata, len + 1);
    postdata = NULL;

    return text;
}


void
initRequestParametersByEnvironmentText(struct AssociativeDynamicTextList** list, char* textFromServer, char* filename, int lineNumber)
{
    int errorNumber = 0;

    if (NULL == textFromServer)
    {
        return;
    }

    if (0 == customStrlen(textFromServer, &errorNumber))
    {
        return;
    }

    struct DynamicTextList* listForExplode = allocateDynamicTextList(&errorNumber, filename, lineNumber);
    struct DynamicText* item = allocateDynamicText(&errorNumber, filename, lineNumber);
    item->set(&item, textFromServer, &errorNumber, filename, lineNumber);
    explodeDynamicText(&item, "&", &listForExplode, filename, lineNumber);
    item->free(&item, &errorNumber, filename, lineNumber);
    item = NULL;

    int amountOfListElements = listForExplode->countElements(&listForExplode, &errorNumber, filename, lineNumber);
    for (int i = 0; i < amountOfListElements; i++)
    {
        struct DynamicText* elementFromList = listForExplode->getElementByIndex(&listForExplode, i, &errorNumber, filename, lineNumber);

        if (0 == elementFromList->getByteLength(&elementFromList, &errorNumber, __FILE__, __LINE__))
        {
            continue;
        }

        struct DynamicTextList* listForPostParameter = allocateDynamicTextList(&errorNumber, filename, lineNumber);
        explodeDynamicText(&elementFromList, "=", &listForPostParameter, filename, lineNumber);

        if (2 == listForPostParameter->countElements(&listForPostParameter, &errorNumber, filename, lineNumber))
        {
            struct DynamicText* textForKey = listForPostParameter->getElementByIndex(&listForPostParameter, 0, &errorNumber, filename, lineNumber);
            struct DynamicText* textForValue = listForPostParameter->getElementByIndex(&listForPostParameter, 1, &errorNumber, filename, lineNumber);

            convertCgiEncodingIntoNormalText(&textForKey, filename, lineNumber);
            convertCgiEncodingIntoNormalText(&textForValue, filename, lineNumber);
            stripTagsInDynamicText(&textForKey, filename, lineNumber);
            stripTagsInDynamicText(&textForValue, filename, lineNumber);

            (*list)->addElement(
                list,
                textForKey->getBytesPointer(&textForKey, &errorNumber),
                textForValue->getBytesPointer(&textForValue, &errorNumber),
                &errorNumber,
                filename,
                lineNumber
            );
        }
        else if (1 == listForPostParameter->countElements(&listForPostParameter, &errorNumber, filename, lineNumber))
        {
            struct DynamicText* textForKey = listForPostParameter->getElementByIndex(&listForPostParameter, 0, &errorNumber, filename, lineNumber);
            convertCgiEncodingIntoNormalText(&textForKey, filename, lineNumber);
            stripTagsInDynamicText(&textForKey, filename, lineNumber);

            (*list)->addElement(list, textForKey->getBytesPointer(&textForKey, &errorNumber), "", &errorNumber, filename, lineNumber);
        }
        else
        {
            appendMessageToErrorLog("Amount of parts for $_POST parameter is not between 1 and 2!", __func__, filename, lineNumber);
            customExit(EXIT_FAILURE);
        }

        listForPostParameter->free(&listForPostParameter, &errorNumber, filename, lineNumber);
        listForPostParameter = NULL;
    }

    listForExplode->free(&listForExplode, &errorNumber, filename, lineNumber);
    listForExplode = NULL;
}
