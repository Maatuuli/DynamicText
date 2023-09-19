/*
The MIT License (MIT)
Copyright (c) 2021-2023 Thomas Krüger
See full details in LICENSE.txt file.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <time.h>

#include "../../wrapperStdLib/wrappedStandardLibrary.c"
#include "../../../tests/mocks/wrappedFunctionForAllocation.c"
#include "../../wrapperStdLib/wrappedFunctionForReallocation.c"
#include "../../DynamicText/DynamicText.class.c"
#include "../AssociativeDynamicText.class.c"
#include "../../../tests/helper_for_tests.c"


static void
executeNegativeTest1(void)
{
    char* titleFromTest = "#01 Parameter for key is NULL!";

    /* ### */
    int errorNumber = 42;
    struct AssociativeDynamicText* var1 = allocateAssociativeDynamicTextByKey(NULL, &errorNumber, __FILE__, __LINE__);

    if (
        (1000 == errorNumber)
        && (NULL == var1)
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
    char* titleFromTest = "#02 Parameter for key is empty!";

    /* ### */
    int errorNumber = 42;
    struct AssociativeDynamicText* var1 = allocateAssociativeDynamicTextByKey("", &errorNumber, __FILE__, __LINE__);

    if (
        (1010 == errorNumber)
        && (NULL == var1)
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
    char* titleFromTest = "#03 Allocate with a mocked allocation function!";

    /* Change mocking function for allocation to NULL. */
    globaleTestingFlagForNullAllocation = 1;

    /* ### */
    int errorNumber = 42;
    struct AssociativeDynamicText* var1 = allocateAssociativeDynamicTextByKey("name1", &errorNumber, __FILE__, __LINE__);

    /* Change mocking function for allocation to NULL. */
    globaleTestingFlagForNullAllocation = 0;

    if (
        (1020 == errorNumber)
        && (NULL == var1)
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
    char* titleFromTest = "#04 Set with NULL parameter!";

    /* ### */
    int errorNumber = 42;
    struct AssociativeDynamicText* var1 = allocateAssociativeDynamicTextByKey("key1", &errorNumber, __FILE__, __LINE__);

    if ((NULL == var1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    var1->set(NULL, "abc", &errorNumber, __FILE__, __LINE__);

    if (3000 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    var1->free(&var1, &errorNumber, __FILE__, __LINE__);

    if (
        (0 == errorNumber)
        && (NULL == var1)
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
    char* titleFromTest = "#05 Set with NULL pointer for parameter!";

    /* ### */
    int errorNumber = 42;
    struct AssociativeDynamicText* var1 = allocateAssociativeDynamicTextByKey("key1", &errorNumber, __FILE__, __LINE__);
    struct AssociativeDynamicText* var2 = NULL;

    if ((NULL == var1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    var1->set(&var2, "key1", &errorNumber, __FILE__, __LINE__);

    if (3010 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    var1->free(&var1, &errorNumber, __FILE__, __LINE__);

    if (
        (0 == errorNumber)
        && (NULL == var1)
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
    char* titleFromTest = "#06 Free NULL parameter!";

    /* ### */
    int errorNumber = 42;
    struct AssociativeDynamicText* var1 = allocateAssociativeDynamicTextByKey("key1", &errorNumber, __FILE__, __LINE__);

    if ((NULL == var1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    var1->free(NULL, &errorNumber, __FILE__, __LINE__);

    if (2000 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    var1->free(&var1, &errorNumber, __FILE__, __LINE__);

    if (
        (0 == errorNumber)
        && (NULL == var1)
        && (globaleAmountOfAllocations == globaleAmountOfFrees)
        && (0 == globaleAmountOfAllocatedMemoryInBytes)
    )
    {
        printf("[SUCCESS] %s\n", titleFromTest);
        return;
    }

    /* ### */
    abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
}


static void
executeNegativeTest7(void)
{
    char* titleFromTest = "#07 Free NULL pointer for parameter!";

    /* ### */
    int errorNumber = 42;
    struct AssociativeDynamicText* var1 = allocateAssociativeDynamicTextByKey("key1", &errorNumber, __FILE__, __LINE__);
    struct AssociativeDynamicText* var2 = NULL;

    if ((NULL == var1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    var1->free(&var2, &errorNumber, __FILE__, __LINE__);

    if (2010 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    var1->free(&var1, &errorNumber, __FILE__, __LINE__);

    if (
        (0 == errorNumber)
        && (NULL == var1)
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
    executeNegativeTest7();

    return EXIT_SUCCESS;
}
