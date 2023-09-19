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
executePositiveTest1(void)
{
    char* titleFromTest = "#01 Offset  0: Find no position of an one-byte search text in an empty text.";

    /* ### */
    int errorNumber = 42;
    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);

    if ((NULL == var1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    var1->set(&var1, "", &errorNumber, __FILE__, __LINE__);

    if (0 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    int pos = findPositionInDynamicText(&var1, "a", 0, &errorNumber, __FILE__, __LINE__);

    if ((-1 != pos) && (0 != errorNumber))
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
executePositiveTest2(void)
{
    char* titleFromTest = "#02 Offset  0: Find no position of an one-byte search text in an one-byte text.";

    /* ### */
    int errorNumber = 42;
    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);

    if ((NULL == var1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    var1->set(&var1, "1", &errorNumber, __FILE__, __LINE__);

    if (0 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    int pos = findPositionInDynamicText(&var1, "a", 0, &errorNumber, __FILE__, __LINE__);

    if ((-1 != pos) && (0 != errorNumber))
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
executePositiveTest3(void)
{
    char* titleFromTest = "#03 Offset  0: Find no position of a multi-byte search text in an one-byte text.";

    /* ### */
    int errorNumber = 42;
    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);

    if ((NULL == var1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    var1->set(&var1, "1", &errorNumber, __FILE__, __LINE__);

    if ((NULL == var1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    int pos = findPositionInDynamicText(&var1, "ü", 0, &errorNumber, __FILE__, __LINE__);

    if ((-1 != pos) && (0 != errorNumber))
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
executePositiveTest4(void)
{
    char* titleFromTest = "#04 Offset  0: Find no position of an one-byte search text in an ordinary text.";

    /* ### */
    int errorNumber = 42;
    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);

    if ((NULL == var1) && (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    var1->set(&var1, "This is a normal sentence.", &errorNumber, __FILE__, __LINE__);

    if (0 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    int pos = findPositionInDynamicText(&var1, "Z", 0, &errorNumber, __FILE__, __LINE__);

    if ((-1 != pos) && (0 != errorNumber))
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
executePositiveTest5(void)
{
    char* titleFromTest = "#05 Offset >0: Find no position of an one-byte search text in an ordinary text.";

    /* ### */
    int errorNumber = 42;
    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);

    if ((NULL == var1) && (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    var1->set(&var1, "The letter Z is a regular letter.", &errorNumber, __FILE__, __LINE__);

    if (0 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    int pos = findPositionInDynamicText(&var1, "Z", 15, &errorNumber, __FILE__, __LINE__);

    if ((-1 != pos) && (0 != errorNumber))
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
executePositiveTest6(void)
{
    char* titleFromTest = "#06 Offset  0: Find no position of a multi-byte search text in an ordinary text.";

    /* ### */
    int errorNumber = 42;
    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);

    if ((NULL == var1) && (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    var1->set(&var1, "Umlautz are regular letters.", &errorNumber, __FILE__, __LINE__);

    if (0 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    int pos = findPositionInDynamicText(&var1, "äöü", 0, &errorNumber, __FILE__, __LINE__);

    if ((-1 != pos) && (0 != errorNumber))
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
executePositiveTest7(void)
{
    char* titleFromTest = "#07 Offset >0: Find no position of a multi-byte search text in an ordinary text.";

    /* ### */
    int errorNumber = 42;
    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);

    if ((NULL == var1) && (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    var1->set(&var1, "Umlautz like äöü are regular letters.", &errorNumber, __FILE__, __LINE__);

    if (0 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    int pos = findPositionInDynamicText(&var1, "äöü", 20, &errorNumber, __FILE__, __LINE__);

    if ((-1 != pos) && (0 != errorNumber))
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
executePositiveTest8(void)
{
    char* titleFromTest = "#08 Offset  0: Find no position of a half correct multi-byte search text in an ordinary text.";

    /* ### */
    int errorNumber = 42;
    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);

    if ((NULL == var1) && (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    var1->set(&var1, "Umlautz like äöü are regular letters.", &errorNumber, __FILE__, __LINE__);

    if (0 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    int pos = findPositionInDynamicText(&var1, "äöT", 0, &errorNumber, __FILE__, __LINE__);

    if ((-1 != pos) && (0 != errorNumber))
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
executePositiveTest9(void)
{
    char* titleFromTest = "#09 Offset  0: Find the correct position of an one-byte search text in an one-byte text.";

    /* ### */
    int errorNumber = 42;
    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);

    if ((NULL == var1) && (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    var1->set(&var1, "1", &errorNumber, __FILE__, __LINE__);

    if (0 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    int pos = findPositionInDynamicText(&var1, "1", 0, &errorNumber, __FILE__, __LINE__);

    if ((-1 == pos) && (0 != errorNumber))
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
executePositiveTest10(void)
{
    char* titleFromTest = "#10 Offset  0: Find the correct position of an one-byte search text in an ordinary text.";

    /* ### */
    int errorNumber = 42;
    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);

    if ((NULL == var1) && (0 != errorNumber))
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
    int pos = findPositionInDynamicText(&var1, "g", 0, &errorNumber, __FILE__, __LINE__);

    if ((12 != pos) && (0 != errorNumber))
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
executePositiveTest11(void)
{
    char* titleFromTest = "#11 Offset >0: Find the correct position of an one-byte search text in an ordinary text.";

    /* ### */
    int errorNumber = 42;
    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);

    if ((NULL == var1) && (0 != errorNumber))
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
    int pos = findPositionInDynamicText(&var1, "e", 12, &errorNumber, __FILE__, __LINE__);

    if ((19 != pos) && (0 != errorNumber))
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
executePositiveTest12(void)
{
    char* titleFromTest = "#12 Offset  0: Find the correct position of a multi-byte search text in an ordinary text.";

    /* ### */
    int errorNumber = 42;
    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);

    if ((NULL == var1) && (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    var1->set(&var1, "The umlautz äöü are regular letters.", &errorNumber, __FILE__, __LINE__);

    if (0 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    int pos = findPositionInDynamicText(&var1, "äöü", 0, &errorNumber, __FILE__, __LINE__);

    if ((12 != pos) && (0 != errorNumber))
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
executePositiveTest13(void)
{
    char* titleFromTest = "#13 Offset >0: Find the correct position of a multi-byte search text in an ordinary text.";

    /* ### */
    int errorNumber = 42;
    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);

    if ((NULL == var1) && (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    var1->set(&var1, "The umlautz äöü are regular letters. The text äöü contains three unicode letters.", &errorNumber, __FILE__, __LINE__);

    if (0 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    int pos = findPositionInDynamicText(&var1, "äöü", 30, &errorNumber, __FILE__, __LINE__);

    /* This is the offset of a multi-byte unicode text with umlauts, be aware of this! */
    if ((49 != pos) && (0 != errorNumber))
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
executePositiveTest14(void)
{
    char* titleFromTest = "#14 ?????????? Offset 0: Find the correct position of a multi-byte search text in an ordinary text.";

    /* ### */
    int errorNumber = 42;
    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);

    if ((NULL == var1) && (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    var1->set(&var1, "commodo descriptio", &errorNumber, __FILE__, __LINE__);

    if (0 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    int pos = findPositionInDynamicText(&var1, "description", 0, &errorNumber, __FILE__, __LINE__);

    if ((-1 != pos) && (0 != errorNumber))
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
    printf("TEST SUITE:\n");
    printf("findPositionInDynamicText function\n\n");
    printf("Positive unit tests:\n");

    executePositiveTest1();
    executePositiveTest2();
    executePositiveTest3();
    executePositiveTest4();
    executePositiveTest5();
    executePositiveTest6();
    executePositiveTest7();
    executePositiveTest8();
    executePositiveTest9();
    executePositiveTest10();
    executePositiveTest11();
    executePositiveTest12();
    executePositiveTest13();
    executePositiveTest14();

    return EXIT_SUCCESS;
}
