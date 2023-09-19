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
#include "../DynamicTextList.class.c"
#include "../../../tests/helper_for_tests.c"


static void
executeNegativeTest1(void)
{
    char* titleFromTest = "#01 Emptyness with NULL parameter!";

    /* ### */
    int errorNumber = 42;
    struct DynamicTextList* list1 = allocateDynamicTextList(&errorNumber, __FILE__, __LINE__);

    if ((NULL == list1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    int result = list1->isEmpty(NULL, &errorNumber, __FILE__, __LINE__);

    if ((-1 != result) || (5000 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    list1->free(&list1, &errorNumber, __FILE__, __LINE__);

    if (
        (0 == errorNumber)
        && (NULL == list1)
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
    char* titleFromTest = "#02 Push to a NULL parameter!";

    /* ### */
    int errorNumber = 42;
    struct DynamicTextList* list1 = allocateDynamicTextList(&errorNumber, __FILE__, __LINE__);

    if ((NULL == list1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    list1->push(NULL, "", &errorNumber, __FILE__, __LINE__);

    if (6000 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    list1->free(&list1, &errorNumber, __FILE__, __LINE__);

    if (
        (0 == errorNumber)
        && (NULL == list1)
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
    char* titleFromTest = "#03 Push to a NULL pointer!";

    /* ### */
    int errorNumber = 42;
    struct DynamicTextList* list1 = allocateDynamicTextList(&errorNumber, __FILE__, __LINE__);
    struct DynamicTextList* list2 = NULL;

    if ((NULL == list1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    list1->push(&list2, "", &errorNumber, __FILE__, __LINE__);

    if (6010 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    list1->free(&list1, &errorNumber, __FILE__, __LINE__);

    if (
        (0 == errorNumber)
        && (NULL == list1)
        && (NULL == list2)
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
    char* titleFromTest = "#04 Push a NULL parameter!";

    /* ### */
    int errorNumber = 42;
    struct DynamicTextList* list1 = allocateDynamicTextList(&errorNumber, __FILE__, __LINE__);

    if ((NULL == list1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    list1->push(&list1, NULL, &errorNumber, __FILE__, __LINE__);

    if (6020 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    list1->free(&list1, &errorNumber, __FILE__, __LINE__);

    if (
        (0 == errorNumber)
        && (NULL == list1)
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
    char* titleFromTest = "#06 Push 2 texts and the last one with a mocked allocation function (always NULL)!";

    /* ### */
    int errorNumber = 42;
    struct DynamicTextList* list1 = allocateDynamicTextList(&errorNumber, __FILE__, __LINE__);

    if ((NULL == list1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    list1->push(&list1, "Just some words for a sentence (ÄÖÜäöüß@µ).", &errorNumber, __FILE__, __LINE__);

    if (0 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* Change mocking function for allocation to NULL. */
    globaleTestingFlagForNullAllocation = 1;

    /* ### */
    errorNumber = 42;
    list1->push(&list1, "Another sentence (ÄÖÜäöüß@µ).", &errorNumber, __FILE__, __LINE__);

    if (6040 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* Reset mocking function for allocation. */
    globaleTestingFlagForNullAllocation = 0;

    /* ### */
    errorNumber = 42;
    list1->free(&list1, &errorNumber, __FILE__, __LINE__);

    if (
        (0 == errorNumber)
        && (NULL == list1)
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
executeNegativeTest7(void)
{
    char* titleFromTest = "#07 Free a NULL parameter!";

    /* ### */
    int errorNumber = 42;
    struct DynamicTextList* list1 = allocateDynamicTextList(&errorNumber, __FILE__, __LINE__);

    if ((NULL == list1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    list1->free(NULL, &errorNumber, __FILE__, __LINE__);

    if (3000 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    list1->free(&list1, &errorNumber, __FILE__, __LINE__);

    if (
        (0 == errorNumber)
        && (NULL == list1)
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
executeNegativeTest8(void)
{
    char* titleFromTest = "#08 Count a NULL parameter!";

    /* ### */
    int errorNumber = 42;
    struct DynamicTextList* list1 = allocateDynamicTextList(&errorNumber, __FILE__, __LINE__);

    if ((NULL == list1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    int result = list1->countElements(NULL, &errorNumber, __FILE__, __LINE__);

    if ((-1 != result) || (2000 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    list1->free(&list1, &errorNumber, __FILE__, __LINE__);

    if (
        (0 == errorNumber)
        && (NULL == list1)
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
executeNegativeTest9(void)
{
    char* titleFromTest = "#09 Get list element with index 0 from a NULL parameter!";

    /* ### */
    int errorNumber = 42;
    struct DynamicTextList* list1 = allocateDynamicTextList(&errorNumber, __FILE__, __LINE__);

    if ((NULL == list1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    struct DynamicText* result = list1->getElementByIndex(NULL, 0, &errorNumber, __FILE__, __LINE__);

    if ((NULL != result) || (4000 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    list1->free(&list1, &errorNumber, __FILE__, __LINE__);

    if (
        (0 == errorNumber)
        && (NULL == list1)
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
executeNegativeTest10(void)
{
    char* titleFromTest = "#10 Get list element with index -1!";

    /* ### */
    int errorNumber = 42;
    struct DynamicTextList* list1 = allocateDynamicTextList(&errorNumber, __FILE__, __LINE__);

    if ((NULL == list1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    list1->push(&list1, "This is a text (ÄÖÜäöüß@µ).", &errorNumber, __FILE__, __LINE__);

    if (0 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    list1->push(&list1, "Another text (ÄÖÜäöüß@µ).", &errorNumber, __FILE__, __LINE__);

    if (0 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    list1->push(&list1, "Additional text (ÄÖÜäöüß@µ).", &errorNumber, __FILE__, __LINE__);

    if (0 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    struct DynamicText* result = list1->getElementByIndex(&list1, -1, &errorNumber, __FILE__, __LINE__);

    if ((NULL != result) || (4020 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    list1->free(&list1, &errorNumber, __FILE__, __LINE__);

    if (
        (0 == errorNumber)
        && (NULL == list1)
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
executeNegativeTest11(void)
{
    char* titleFromTest = "#11 Get a list element with an index out of bounds!";

    /* ### */
    int errorNumber = 42;
    struct DynamicTextList* list1 = allocateDynamicTextList(&errorNumber, __FILE__, __LINE__);

    if ((NULL == list1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    list1->push(&list1, "This is a text (ÄÖÜäöüß@µ).", &errorNumber, __FILE__, __LINE__);

    if (0 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    list1->push(&list1, "Another text (ÄÖÜäöüß@µ).", &errorNumber, __FILE__, __LINE__);

    if (0 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    list1->push(&list1, "Additional text (ÄÖÜäöüß@µ).", &errorNumber, __FILE__, __LINE__);

    if (0 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    struct DynamicText* result = list1->getElementByIndex(&list1, 999, &errorNumber, __FILE__, __LINE__);

    if ((NULL != result) || (4030 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    list1->free(&list1, &errorNumber, __FILE__, __LINE__);

    if (
        (0 == errorNumber)
        && (NULL == list1)
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
executeNegativeTest12(void)
{
    char* titleFromTest = "#12 Mocked malloc returns NULL for allocation!";

    /* Change mocking function for allocation to returning always NULL. */
    globaleTestingFlagForNullAllocation = 1;

    /* ### */
    int errorNumber = 42;
    struct DynamicTextList* list1 = allocateDynamicTextList(&errorNumber, __FILE__, __LINE__);

    if ((NULL != list1) || (1000 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* Reset mocking function for allocation. */
    globaleTestingFlagForNullAllocation = 0;

    /* ### */
    if (
        (globaleAmountOfAllocations == globaleAmountOfFrees)
        && (0 == globaleAmountOfAllocatedMemoryInBytes)
    )
    {
        printf("[SUCCESS] %s\n", titleFromTest);
        return;
    }

    abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
}


static void
executeNegativeTest13(void)
{
    char* titleFromTest = "#13 Check for emptyness on NULL pointer!";

    /* ### */
    int errorNumber = 42;
    struct DynamicTextList* list1 = allocateDynamicTextList(&errorNumber, __FILE__, __LINE__);
    struct DynamicTextList* list2 = NULL;

    if ((NULL == list1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    int result = list1->isEmpty(&list2, &errorNumber, __FILE__, __LINE__);

    if ((-1 != result) || (5010 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    list1->free(&list1, &errorNumber, __FILE__, __LINE__);

    if (
        (0 == errorNumber)
        && (NULL == list1)
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
executeNegativeTest14(void)
{
    char* titleFromTest = "#14 Free a NULL pointer!";

    /* ### */
    int errorNumber = 42;
    struct DynamicTextList* list1 = allocateDynamicTextList(&errorNumber, __FILE__, __LINE__);
    struct DynamicTextList* list2 = NULL;

    if ((NULL == list1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    list1->free(&list2, &errorNumber, __FILE__, __LINE__);

    if (3010 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    list1->free(&list1, &errorNumber, __FILE__, __LINE__);

    if (
        (0 == errorNumber)
        && (NULL == list1)
        && (NULL == list2)
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
executeNegativeTest15(void)
{
    char* titleFromTest = "#15 Count a dereferenced NULL parameter!";

    /* ### */
    int errorNumber = 42;
    struct DynamicTextList* list1 = allocateDynamicTextList(&errorNumber, __FILE__, __LINE__);
    struct DynamicTextList* list2 = NULL;

    if ((NULL == list1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    int result = list1->countElements(&list2, &errorNumber, __FILE__, __LINE__);

    if ((-1 != result) || (2010 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    list1->free(&list1, &errorNumber, __FILE__, __LINE__);

    if (
        (0 == errorNumber)
        && (NULL == list1)
        && (NULL == list2)
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
executeNegativeTest16(void)
{
    char* titleFromTest = "#16 Get a list element from a dereferenced NULL parameter!";

    /* ### */
    int errorNumber = 42;
    struct DynamicTextList* list1 = allocateDynamicTextList(&errorNumber, __FILE__, __LINE__);
    struct DynamicTextList* list2 = NULL;

    if ((NULL == list1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    struct DynamicText* result = list1->getElementByIndex(&list2, 0, &errorNumber, __FILE__, __LINE__);

    if ((NULL != result) || (4010 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    list1->free(&list1, &errorNumber, __FILE__, __LINE__);

    if (
        (0 == errorNumber)
        && (NULL == list1)
        && (NULL == list2)
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
    printf("\nNegative unit tests:\n");

    globaleDisableErrorLogging = 1;

    executeNegativeTest1();
    executeNegativeTest2();
    executeNegativeTest3();
    executeNegativeTest4();

    executeNegativeTest6();
    executeNegativeTest7();
    executeNegativeTest8();
    executeNegativeTest9();
    executeNegativeTest10();
    executeNegativeTest11();
    executeNegativeTest12();
    executeNegativeTest13();
    executeNegativeTest14();
    executeNegativeTest15();
    executeNegativeTest16();

    return EXIT_SUCCESS;
}
