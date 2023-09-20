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
executePositiveTest1(void)
{
    char* titleFromTest = "#01 Set multi-byte value.";

    /* ### */
    char* textForkey = "name1";
    char* textForValue = "ÄÖÜäöüß@µ";
    int errorNumber = 42;
    struct AssociativeDynamicText* var1 = allocateAssociativeDynamicTextByKey(textForkey, &errorNumber, __FILE__, __LINE__);

    if ((NULL == var1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    var1->set(&var1, textForValue, &errorNumber, __FILE__, __LINE__);

    if (0 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    struct DynamicText* key = var1->getKey(&var1, &errorNumber, __FILE__, __LINE__);
    if (0 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    errorNumber = 42;
    struct DynamicText* value = var1->getValue(&var1, &errorNumber, __FILE__, __LINE__);
    if (0 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;

    if (
        (customStrlen(textForkey, &errorNumber) != key->getLength(&key, &errorNumber, __FILE__, __LINE__))
        || (0 != errorNumber)
    )
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    if (
        (0 != customStrncmp(key->getBytesPointer(&key, &errorNumber), textForkey, customStrlen(textForkey, &errorNumber)))
        || (0 != errorNumber)
    )
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    if (
        (customStrlen(textForValue, &errorNumber) != value->getLength(&value, &errorNumber, __FILE__, __LINE__))
        || (0 != errorNumber)
    )
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    if (
        (0 != customStrncmp(value->getBytesPointer(&value, &errorNumber), textForValue, customStrlen(textForValue, &errorNumber)))
        || (0 != errorNumber)
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
    printf("AssociativeDynamicText.class.c\n\n");
    printf("Positive unit tests:\n");

    executePositiveTest1();

    return EXIT_SUCCESS;
}
