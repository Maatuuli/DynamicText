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
#include "../../../tests/mocks/wrappedFunctionForAllocation.c"
#include "../../wrapperStdLib/wrappedFunctionForReallocation.c"
#include "../../DynamicText/DynamicText.class.c"
#include "../../DynamicTextList/DynamicTextList.class.c"
#include "../../text_functions/text_functions.c"
#include "../../AssociativeDynamicText/AssociativeDynamicText.class.c"
#include "../AssociativeDynamicTextList.class.c"
#include "../../../tests/helper_for_tests.c"


static void
executeNegativeTest1(void)
{
    char* titleFromTest = "#01 Allocate list with a mocked allocation function which always return NULL!";

    /* Change mocking function for allocation to NULL. */
    globaleTestingFlagForNullAllocation = 1;

    /* ### */
    int errorNumber = 42;
    struct AssociativeDynamicTextList* list1 = allocateAssociativeDynamicTextList(&errorNumber, __FILE__, __LINE__);

    /* Reset mocking function for allocation. */
    globaleTestingFlagForNullAllocation = 0;

    if (
        (1000 == errorNumber)
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
    char* titleFromTest = "#02 8x negative unit tests for adding an element.";

    /* ### */
    int errorNumber = 42;
    struct AssociativeDynamicTextList* list1 = allocateAssociativeDynamicTextList(&errorNumber, __FILE__, __LINE__);
    struct AssociativeDynamicTextList* list2 = NULL;

    if ((NULL == list1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    list1->addElement(NULL, "name1", "value1", &errorNumber, __FILE__, __LINE__);

    if (2000 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    list1->addElement(&list2, "name1", "value1", &errorNumber, __FILE__, __LINE__);

    if (2010 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    list1->addElement(&list1, NULL, "value1", &errorNumber, __FILE__, __LINE__);

    if (2020 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    list1->addElement(&list1, "", "value1", &errorNumber, __FILE__, __LINE__);

    if (2030 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    list1->addElement(&list1, "name1", NULL, &errorNumber, __FILE__, __LINE__);

    if (2040 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* Change mocking function for allocation to NULL. */
    globaleTestingFlagForNullAllocation = 1;

    /* ### */
    errorNumber = 42;
    list1->addElement(&list1, "name1", "value1", &errorNumber, __FILE__, __LINE__);

    if (2050 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* Reset mocking function for allocation. */
    globaleTestingFlagForNullAllocation = 0;

    /* ### */
    errorNumber = 42;
    list1->addElement(&list1, "name1", "value1", &errorNumber, __FILE__, __LINE__);

    if (0 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    list1->addElement(&list1, "name1", "value2", &errorNumber, __FILE__, __LINE__);

    if (2060 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* Change mocking function for allocation to NULL. */
    globaleTestingFlagForNullAllocation = 1;

    errorNumber = 42;
    list1->addElement(&list1, "name2", "value2", &errorNumber, __FILE__, __LINE__);

    if (2070 != errorNumber)
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

    /* ### */
    abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
}


static void
executeNegativeTest3(void)
{
    char* titleFromTest = "#03 Count elements on NULL parameter and on NULL pointer for list!";

    /* ### */
    int errorNumber = 42;
    struct AssociativeDynamicTextList* list1 = allocateAssociativeDynamicTextList(&errorNumber, __FILE__, __LINE__);
    struct AssociativeDynamicTextList* list2 = NULL;

    if ((NULL == list1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    int result = list1->countElements(NULL, &errorNumber, __FILE__, __LINE__);

    if ((-1 != result) || (3000 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    result = list1->countElements(&list2, &errorNumber, __FILE__, __LINE__);

    if ((-1 != result) || (3010 != errorNumber))
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
executeNegativeTest4(void)
{
    char* titleFromTest = "#04 Free NULL parameter and NULL pointer!";

    /* ### */
    int errorNumber = 42;
    struct AssociativeDynamicTextList* list1 = allocateAssociativeDynamicTextList(&errorNumber, __FILE__, __LINE__);
    struct AssociativeDynamicTextList* list2 = NULL;

    if ((NULL == list1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    list1->free(NULL, &errorNumber, __FILE__, __LINE__);

    if (4000 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    list1->free(&list2, &errorNumber, __FILE__, __LINE__);

    if (4010 != errorNumber)
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
executeNegativeTest5(void)
{
    char* titleFromTest = "#05 5x negative unit tests for getting an element.";

    /* ### */
    int errorNumber = 42;
    struct AssociativeDynamicTextList* list1 = allocateAssociativeDynamicTextList(&errorNumber, __FILE__, __LINE__);
    struct AssociativeDynamicTextList* list2 = NULL;

    if ((NULL == list1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    struct AssociativeDynamicText* result = list1->getElement(NULL, "name1", &errorNumber, __FILE__, __LINE__);

    if ((NULL != result) || (5000 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    result = list1->getElement(&list2, "name1", &errorNumber, __FILE__, __LINE__);

    if ((NULL != result) || (5010 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    list1->addElement(&list1, "name1", "value1", &errorNumber, __FILE__, __LINE__);

    if (0 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    result = list1->getElement(&list1, NULL, &errorNumber, __FILE__, __LINE__);

    if ((NULL != result) || (5020 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    result = list1->getElement(&list1, "", &errorNumber, __FILE__, __LINE__);

    if ((NULL != result) || (5030 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    result = list1->getElement(&list1, "name2", &errorNumber, __FILE__, __LINE__);

    if ((NULL != result) || (5040 != errorNumber))
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
    char* titleFromTest = "#06 Empty check on NULL parameter and NULL pointer for list!";

    /* ### */
    int errorNumber = 42;
    struct AssociativeDynamicTextList* list1 = allocateAssociativeDynamicTextList(&errorNumber, __FILE__, __LINE__);
    struct AssociativeDynamicTextList* list2 = NULL;

    if ((NULL == list1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    int result = list1->isEmpty(NULL, &errorNumber, __FILE__, __LINE__);

    if ((-1 != result) || (6000 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    result = list1->isEmpty(&list2, &errorNumber, __FILE__, __LINE__);

    if ((-1 != result) || (6010 != errorNumber))
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
executeNegativeTest7(void)
{
    char* titleFromTest = "#07 4x negative unit tests for checking if a key exists.";

    /* ### */
    int errorNumber = 42;
    struct AssociativeDynamicTextList* list1 = allocateAssociativeDynamicTextList(&errorNumber, __FILE__, __LINE__);
    struct AssociativeDynamicTextList* list2 = NULL;

    if ((NULL == list1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    int result = list1->isKeyExisting(NULL, "name1", &errorNumber, __FILE__, __LINE__);

    if ((-1 != result) || (7000 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    result = list1->isKeyExisting(&list2, "name1", &errorNumber, __FILE__, __LINE__);

    if ((-1 != result) || (7010 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    result = list1->isKeyExisting(&list1, NULL, &errorNumber, __FILE__, __LINE__);

    if ((-1 != result) || (7020 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    result = list1->isKeyExisting(&list1, "", &errorNumber, __FILE__, __LINE__);

    if ((-1 != result) || (7030 != errorNumber))
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
