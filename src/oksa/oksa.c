
void
loadTextFileIntoDynamicText(char* path, struct DynamicText** outputText, char* filename, int lineNumber)
{
    /* @TODO: Need custom wrapper for fopen()? */
    FILE* fileForHtml = fopen(path, "r");

    if (NULL == fileForHtml)
    {
        appendMessageToErrorLog("fopen() returns NULL!", __func__, filename, lineNumber);
        customExit(EXIT_FAILURE);
    }

    int nread = 0;
    struct stat st;
    /* @TODO: Need custom wrapper for stat()? */
    stat(path, &st);
    int chunksize = st.st_size + 64;
    char* buf = customMalloc(chunksize * sizeof(char));

    /* Resolve lazy page allocation with memory clearing. */
    customMemset(buf, '\0', chunksize * sizeof(char));

    while ((nread = fread(buf, 1, chunksize, fileForHtml)) > 0)
    {
        if (ferror(fileForHtml))
        {
            appendMessageToErrorLog("ferror() returns error!", __func__, filename, lineNumber);
            customExit(EXIT_FAILURE);
        }

        int errorNumber = 0;
        (*outputText)->append(outputText, buf, &errorNumber, filename, lineNumber);
    }

    /* @TODO: Need custom wrapper for fclose()? */
    fclose(fileForHtml);
    customFree(buf, chunksize);
}


void renderOksaText(struct DynamicText** outputText, struct AssociativeDynamicTextList** list1, char* filename, int lineNumber);


void
renderOksaFile(char* path, struct DynamicText** outputText, struct AssociativeDynamicTextList** list1, char* filename, int lineNumber)
{
    /* @TODO: Need custom wrapper for fopen()? */
    FILE* fileForHtml = fopen(path, "r");

    if (NULL == fileForHtml)
    {
        appendMessageToErrorLog("fopen() returns NULL!", __func__, filename, lineNumber);
        customExit(EXIT_FAILURE);
    }

    int nread = 0;
    struct stat st;
    /* @TODO: Need custom wrapper for stat()? */
    stat(path, &st);
    int chunksize = st.st_size + 64;
    char* buf = customMalloc(chunksize * sizeof(char));

    /* Resolve lazy page allocation with memory clearing. */
    customMemset(buf, '\0', chunksize * sizeof(char));

    while ((nread = fread(buf, 1, chunksize, fileForHtml)) > 0)
    {
        if (ferror(fileForHtml))
        {
            appendMessageToErrorLog("ferror() returns error!", __func__, filename, lineNumber);
            customExit(EXIT_FAILURE);
        }

        int errorNumber = 0;
        (*outputText)->append(outputText, buf, &errorNumber, filename, lineNumber);
    }

    /* @TODO: Need custom wrapper for fclose()? */
    fclose(fileForHtml);
    customFree(buf, chunksize);

    renderOksaText(outputText, list1, filename, lineNumber);
}


void
renderOksaText(struct DynamicText** outputText, struct AssociativeDynamicTextList** list1, char* filename, int lineNumber)
{
    int errorNumber = 0;

    if (NULL == list1)
    {
        return;
    }

    struct DynamicText* var1 = allocateDynamicText(&errorNumber, filename, lineNumber);
    struct associativeDynamicTextListElement* bufferList = (*list1)->element;

    while (NULL != bufferList)
    {
        struct AssociativeDynamicText* element = bufferList->item;

        var1->set(
            &var1,
            element->internalValue->getBytesPointer(&(element->internalValue), &errorNumber),
            &errorNumber,
            filename,
            lineNumber
        );
        convertSpecialCharsIntoHtmlCodes(&var1, filename, lineNumber);

        replaceDynamicText(
            outputText,
            element->internalKey->getBytesPointer(&(element->internalKey), &errorNumber),
            var1->getBytesPointer(&var1, &errorNumber),
            filename,
            lineNumber
        );

        bufferList = bufferList->next;
    }

    var1->free(&var1, &errorNumber, filename, lineNumber);
}
