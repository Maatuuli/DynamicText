
int
findPositionInDynamicText(struct DynamicText** text, char* needle, int offset, int* errorNumber, char* filename, int lineNumber)
{
    if (NULL == text)
    {
        appendMessageToErrorLog("Variable is NULL!", __func__, filename, lineNumber);
        *errorNumber = 20000;

        return -1;
    }

    if (NULL == (*text))
    {
        appendMessageToErrorLog("Pointer is NULL!", __func__, filename, lineNumber);
        *errorNumber = 20010;

        return -1;
    }

    if (NULL == needle)
    {
        appendMessageToErrorLog("Needle is NULL!", __func__, filename, lineNumber);
        *errorNumber = 20020;

        return -1;
    }

    int lengthOfNeedle = customStrlen(needle, errorNumber);
    if (0 == lengthOfNeedle)
    {
        char* message = "Text for needle is empty!";
        appendMessageToErrorLog(message, __func__, filename, lineNumber);
        *errorNumber = 20030;

        return -1;
    }

    if (offset < 0)
    {
        char* message = "Offset for start index is smaller than 0!";
        appendMessageToErrorLog(message, __func__, filename, lineNumber);
        *errorNumber = 20040;

        return -1;
    }

    int lengthOfText = (*text)->getByteLength(text, errorNumber, filename, lineNumber);
    if (0 == lengthOfText)
    {
        *errorNumber = 0;

        return -1;
    }

    if (offset >= lengthOfText)
    {
        char* message = "Offset for start index is greater-equal than length of text!";
        appendMessageToErrorLog(message, __func__, filename, lineNumber);
        *errorNumber = 20050;

        return -1;
    }

    if (lengthOfNeedle > lengthOfText)
    {
        *errorNumber = 0;

        return -1;
    }

    for (int i = offset; i < lengthOfText; i++)
    {
        if ((*text)->bytes[i] != needle[0])
        {
            continue;
        }

        int maxBytesUntilEndOfText = lengthOfText - i;
        if (maxBytesUntilEndOfText < lengthOfNeedle)
        {
            break;
        }

        int isValid = 1;

        for (int k = 0; k < lengthOfNeedle; k++)
        {
            if ((*text)->bytes[i + k] != needle[k])
            {
                isValid = 0;
            }
        }

        if (isValid)
        {

            *errorNumber = 0;

            return i;
        }
    }

    *errorNumber = 0;

    return -1;
}


void
getSubstringInBytesFromDynamicText(
    struct DynamicText** text,
    int startIndexInBytes,
    int endIndexInBytes,
    struct DynamicText** substring,
    char* filename, int lineNumber
)
{
    int errorNumber = 0;

    if (NULL == text)
    {
        appendMessageToErrorLog("Variable text is NULL!", __func__, filename, lineNumber);
        customExit(EXIT_FAILURE);
    }

    if (NULL == (*text))
    {
        appendMessageToErrorLog("Pointer for text is NULL!", __func__, filename, lineNumber);
        customExit(EXIT_FAILURE);
    }

    if (NULL == substring)
    {
        appendMessageToErrorLog("Variable for substring is NULL!", __func__, filename, lineNumber);
        customExit(EXIT_FAILURE);
    }

    if (NULL == (*substring))
    {
        appendMessageToErrorLog("Pointer for substring is NULL!", __func__, filename, lineNumber);
        customExit(EXIT_FAILURE);
    }

    if (startIndexInBytes < 0)
    {
        appendMessageToErrorLog("startIndexInBytes is smaller than 0!", __func__, filename, lineNumber);
        customExit(EXIT_FAILURE);
    }

    if (startIndexInBytes >= ((int32_t) customStrlen((*text)->bytes, &errorNumber)))
    {
        char* message = "startIndexInBytes is greater-equal than the maximum length of text!";
        appendMessageToErrorLog(message, __func__, filename, lineNumber);
        customExit(EXIT_FAILURE);
    }

    if (endIndexInBytes < startIndexInBytes)
    {
        char* message = "endIndexInBytes is smaller than startIndexInBytes!";
        appendMessageToErrorLog(message, __func__, filename, lineNumber);
        customExit(EXIT_FAILURE);
    }

    if (endIndexInBytes > ((int32_t) customStrlen((*text)->bytes, &errorNumber)))
    {
        char* message = "endIndexInBytes is greater-equal than the maximum length of text!";
        appendMessageToErrorLog(message, __func__, filename, lineNumber);
        customExit(EXIT_FAILURE);
    }

    int maxLength = endIndexInBytes - startIndexInBytes;

    if ((*substring)->amountOfBytes < maxLength)
    {
        (*substring)->resize(substring, (*text)->amountOfBytes, &errorNumber, filename, lineNumber);
    }

    /* Clearing allocated memory again for safety. */
    customMemset((*substring)->bytes, '\0', (*substring)->amountOfBytes);

    for (int i = 0; i < maxLength; i++)
    {
        (*substring)->bytes[i] = (*text)->bytes[i + startIndexInBytes];
    }

    (*substring)->bytes[(*substring)->amountOfBytes - 1] = '\0';

    /*
    if (maxLength == (*substring)->amountOfBytes)
    {
        (*substring)->bytes[(*substring)->amountOfBytes - 1] = '\0';
    }
    else
    {
        (*substring)->bytes[(*substring)->amountOfBytes - 1] = '\0';
    }
    */
}


void
explodeDynamicText(struct DynamicText** text, char* separator, struct DynamicTextList** list, char* filename, int lineNumber)
{
    int errorNumber = 0;
    int lengthOfText = (*text)->getByteLength(text, &errorNumber, filename, lineNumber);
    int lengthOfSeparator = customStrlen(separator, &errorNumber);

    if (0 == lengthOfText)
    {
        appendMessageToErrorLog("Text is empty!", __func__, filename, lineNumber);
        customExit(EXIT_FAILURE);
    }

    if (0 == lengthOfSeparator)
    {
        appendMessageToErrorLog("Separator is empty!", __func__, filename, lineNumber);
        customExit(EXIT_FAILURE);
    }

    int offset = 0;
    int bufferCounter = 0;

    struct DynamicText* var1 = allocateDynamicText(&errorNumber, filename, lineNumber);

    if (var1->amountOfBytes < (*text)->amountOfBytes)
    {
        var1->resize(&var1, (*text)->amountOfBytes, &errorNumber, filename, lineNumber);
    }

    int delay = 0;

    for (int i = offset; i < lengthOfText; i++)
    {
        if (delay > 0)
        {
            delay--;

            if ((i + 1) == lengthOfText)
            {
                (*list)->push(list, "", &errorNumber, filename, lineNumber);
                break;
            }

            continue;
        }

        if ((*text)->bytes[i] != separator[0])
        {
            var1->bytes[bufferCounter] = (*text)->bytes[i];
            bufferCounter++;

            continue;
        }

        int isValid = 1;

        for (int k = 0; k < lengthOfSeparator; k++)
        {
            if ((i + k) >= lengthOfText)
            {
                // @TODO: Do we need this assertion?
                // isValid = 0;

                break;
            }

            if ((*text)->bytes[i + k] != separator[k])
            {
                isValid = 0;
            }
        }

        if (isValid)
        {
            (*list)->push(list, var1->bytes, &errorNumber, filename, lineNumber);

            bufferCounter = 0;
            var1->set(&var1, "", &errorNumber, filename, lineNumber);

            if ((i + 1) == lengthOfText)
            {
                (*list)->push(list, "", &errorNumber, filename, lineNumber);
                break;
            }

            delay += (lengthOfSeparator - 1);

            continue;
        }

        var1->bytes[bufferCounter] = (*text)->bytes[i];
        bufferCounter++;
    }

    if (var1->getByteLength(&var1, &errorNumber, filename, lineNumber) > 0)
    {
        (*list)->push(list, var1->bytes, &errorNumber, filename, lineNumber);
        var1->set(&var1, "", &errorNumber, filename, lineNumber);
    }

    var1->free(&var1, &errorNumber, __FILE__, __LINE__);
    var1 = NULL;
}


void
implodeListForDynamicText(
    struct DynamicTextList** list,
    struct DynamicText** text,
    char* textForInsert,
    char* filename,
    int lineNumber
)
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

    if (NULL == text)
    {
        appendMessageToErrorLog("Text variable is NULL!", __func__, filename, lineNumber);
        customExit(EXIT_FAILURE);
    }

    if (NULL == (*text))
    {
        appendMessageToErrorLog("Text pointer is NULL!", __func__, filename, lineNumber);
        customExit(EXIT_FAILURE);
    }

    struct DynamicTextListElement* bufferList = (*list)->element;

    int counter = 1;
    while (NULL != bufferList)
    {
        struct DynamicText* element = bufferList->item;

        int errorNumber = 0;
        (*text)->append(text, element->getBytesPointer(&element, &errorNumber), &errorNumber, filename, lineNumber);

        if (NULL != bufferList->next)
        {
            (*text)->append(text, textForInsert, &errorNumber, filename, lineNumber);
        }

        bufferList = bufferList->next;
        counter++;
    }
}


void
stripTagsInDynamicText(struct DynamicText** element, char* filename, int lineNumber)
{
    int errorNumber = 0;
    struct DynamicText* newText = allocateDynamicText(&errorNumber, filename, lineNumber);

    if (newText->amountOfBytes < (*element)->amountOfBytes)
    {
        newText->resize(&newText, (*element)->amountOfBytes, &errorNumber, filename, lineNumber);
    }

    int length = customStrlen((*element)->bytes, &errorNumber);
    for (int i = 0; i <= (length - 1); i++)
    {
        if ('<' == (*element)->bytes[i])
        {
            newText->bytes[i] = ' ';
            continue;
        }

        if ('>' == (*element)->bytes[i])
        {
            newText->bytes[i] = ' ';
            continue;
        }

        newText->bytes[i] = (*element)->bytes[i];
    }

    newText->bytes[length - 1] = '\0';

    // @TODO: This is inefficient. How to handle it better?
    (*element)->set(element, newText->bytes, &errorNumber, filename, lineNumber);
    newText->free(&newText, &errorNumber, filename, lineNumber);
    newText = NULL;
}


void
replaceDynamicTextWithOffset(struct DynamicText** text, char* search, char* replace, int offset, char* filename, int lineNumber)
{
    int errorNumber = 0;
    if (NULL == text)
    {
        appendMessageToErrorLog("Variable for text is NULL!", __func__, filename, lineNumber);
        customExit(EXIT_FAILURE);
    }

    if (NULL == (*text))
    {
        appendMessageToErrorLog("Pointer for text is NULL!", __func__, filename, lineNumber);
        customExit(EXIT_FAILURE);
    }

    int lengthOfText = (*text)->getByteLength(text, &errorNumber, filename, lineNumber);

    if (0 == lengthOfText)
    {
        appendMessageToErrorLog("Text is empty!", __func__, filename, lineNumber);
        customExit(EXIT_FAILURE);
    }

    if (NULL == search)
    {
        appendMessageToErrorLog("Variable for search is NULL!", __func__, filename, lineNumber);
        customExit(EXIT_FAILURE);
    }

    int lengthOfSearch = customStrlen(search, &errorNumber);

    if (0 == lengthOfSearch)
    {
        appendMessageToErrorLog("Search is empty!", __func__, filename, lineNumber);
        customExit(EXIT_FAILURE);
    }

    if (NULL == replace)
    {
        appendMessageToErrorLog("Variable for replace is NULL!", __func__, filename, lineNumber);
        customExit(EXIT_FAILURE);
    }

    if (lengthOfSearch > lengthOfText)
    {
        return;
    }

    int lengthOfReplace = customStrlen(replace, &errorNumber);
    int startByteIndex = 0;
    int isTextContainingSearch = 0;

    int i = 0 + offset;

    while (i < lengthOfText)
    {
        if ((i + lengthOfSearch) > lengthOfText)
        {
            break;
        }

        /* If current byte has not the initial utf8 start code than skip. */
        if (0 != ((*text)->bytes[i] & 0x80))
        {
            if (0xC0 != ((*text)->bytes[i] & 0xC0))
            {
                i++;
                continue;
            }
        }

        if ((*text)->bytes[i] != search[0])
        {
            i++;
            continue;
        }

        int isMatching = 1;
        for (int k = 0; k < lengthOfSearch; k++)
        {
            if ((*text)->bytes[i + k] != search[k])
            {
                isMatching = 0;
            }
        }

        if (0 == isMatching)
        {
            i++;
            continue;
        }

        startByteIndex = i;
        isTextContainingSearch = 1;
        break;
    }

    if (0 == isTextContainingSearch)
    {
        return;
    }

    struct DynamicText* var1 = allocateDynamicText(&errorNumber, filename, lineNumber);

    int newSize = (*text)->amountOfBytes - lengthOfSearch + lengthOfReplace;
    if (newSize > var1->amountOfBytes)
    {
        var1->resize(&var1, newSize, &errorNumber, filename, lineNumber);
    }

    customMemcpy(var1->bytes, (*text)->bytes, startByteIndex);
    customMemcpy(&var1->bytes[startByteIndex], replace, lengthOfReplace);
    int maxLength = lengthOfText - startByteIndex - lengthOfSearch;
    customMemcpy(
        &var1->bytes[startByteIndex + lengthOfReplace],
        &(*text)->bytes[startByteIndex + lengthOfSearch],
        maxLength
    );

    (*text)->set(text, var1->bytes, &errorNumber, filename, lineNumber);
    var1->free(&var1, &errorNumber, filename, lineNumber);

    if ((*text)->getByteLength(text, &errorNumber, filename, lineNumber) > 0)
    {
        replaceDynamicTextWithOffset(
            text,
            search,
            replace,
            (startByteIndex + lengthOfReplace),
            filename,
            lineNumber
        );
    }
}


struct timespec clockStartForReplace;
struct timespec clockEndForReplace;
long double runtimeInMilliSecondsForReplaces = 0.0;
int globaleAmountOfReplaces = 0;

void
replaceDynamicText(struct DynamicText** text, char* search, char* replace, char* filename, int lineNumber)
{
    // @TODO: Custom-Funktion fehlt!
    if (-1 == clock_gettime(CLOCK_REALTIME, &clockStartForReplace))
    {
        // @TODO: Custom-Funktion fehlt!
        perror("clock_gettime // clockStartForReplace");
        exit(EXIT_FAILURE);
    }

    replaceDynamicTextWithOffset(text, search, replace, 0, filename, lineNumber);

    globaleAmountOfReplaces++;

    // @TODO: Custom-Funktion fehlt!
    if (-1 == clock_gettime(CLOCK_REALTIME, &clockEndForReplace))
    {
        // @TODO: Custom-Funktion fehlt!
        perror("clock_gettime // clockEndForReplace");
        exit(EXIT_FAILURE);
    }

    long double runtimeInMilliSeconds = ((long double) clockEndForReplace.tv_nsec / 1000000.0L) + (((long double) clockEndForReplace.tv_sec - (long double) clockStartForReplace.tv_sec) * 1000.0L);
    runtimeInMilliSeconds -= ((long double) clockStartForReplace.tv_nsec / 1000000.0L);

    runtimeInMilliSecondsForReplaces += runtimeInMilliSeconds;
}


int
convertTextIntoInteger(char* text, char* filename, int lineNumber)
{
    if (NULL == text)
    {
        appendMessageToErrorLog("Variable for text is NULL!", __func__, filename, lineNumber);
        customExit(EXIT_FAILURE);
    }

    return customStrtol(text, (char**) NULL, 10);
}


int
isExactTextMatch(char* text1, char* text2, char* filename, int lineNumber)
{
    if (NULL == text1)
    {
        appendMessageToErrorLog("Variable text1 is NULL!", __func__, filename, lineNumber);
        customExit(EXIT_FAILURE);
    }

    if (NULL == text2)
    {
        appendMessageToErrorLog("Variable text2 is NULL!", __func__, filename, lineNumber);
        customExit(EXIT_FAILURE);
    }

    int errorNumber = 0;
    int lengthOfText1 = customStrlen(text1, &errorNumber);
    int lengthOfText2 = customStrlen(text2, &errorNumber);

    if (lengthOfText1 != lengthOfText2)
    {
        return 0;
    }

    int maximumLength = lengthOfText1;

    if (lengthOfText2 < maximumLength)
    {
        maximumLength = lengthOfText2;
    }

    if (0 == customStrncmp(text1, text2, maximumLength))
    {
        return 1;
    }

    return 0;
}


int
startsWith(const char *haystack, const char *needle, char* filename, int lineNumber)
{
    if (
        (NULL == haystack)
        || (NULL == needle)
    )
    {
        return 0;
    }

    int errorNumber = 0;
    int lengthOfHaystack = customStrlen(haystack, &errorNumber);
    int lengthOfNeedle = customStrlen(needle, &errorNumber);

    if (lengthOfHaystack < lengthOfNeedle)
    {
        return 0;
    }

    return (0 == customMemcmp(haystack, needle, lengthOfNeedle));
}


int
endsWith(const char *haystack, const char *needle, char* filename, int lineNumber)
{
    if (
        (NULL == haystack)
        || (NULL == needle)
    )
    {
        return 0;
    }

    int errorNumber = 0;
    int lengthOfHaystack = customStrlen(haystack, &errorNumber);
    int lengthOfNeedle = customStrlen(needle, &errorNumber);

    if (lengthOfNeedle > lengthOfHaystack)
    {
        return 0;
    }

    return (0 == customStrncmp(haystack + lengthOfHaystack - lengthOfNeedle, needle, lengthOfNeedle));
}


void
toLower(struct DynamicText** text, char* filename, int lineNumber)
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

    struct typeForMapping mappingForUnicode[] = {
        {.from="Ä", .to="ä"},
        {.from="Ö", .to="ö"},
        {.from="Ü", .to="ü"},
        {.from="ẞ", .to="ß"},
    };

    int amountOfElements = sizeof(mappingForUnicode) / sizeof(mappingForUnicode[0]);
    for (int i = 0; i < amountOfElements; i++)
    {
        replaceDynamicText(text, mappingForUnicode[i].from, mappingForUnicode[i].to, filename, lineNumber);
    }

    struct typeForMapping mappingForAscii[] = {
        {.from="A", .to="a"},
        {.from="B", .to="b"},
        {.from="C", .to="c"},
        {.from="D", .to="d"},
        {.from="E", .to="e"},
        {.from="F", .to="f"},
        {.from="G", .to="g"},
        {.from="H", .to="h"},
        {.from="I", .to="i"},
        {.from="J", .to="j"},
        {.from="K", .to="k"},
        {.from="L", .to="l"},
        {.from="M", .to="m"},
        {.from="N", .to="n"},
        {.from="O", .to="o"},
        {.from="P", .to="p"},
        {.from="Q", .to="q"},
        {.from="R", .to="r"},
        {.from="S", .to="s"},
        {.from="T", .to="t"},
        {.from="U", .to="u"},
        {.from="V", .to="v"},
        {.from="W", .to="w"},
        {.from="X", .to="x"},
        {.from="Y", .to="y"},
        {.from="Z", .to="z"},
    };

    char* textBuffer = (*text)->getBytesPointer(text, &errorNumber);
    int length = customStrlen(textBuffer, &errorNumber);
    amountOfElements = sizeof(mappingForAscii) / sizeof(mappingForAscii[0]);

    for (int i = 0; i <= (length - 1); i++)
    {
        for (int k = 0; k < amountOfElements; k++)
        {
            if (*(mappingForAscii[k].from) == textBuffer[i])
            {
                textBuffer[i] = *(mappingForAscii[k].to);
            }
        }
    }
}
