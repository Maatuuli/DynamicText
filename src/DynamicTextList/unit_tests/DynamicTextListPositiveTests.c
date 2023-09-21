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
executePositiveTest1(void)
{
    char* titleFromTest = "#01 Count the amount of list elements from an empty DynamicTextList.";

    /* ### */
    int errorNumber = 42;
    struct DynamicTextList* list1 = allocateDynamicTextList(&errorNumber, __FILE__, __LINE__);

    if ((NULL == list1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    int countForList1 = list1->countElements(&list1, &errorNumber, __FILE__, __LINE__);

    if ((0 != countForList1) || (0 != errorNumber))
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
executePositiveTest2(void)
{
    char* titleFromTest = "#02 Count the amount of list elements from a list with 3 elements.";

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
    list1->push(&list1, "", &errorNumber, __FILE__, __LINE__);

    if (0 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    int countForList1 = list1->countElements(&list1, &errorNumber, __FILE__, __LINE__);

    if ((3 != countForList1) || (0 != errorNumber))
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
executePositiveTest3(void)
{
    char* titleFromTest = "#03 Check emptyness for an empty DynamicTextList.";

    /* ### */
    int errorNumber = 42;
    struct DynamicTextList* list1 = allocateDynamicTextList(&errorNumber, __FILE__, __LINE__);

    if ((NULL == list1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    int result = list1->isEmpty(&list1, &errorNumber, __FILE__, __LINE__);

    if ((1 != result) || (0 != errorNumber))
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
executePositiveTest4(void)
{
    char* titleFromTest = "#04 Check emptyness for a list with 1 element.";

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
    int result = list1->isEmpty(&list1, &errorNumber, __FILE__, __LINE__);

    if ((0 != result) || (0 != errorNumber))
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
executePositiveTest5(void)
{
    char* titleFromTest = "#05 Get the correct element #1 from a list with 3 elements.";

    /* ### */
    int errorNumber = 42;
    struct DynamicTextList* list1 = allocateDynamicTextList(&errorNumber, __FILE__, __LINE__);

    if ((NULL == list1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    char* sentence1 = "This is a text (ÄÖÜäöüß@µ).";
    char* sentence2 = "Another text (ÄÖÜäöüß@µ).";
    char* sentence3 = "";
    errorNumber = 42;
    list1->push(&list1, sentence1, &errorNumber, __FILE__, __LINE__);

    if (0 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    list1->push(&list1, sentence2, &errorNumber, __FILE__, __LINE__);

    if (0 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    list1->push(&list1, sentence3, &errorNumber, __FILE__, __LINE__);

    if (0 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    struct DynamicText* var1 = list1->getElementByIndex(&list1, 0, &errorNumber, __FILE__, __LINE__);

    if (
        (0 != errorNumber)
        || (NULL == var1)
        || (customStrlen(sentence1, &errorNumber) != var1->getByteLength(&var1, &errorNumber, __FILE__, __LINE__))
        || (0 != errorNumber)
        || (0 != customStrncmp(var1->getBytesPointer(&var1, &errorNumber), sentence1, customStrlen(sentence1, &errorNumber)))
        || (0 != errorNumber)
    )
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

    /* ### */
    abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
}


static void
executePositiveTest6(void)
{
    char* titleFromTest = "#06 Get the correct element #3 from a list with 3 elements.";

    /* ### */
    int errorNumber = 42;
    struct DynamicTextList* list1 = allocateDynamicTextList(&errorNumber, __FILE__, __LINE__);

    if ((NULL == list1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    char* sentence1 = "This is a text (ÄÖÜäöüß@µ).";
    char* sentence2 = "Another text (ÄÖÜäöüß@µ).";
    char* sentence3 = "";
    errorNumber = 42;
    list1->push(&list1, sentence1, &errorNumber, __FILE__, __LINE__);

    if (0 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    list1->push(&list1, sentence2, &errorNumber, __FILE__, __LINE__);

    if (0 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    list1->push(&list1, sentence3, &errorNumber, __FILE__, __LINE__);

    if (0 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    struct DynamicText* var1 = list1->getElementByIndex(&list1, 2, &errorNumber, __FILE__, __LINE__);

    if (
        (0 != errorNumber)
        || (NULL == var1)
        || (customStrlen(sentence3, &errorNumber) != var1->getByteLength(&var1, &errorNumber, __FILE__, __LINE__))
        || (0 != customStrncmp(var1->getBytesPointer(&var1, &errorNumber), sentence3, customStrlen(sentence3, &errorNumber)))
    )
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

    /* ### */
    abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
}


int
main(void)
{
    printf("\n");
    printf("TEST SUITE:\n");
    printf("DynamicTextList.class.c\n\n");
    printf("Positive unit tests:\n");

    executePositiveTest1();
    executePositiveTest2();
    executePositiveTest3();
    executePositiveTest4();
    executePositiveTest5();
    executePositiveTest6();

    return EXIT_SUCCESS;
}
