/*
The MIT License (MIT)
Copyright (c) 2021-2023 Thomas Krüger
See full details in LICENSE.txt file.
*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>

#include "../../wrapperStdLib/wrappedStandardLibrary.c"
#include "../../../tests/mocks/wrappedFunctionForAllocation.c"
#include "../../../tests/mocks/wrappedFunctionForReallocation.c"
#include "../DynamicText.class.c"
#include "../../../tests/helper_for_tests.c"


static void
executeNegativeTest1(void)
{
    char* titleFromTest = "#01 Allocate with a mocked malloc function (always NULL)!";

    /* Change mocking function for allocation to returning always NULL. */
    globaleTestingFlagForNullAllocation = 1;
    int oldAmountOfReallocations = globaleAmountOfReallocations;
    int errorNumber = 42;
    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);

    if ((NULL != var1) || (1000 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* Reset mocking function for allocation. */
    globaleTestingFlagForNullAllocation = 0;

    /* ### */
    if (
        (NULL == var1)
        && (globaleAmountOfAllocations == globaleAmountOfFrees)
        && (oldAmountOfReallocations == globaleAmountOfReallocations)
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
    char* titleFromTest = "#02 Set an empty text to a NULL parameter!";

    /* ### */
    int errorNumber = 42;
    int oldAmountOfReallocations = globaleAmountOfReallocations;
    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);

    if ((NULL == var1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    var1->set(NULL, "", &errorNumber, __FILE__, __LINE__);

    if (6000 != errorNumber)
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
        && (oldAmountOfReallocations == globaleAmountOfReallocations)
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
    char* titleFromTest = "#03 Set an empty text to a NULL pointer!";

    /* ### */
    int errorNumber = 42;
    int oldAmountOfReallocations = globaleAmountOfReallocations;
    struct DynamicText* var1 = NULL;
    struct DynamicText* var2 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);

    if ((NULL == var2) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    var2->set(&var1, "", &errorNumber, __FILE__, __LINE__);

    if (6010 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    var2->free(&var2, &errorNumber, __FILE__, __LINE__);

    if (
        (0 == errorNumber)
        && (NULL == var2)
        && (globaleAmountOfAllocations == globaleAmountOfFrees)
        && (oldAmountOfReallocations == globaleAmountOfReallocations)
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
    char* titleFromTest = "#04 Set a NULL parameter to a valid dynamic text!";

    /* ### */
    int errorNumber = 42;
    int oldAmountOfReallocations = globaleAmountOfReallocations;
    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);

    if ((NULL == var1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    var1->set(&var1, NULL, &errorNumber, __FILE__, __LINE__);

    /* ### */
    if (6020 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    var1->free(&var1, &errorNumber, __FILE__, __LINE__);

    /* ### */
    if (
        (0 == errorNumber)
        && (NULL == var1)
        && (globaleAmountOfAllocations == globaleAmountOfFrees)
        && (oldAmountOfReallocations == globaleAmountOfReallocations)
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
    char* titleFromTest = "#05 Set text over maximum allowed bytes limit!";

    /* ### */
    int errorNumber = 42;
    int oldAmountOfReallocations = globaleAmountOfReallocations;
    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);

    if ((NULL == var1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    int maxAllowedSizeInBytes = (1 + var1->maxAmountOfBytes) * sizeof(char);
    char* hugeText = customMalloc(maxAllowedSizeInBytes);

    /* ### */
    customMemset(hugeText, 'a', maxAllowedSizeInBytes);
    hugeText[maxAllowedSizeInBytes - 1] = '\0';

    /* ### */
    errorNumber = 42;
    var1->set(&var1, hugeText, &errorNumber, __FILE__, __LINE__);

    if (6030 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    customFree(hugeText, maxAllowedSizeInBytes);
    errorNumber = 42;
    var1->free(&var1, &errorNumber, __FILE__, __LINE__);

    if (
        (0 == errorNumber)
        && (NULL == var1)
        && (globaleAmountOfAllocations == globaleAmountOfFrees)
        && (oldAmountOfReallocations == globaleAmountOfReallocations)
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
    char* titleFromTest = "#06 Append a text to a NULL parameter!";

    /* ### */
    int errorNumber = 42;
    int oldAmountOfReallocations = globaleAmountOfReallocations;
    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);

    if ((NULL == var1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    var1->append(NULL, "abc", &errorNumber, __FILE__, __LINE__);

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
        && (oldAmountOfReallocations == globaleAmountOfReallocations)
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
    char* titleFromTest = "#07 Append a text to a NULL pointer!";

    /* ### */
    int errorNumber = 42;
    int oldAmountOfReallocations = globaleAmountOfReallocations;
    struct DynamicText* var1 = NULL;
    struct DynamicText* var2 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);

    if ((NULL == var2) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    var2->append(&var1, "abc", &errorNumber, __FILE__, __LINE__);

    if (2010 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    var2->free(&var2, &errorNumber, __FILE__, __LINE__);

    if (
        (0 == errorNumber)
        && (NULL == var2)
        && (globaleAmountOfAllocations == globaleAmountOfFrees)
        && (oldAmountOfReallocations == globaleAmountOfReallocations)
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
    char* titleFromTest = "#08 Append a NULL parameter to a dynamic text!";

    /* ### */
    int errorNumber = 42;
    int oldAmountOfReallocations = globaleAmountOfReallocations;
    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);

    if ((NULL == var1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    var1->append(&var1, NULL, &errorNumber, __FILE__, __LINE__);

    if (2020 != errorNumber)
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
        && (oldAmountOfReallocations == globaleAmountOfReallocations)
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
    char* titleFromTest = "#09 Append text over maximum allowed bytes limit!";

    /* ### */
    int errorNumber = 42;
    int oldAmountOfReallocations = globaleAmountOfReallocations;
    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);

    if ((NULL == var1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    var1->set(&var1, "abcdef", &errorNumber, __FILE__, __LINE__);

    if (0 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    int maxAllowedSizeInBytes = var1->maxAmountOfBytes * sizeof(char);
    char* hugeText = customMalloc(maxAllowedSizeInBytes);

    /* ### */
    customMemset(hugeText, 'a', maxAllowedSizeInBytes);
    hugeText[maxAllowedSizeInBytes - 1] = '\0';

    /* ### */
    errorNumber = 42;
    var1->append(&var1, hugeText, &errorNumber, __FILE__, __LINE__);

    if (2030 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    customFree(hugeText, maxAllowedSizeInBytes);

    /* ### */
    errorNumber = 42;
    var1->free(&var1, &errorNumber, __FILE__, __LINE__);

    if (
        (0 == errorNumber)
        && (NULL == var1)
        && (globaleAmountOfAllocations == globaleAmountOfFrees)
        && (oldAmountOfReallocations == globaleAmountOfReallocations)
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
    char* titleFromTest = "#10 Resize a NULL parameter!";

    /* ### */
    int errorNumber = 42;
    int oldAmountOfReallocations = globaleAmountOfReallocations;
    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);

    if ((NULL == var1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    var1->resize(NULL, 200, &errorNumber, __FILE__, __LINE__);

    if (5000 != errorNumber)
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
        && (oldAmountOfReallocations == globaleAmountOfReallocations)
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
    char* titleFromTest = "#11 Resize a NULL pointer!";

    /* ### */
    int errorNumber = 42;
    int oldAmountOfReallocations = globaleAmountOfReallocations;
    struct DynamicText* var1 = NULL;
    struct DynamicText* var2 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);

    if ((NULL == var2) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    var2->resize(&var1, 200, &errorNumber, __FILE__, __LINE__);

    if (5010 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    var2->free(&var2, &errorNumber, __FILE__, __LINE__);

    if (
        (0 == errorNumber)
        && (NULL == var2)
        && (globaleAmountOfAllocations == globaleAmountOfFrees)
        && (oldAmountOfReallocations == globaleAmountOfReallocations)
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
    char* titleFromTest = "#12 Resize to a smaller size of bytes!";

    /* ### */
    int errorNumber = 42;
    int oldAmountOfReallocations = globaleAmountOfReallocations;
    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);

    if ((NULL == var1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    int newMemoryValueInBytes = var1->amountOfBytes / 2;
    var1->resize(&var1, newMemoryValueInBytes, &errorNumber, __FILE__, __LINE__);

    if (5020 != errorNumber)
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
        && (oldAmountOfReallocations == globaleAmountOfReallocations)
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
    char* titleFromTest = "#13 Resize to same size!";

    /* ### */
    int errorNumber = 42;
    int oldAmountOfReallocations = globaleAmountOfReallocations;
    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);

    if ((NULL == var1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    var1->resize(&var1, var1->amountOfBytes, &errorNumber, __FILE__, __LINE__);

    if (5030 != errorNumber)
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
        && (oldAmountOfReallocations == globaleAmountOfReallocations)
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
    char* titleFromTest = "#14 Resize with a mocked realloc function (always NULL)!";

    /* ### */
    int oldAmountOfReallocations = globaleAmountOfReallocations;
    int errorNumber = 42;
    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);

    if ((NULL == var1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* Change mocking function for re-allocation to returning always NULL. */
    globaleTestingFlagForNullReallocation = 1;

    /* ### */
    errorNumber = 42;
    int newMemoryValueInBytes = var1->amountOfBytes * 2;
    var1->resize(&var1, newMemoryValueInBytes, &errorNumber, __FILE__, __LINE__);

    if (5040 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* Reset mocking function for re-allocation. */
    globaleTestingFlagForNullReallocation = 0;

    /* ### */
    errorNumber = 42;
    var1->free(&var1, &errorNumber, __FILE__, __LINE__);

    if (
        (0 == errorNumber)
        && (NULL == var1)
        && (globaleAmountOfAllocations == globaleAmountOfFrees)
        && (oldAmountOfReallocations == globaleAmountOfReallocations)
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
    char* titleFromTest = "#15 Get byte length from a NULL parameter or NULL pointer!";

    /* ### */
    int errorNumber = 42;
    int oldAmountOfReallocations = globaleAmountOfReallocations;
    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);
    struct DynamicText* var2 = NULL;

    if ((NULL == var1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    int result = var1->getByteLength(NULL, &errorNumber, __FILE__, __LINE__);

    if (
        (4000 != errorNumber)
        || (-1 != result)
    )
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    result = var1->getByteLength(&var2, &errorNumber, __FILE__, __LINE__);

    if (
        (4010 != errorNumber)
        || (-1 != result)
    )
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    char* bufferedPointer = var1->bytes;
    var1->bytes = NULL;
    result = var1->getByteLength(&var1, &errorNumber, __FILE__, __LINE__);

    if (
        (4020 != errorNumber)
        || (-1 != result)
    )
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    var1->bytes = bufferedPointer;

    /* ### */
    errorNumber = 42;
    var1->free(&var1, &errorNumber, __FILE__, __LINE__);

    if (
        (0 == errorNumber)
        && (NULL == var1)
        && (globaleAmountOfAllocations == globaleAmountOfFrees)
        && (oldAmountOfReallocations == globaleAmountOfReallocations)
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
    char* titleFromTest = "#16 Get UTF-8 length from a NULL parameter or NULL pointer!";

    /* ### */
    int errorNumber = 42;
    int oldAmountOfReallocations = globaleAmountOfReallocations;
    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);
    struct DynamicText* var2 = NULL;

    if ((NULL == var1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    int result = var1->getUtf8Length(NULL, &errorNumber, __FILE__, __LINE__);

    if (
        (8000 != errorNumber)
        || (-1 != result)
    )
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    result = var1->getUtf8Length(&var2, &errorNumber, __FILE__, __LINE__);

    if (
        (8010 != errorNumber)
        || (-1 != result)
    )
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
        && (oldAmountOfReallocations == globaleAmountOfReallocations)
        && (0 == globaleAmountOfAllocatedMemoryInBytes)
    )
    {
        printf("[SUCCESS] %s\n", titleFromTest);
        return;
    }

    abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
}


static void
executeNegativeTest17(void)
{
    char* titleFromTest = "#17 Get byte data from a NULL parameter or NULL pointer!";

    /* ### */
    int errorNumber = 42;
    int oldAmountOfReallocations = globaleAmountOfReallocations;
    struct DynamicText* var1 = NULL;
    struct DynamicText* var2 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);

    if ((NULL == var2) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    char* result = var2->getBytesPointer(NULL, &errorNumber);

    if ((7000 != errorNumber) || (NULL != result))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    result = var2->getBytesPointer(&var1, &errorNumber);

    if ((NULL != result) || (7010 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    var2->free(&var2, &errorNumber, __FILE__, __LINE__);

    if (
        (0 == errorNumber)
        && (NULL == var2)
        && (globaleAmountOfAllocations == globaleAmountOfFrees)
        && (oldAmountOfReallocations == globaleAmountOfReallocations)
        && (0 == globaleAmountOfAllocatedMemoryInBytes)
    )
    {
        printf("[SUCCESS] %s\n", titleFromTest);
        return;
    }

    abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
}


static void
executeNegativeTest18(void)
{
    char* titleFromTest = "#18 Free a NULL parameter!";

    /* ### */
    int errorNumber = 42;
    int oldAmountOfReallocations = globaleAmountOfReallocations;
    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);
    if ((NULL == var1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    var1->free(NULL, &errorNumber, __FILE__, __LINE__);

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
        && (oldAmountOfReallocations == globaleAmountOfReallocations)
        && (0 == globaleAmountOfAllocatedMemoryInBytes)
    )
    {
        printf("[SUCCESS] %s\n", titleFromTest);
        return;
    }

    abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
}


static void
executeNegativeTest19(void)
{
    char* titleFromTest = "#19 Free a NULL pointer (\"double free\")!";

    /* ### */
    int errorNumber = 42;
    int oldAmountOfReallocations = globaleAmountOfReallocations;
    struct DynamicText* var1 = NULL;
    struct DynamicText* var2 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);

    if ((NULL == var2) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    var2->free(&var1, &errorNumber, __FILE__, __LINE__);

    if (3010 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    var2->free(&var2, &errorNumber, __FILE__, __LINE__);

    if (
        (0 == errorNumber)
        && (NULL == var2)
        && (globaleAmountOfAllocations == globaleAmountOfFrees)
        && (oldAmountOfReallocations == globaleAmountOfReallocations)
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
    executeNegativeTest8();
    executeNegativeTest9();
    executeNegativeTest10();
    executeNegativeTest11();
    executeNegativeTest12();
    executeNegativeTest13();
    executeNegativeTest14();
    executeNegativeTest15();
    executeNegativeTest16();
    executeNegativeTest17();
    executeNegativeTest18();
    executeNegativeTest19();

    return EXIT_SUCCESS;
}
