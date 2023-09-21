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
executeNegativeTest1(void)
{
    char* titleFromTest = "#01 Find a position in a NULL parameter!";

    /* ### */
    int errorNumber = 42;
    int pos = findPositionInDynamicText(NULL, "is", 0, &errorNumber, __FILE__, __LINE__);

    if (
        (-1 == pos)
        && (20000 == errorNumber)
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
executeNegativeTest2(void)
{
    char* titleFromTest = "#02 Find a position in a NULL dynamicText pointer!";

    /* ### */
    int errorNumber = 42;
    struct DynamicText* var1 = NULL;
    int pos = findPositionInDynamicText(&var1, "is", 0, &errorNumber, __FILE__, __LINE__);

    if (
        (-1 == pos)
        && (20010 == errorNumber)
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
executeNegativeTest3(void)
{
    char* titleFromTest = "#03 Parameter for needle is NULL!";

    /* ### */
    int errorNumber = 42;
    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);

    if ((NULL == var1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    int pos = findPositionInDynamicText(&var1, NULL, 0, &errorNumber, __FILE__, __LINE__);

    if ((-1 != pos) || (20020 != errorNumber)
    )
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    var1->free(&var1, &errorNumber, __FILE__, __LINE__);

    if (
        (NULL == var1)
        && (0 == errorNumber)
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
executeNegativeTest4(void)
{
    char* titleFromTest = "#04 Text from needle parameter is empty!";

    /* ### */
    int errorNumber = 42;
    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);

    if ((NULL == var1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    int pos = findPositionInDynamicText(&var1, "", 0, &errorNumber, __FILE__, __LINE__);

    if ((-1 != pos) || (20030 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    var1->free(&var1, &errorNumber, __FILE__, __LINE__);

    if (
        (NULL == var1)
        && (0 == errorNumber)
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
executeNegativeTest5(void)
{
    char* titleFromTest = "#05 Offset for start index is smaller than 0!";

    /* ### */
    int errorNumber = 42;
    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);

    if ((NULL == var1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    var1->set(&var1, "This is a regular sentence.", &errorNumber, __FILE__, __LINE__);

    if (0 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    int pos = findPositionInDynamicText(&var1, "abc", -1, &errorNumber, __FILE__, __LINE__);

    if ((-1 != pos) || (20040 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    var1->free(&var1, &errorNumber, __FILE__, __LINE__);

    if (
        (NULL == var1)
        && (0 == errorNumber)
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
executeNegativeTest6(void)
{
    char* titleFromTest = "#06 Offset for start index is greater-equal than length of text!";

    /* ### */
    int errorNumber = 42;
    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);

    if ((NULL == var1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    var1->set(&var1, "This is a regular sentence.", &errorNumber, __FILE__, __LINE__);

    if (0 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    int pos = findPositionInDynamicText(
        &var1,
        "abc",
        10 + var1->getByteLength(&var1, &errorNumber, __FILE__, __LINE__),
        &errorNumber,
        __FILE__,
        __LINE__
    );

    if ((-1 != pos) || (20050 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    var1->free(&var1, &errorNumber, __FILE__, __LINE__);

    if (
        (NULL == var1)
        && (0 == errorNumber)
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
    printf("Negative unit tests:\n");

    globaleDisableErrorLogging = 1;

    executeNegativeTest1();
    executeNegativeTest2();
    executeNegativeTest3();
    executeNegativeTest4();
    executeNegativeTest5();
    executeNegativeTest6();

    return EXIT_SUCCESS;
}
