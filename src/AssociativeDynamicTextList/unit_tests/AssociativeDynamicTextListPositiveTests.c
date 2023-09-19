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
executePositiveTest1(void)
{
    char* titleFromTest = "#01 Check on emptyness for a list with 0 elements and with 1 element.";

    /* ### */
    int errorNumber = 42;
    struct AssociativeDynamicTextList* list1 = allocateAssociativeDynamicTextList(&errorNumber, __FILE__, __LINE__);

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
    list1->addElement(&list1, "name1", "value1", &errorNumber, __FILE__, __LINE__);

    if (0 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    result = list1->isEmpty(&list1, &errorNumber, __FILE__, __LINE__);

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
executePositiveTest2(void)
{
    char* titleFromTest = "#02 Check if regular key exists in empty list, in list with 3 elements and check for non-existing key.";

    /* ### */
    int errorNumber = 42;
    struct AssociativeDynamicTextList* list1 = allocateAssociativeDynamicTextList(&errorNumber, __FILE__, __LINE__);

    if ((NULL == list1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    int result = list1->isKeyExisting(&list1, "name1", &errorNumber, __FILE__, __LINE__);

    if ((0 != result) || (0 != errorNumber))
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
    list1->addElement(&list1, "name2", "value2", &errorNumber, __FILE__, __LINE__);

    if (0 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    list1->addElement(&list1, "name3", "value3", &errorNumber, __FILE__, __LINE__);

    if (0 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    if (
        (1 != list1->isKeyExisting(&list1, "name1", &errorNumber, __FILE__, __LINE__))
        || (0 != errorNumber)
    )
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    if (
        (1 != list1->isKeyExisting(&list1, "name2", &errorNumber, __FILE__, __LINE__))
        || (0 != errorNumber)
    )
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    if (
        (1 != list1->isKeyExisting(&list1, "name3", &errorNumber, __FILE__, __LINE__))
        || (0 != errorNumber)
    )
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    result = list1->isKeyExisting(&list1, "non-existing-key", &errorNumber, __FILE__, __LINE__);

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
executePositiveTest3(void)
{
    char* titleFromTest = "#03 Get different elements with their key from a list.";

    /* ### */
    char* textForKey1 = "a";
    char* textForKey2 = "ÄÖÜ";
    char* textForKey3 = "Sed ut (ÄÖÜäöüß@µ) unde omnis iste natus error sit voluptatem accusantium doloremque laudantium, totam rem aperiam, eaque ipsa quae ab illo inventore veritatis et quasi architecto beatae vitae dicta sunt explicabo. Nemo enim ipsam voluptatem quia voluptas sit aspernatur aut odit aut fugit, sed quia consequuntur magni dolores eos qui ratione voluptatem sequi nesciunt. Neque porro quisquam est, qui dolorem ipsum quia dolor sit amet, consectetur, adipisci velit, sed quia non numquam eius modi tempora incidunt ut labore et dolore magnam aliquam quaerat voluptatem. Ut enim ad minima veniam, quis nostrum exercitationem ullam corporis suscipit laboriosam, nisi ut aliquid ex ea commodi consequatur? Quis autem vel eum iure reprehenderit qui in ea voluptate velit esse quam nihil molestiae consequatur, vel illum qui dolorem eum fugiat quo voluptas nulla pariatur?";

    char* textForValue1 = "value1";
    char* textForValue2 = "value2";
    char* textForValue3 = "value3";

    int errorNumber = 42;
    struct AssociativeDynamicTextList* list1 = allocateAssociativeDynamicTextList(&errorNumber, __FILE__, __LINE__);

    if ((NULL == list1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    list1->addElement(&list1, textForKey1, textForValue1, &errorNumber, __FILE__, __LINE__);

    if (0 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    list1->addElement(&list1, textForKey2, textForValue2, &errorNumber, __FILE__, __LINE__);

    if (0 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    list1->addElement(&list1, textForKey3, textForValue3, &errorNumber, __FILE__, __LINE__);

    if (0 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    struct AssociativeDynamicText* var1 = list1->getElement(&list1, textForKey1, &errorNumber, __FILE__, __LINE__);

    if (0 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    struct AssociativeDynamicText* var2 = list1->getElement(&list1, textForKey2, &errorNumber, __FILE__, __LINE__);

    if (0 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    struct AssociativeDynamicText* var3 = list1->getElement(&list1, textForKey3, &errorNumber, __FILE__, __LINE__);

    if (0 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    struct DynamicText* text1 = var1->internalValue;
    struct DynamicText* text2 = var2->internalValue;
    struct DynamicText* text3 = var3->internalValue;

    errorNumber = 42;
    if (
        (1 != isExactTextMatch(text1->getBytesPointer(&text1, &errorNumber), textForValue1, __FILE__, __LINE__))
        || (0 != errorNumber)
    )
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    if (
        (1 != isExactTextMatch(text2->getBytesPointer(&text2, &errorNumber), textForValue2, __FILE__, __LINE__))
        || (0 != errorNumber)
    )
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    if (
        (1 != isExactTextMatch(text3->getBytesPointer(&text3, &errorNumber), textForValue3, __FILE__, __LINE__))
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

    abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
}


static void
executePositiveTest4(void)
{
    char* titleFromTest = "#04 Count empty list and list with 1 element.";

    /* ### */
    int errorNumber = 42;
    struct AssociativeDynamicTextList* list1 = allocateAssociativeDynamicTextList(&errorNumber, __FILE__, __LINE__);

    if ((NULL == list1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    int result = list1->countElements(&list1, &errorNumber, __FILE__, __LINE__);

    if ((0 != result) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    list1->addElement(&list1, "key1", "value1", &errorNumber, __FILE__, __LINE__);

    if (0 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    result = list1->countElements(&list1, &errorNumber, __FILE__, __LINE__);

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


int
main(void)
{
    printf("\n");
    printf("TEST SUITE:\n");
    printf("AssociativeDynamicTextList.class.c\n\n");
    printf("Positive unit tests:\n");

    executePositiveTest1();
    executePositiveTest2();
    executePositiveTest3();
    executePositiveTest4();

    return EXIT_SUCCESS;
}
