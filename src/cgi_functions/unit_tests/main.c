/*
The MIT License (MIT)
Copyright (c) 2021 Thomas Krüger
See full details in LICENSE.txt file.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <time.h>

#include "../../wrapperStdLib/wrappedStandardLibrary.c"
#include "../../wrapperStdLib/wrappedFunctionForAllocation.c"
#include "../../wrapperStdLib/wrappedFunctionForReallocation.c"
#include "../../DynamicText/DynamicText.class.c"
#include "../../DynamicTextList/DynamicTextList.class.c"
#include "../../text_functions/text_functions.c"
#include "../../AssociativeDynamicText/AssociativeDynamicText.class.c"
#include "../../AssociativeDynamicTextList/AssociativeDynamicTextList.class.c"
#include "../cgi_functions.c"
#include "../../../tests/helper_for_tests.c"


static void
executeTest1(void)
{
    char* titleFromTest = "#01 ???.";

    int var1 = getNumericValueFromHexadecialLetter('A', __FILE__, __LINE__);

    if (
        (var1 < 0)
        || (var1 > 15)
    )
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    if (
        (var1 >= 0)
        && (var1 <= 15)
        && (globaleAmountOfAllocations == globaleAmountOfFrees)
        && (0 == globaleAmountOfAllocatedMemoryInBytes)
    )
    {
        printf("[SUCCESS] %s\n", titleFromTest);
        return;
    }

    abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
}


static void
executeTest2(void)
{
    char* titleFromTest = "#02 ???.";

    int errorNumber = 0;
    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);

    char* sentenceActual = "This is a text.";
    char* sentenceExpected = "This is a text.";
    var1->set(&var1, sentenceActual, &errorNumber, __FILE__, __LINE__);

    convertCgiEncodingIntoNormalText(&var1,  __FILE__, __LINE__);

    if (
        (customStrlen(sentenceExpected, &errorNumber) != var1->getLength(&var1, &errorNumber, __FILE__, __LINE__))
        || (0 != customStrncmp(var1->getBytesPointer(&var1, &errorNumber), sentenceExpected, customStrlen(sentenceExpected, &errorNumber)))
    )
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    var1->free(&var1, &errorNumber, __FILE__, __LINE__);

    if (
        (NULL == var1)
        && (globaleAmountOfAllocations == globaleAmountOfFrees)
        && (0 == globaleAmountOfAllocatedMemoryInBytes)
    )
    {
        printf("[SUCCESS] %s\n", titleFromTest);
        return;
    }

    abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
}


static void
executeTest3(void)
{
    char* titleFromTest = "#03 ???.";

    int errorNumber = 0;
    struct AssociativeDynamicTextList* list = allocateAssociativeDynamicTextList(&errorNumber, __FILE__, __LINE__);
    // char* textFromServer = "var1=value1&var2&value2"; // @TOOO: ERROR!
    char* textFromServer = "var1=value1&item1&value2";

    initRequestParametersByEnvironmentText(&list, textFromServer, __FILE__, __LINE__);

    if (
        (NULL == list)
        || (1 != list->isKeyExisting(&list, "var1", &errorNumber, __FILE__, __LINE__))
        || (1 != list->isKeyExisting(&list, "var2", &errorNumber, __FILE__, __LINE__))
    )
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    list->free(&list, &errorNumber, __FILE__, __LINE__);

    if (
        (NULL == list)
        && (globaleAmountOfAllocations == globaleAmountOfFrees)
        && (0 == globaleAmountOfAllocatedMemoryInBytes)
    )
    {
        printf("[SUCCESS] %s\n", titleFromTest);
        return;
    }

    abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
}


int
main(void)
{
    printf("\n");
    printf("TEST SUITE: cgi_functions.c\n");

    executeTest1();
    executeTest2();
    executeTest3();

    return EXIT_SUCCESS;
}
