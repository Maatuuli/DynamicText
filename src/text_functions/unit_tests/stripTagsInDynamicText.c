/*
The MIT License (MIT)
Copyright (c) 2021-2023 Thomas Krüger
See full details in LICENSE.txt file.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../../wrapperStdLib/wrappedStandardLibrary.c"
#include "../../wrapperStdLib/wrappedFunctionForAllocation.c"
#include "../../wrapperStdLib/wrappedFunctionForReallocation.c"
#include "../../DynamicText/DynamicText.class.c"
#include "../../DynamicTextList/DynamicTextList.class.c"
#include "../text_functions.c"
#include "../../../tests/helper_for_tests.c"


static void
executeTest1(void)
{
    char* titleFromTest = "#01 Strip tags in text with inline Javascript.";

    int errorNumber = 0;
    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);
    var1->set(
        &var1,
        "This is a short text including script tags. <script>alert('');</script> End of text.",
        &errorNumber,
        __FILE__,
        __LINE__
    );

    stripTagsInDynamicText(&var1, __FILE__, __LINE__);

    if (-1 != findPositionInDynamicText(&var1, "<script>", 0, &errorNumber, __FILE__, __LINE__))
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
executeTest2(void)
{
    char* titleFromTest = "#02 Strip tags in a text with any tags.";

    int errorNumber = 0;
    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);
    var1->set(&var1, "This is a short text including no script tags.", &errorNumber, __FILE__, __LINE__);

    stripTagsInDynamicText(&var1, __FILE__, __LINE__);

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


int
main(void)
{
    printf("\n");
    printf("TEST SUITE: stripTagsInDynamicText function\n");

    executeTest1();
    executeTest2();

    return EXIT_SUCCESS;
}
