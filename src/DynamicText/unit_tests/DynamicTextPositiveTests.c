/*
The MIT License (MIT)
Copyright (c) 2021-2023 Thomas Krüger
See full details in LICENSE.txt file.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>

#include "../../wrapperStdLib/wrappedStandardLibrary.c"
#include "../../../tests/mocks/wrappedFunctionForAllocation.c"
#include "../../../tests/mocks/wrappedFunctionForReallocation.c"
#include "../DynamicText.class.c"
#include "../../../tests/helper_for_tests.c"


// DEBUG: static void wueder zurückstellen!!!


void
executePositiveTest1(void)
{
    char* titleFromTest = "#01 Initialise and free a dynamic text.";

    /* ### */
    int errorNumber = 42;
    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);

    if ((NULL == var1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    checkIfUnusedMemoryIsSetUpAsZero(titleFromTest, &var1, __FILE__, __LINE__);

    /* ### */
    errorNumber = 42;
    if (
        (customStrlen("", &errorNumber) != var1->getLength(&var1, &errorNumber, __FILE__, __LINE__))
        || (0 != errorNumber)
    )
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    if (
        (0 != customStrncmp(var1->getBytesPointer(&var1, &errorNumber), "", customStrlen("", &errorNumber)))
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


void
executePositiveTest2(void)
{
    char* titleFromTest = "#02 Set an empty text.";

    /* ### */
    int errorNumber = 42;
    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);

    if ((NULL == var1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    checkIfUnusedMemoryIsSetUpAsZero(titleFromTest, &var1, __FILE__, __LINE__);

    /* ### */
    errorNumber = 42;
    var1->set(&var1, "", &errorNumber, __FILE__, __LINE__);

    if (0 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    checkIfUnusedMemoryIsSetUpAsZero(titleFromTest, &var1, __FILE__, __LINE__);

    /* ### */
    errorNumber = 42;
    if (
        (customStrlen("", &errorNumber) != var1->getLength(&var1, &errorNumber, __FILE__, __LINE__))
        || (0 != errorNumber)
    )
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    if (
        (0 != var1->getLength(&var1, &errorNumber, __FILE__, __LINE__))
        || (0 != errorNumber)
    )
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    if (
        (0 != customStrncmp(var1->getBytesPointer(&var1, &errorNumber), "", customStrlen("", &errorNumber)))
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


void
executePositiveTest3(void)
{
    char* titleFromTest = "#03 Set an unicode text.";

    /* ### */
    int errorNumber = 42;
    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);

    if ((NULL == var1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    checkIfUnusedMemoryIsSetUpAsZero(titleFromTest, &var1, __FILE__, __LINE__);

    /* ### */
    errorNumber = 42;
    char* ordinaryText = "This is an unicode text (ÄÖÜäöüß@µ).";
    var1->set(&var1, ordinaryText, &errorNumber, __FILE__, __LINE__);

    if (0 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    checkIfUnusedMemoryIsSetUpAsZero(titleFromTest, &var1, __FILE__, __LINE__);

    /* ### */
    errorNumber = 42;
    if (
        (customStrlen(ordinaryText, &errorNumber) != var1->getLength(&var1, &errorNumber, __FILE__, __LINE__))
        || (0 != errorNumber)
    )
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    if (
        (0 != customStrncmp(var1->getBytesPointer(&var1, &errorNumber), ordinaryText, customStrlen(ordinaryText, &errorNumber)))
        || (0 != errorNumber)
    )
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
        && (0 == globaleAmountOfAllocatedMemoryInBytes)
    )
    {
        printf("[SUCCESS] %s\n", titleFromTest);
        return;
    }

    abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
}


void
executePositiveTest4(void)
{
    char* titleFromTest = "#04 Set a text with the longest possible length without triggering a reallocation.";

    /* ### */
    int oldAmountOfReallocations = globaleAmountOfReallocations;
    char* exampleText = "Adipiscing elit, sed do eiusmod tempor incididunt ut labore et.";
                      // 123456789012345678901234567890123456789012345678901234567890123
                      // 1       10        20        30        40        50        60 63

    int errorNumber = 42;
    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);

    if ((NULL == var1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    checkIfUnusedMemoryIsSetUpAsZero(titleFromTest, &var1, __FILE__, __LINE__);

    /* ### */
    errorNumber = 42;
    var1->set(&var1, exampleText, &errorNumber, __FILE__, __LINE__);

    if (0 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    checkIfUnusedMemoryIsSetUpAsZero(titleFromTest, &var1, __FILE__, __LINE__);

    /* ### */
    errorNumber = 42;
    if (
        (customStrlen(exampleText, &errorNumber) != (var1->amountOfBytes - 1))
        || (0 != errorNumber)
        || (customStrlen(exampleText, &errorNumber) != var1->getLength(&var1, &errorNumber, __FILE__, __LINE__))
        || (0 != errorNumber)
    )
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    errorNumber = 42;
    if (
        (0 != customStrncmp(var1->getBytesPointer(&var1, &errorNumber), exampleText, customStrlen(exampleText, &errorNumber)))
        || (0 != errorNumber)
        || (oldAmountOfReallocations != globaleAmountOfReallocations)
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


void
executePositiveTest5(void)
{
    char* titleFromTest = "#05 Set a large text to trigger reallocation.";

    /* ### */
    int oldAmountOfReallocations = globaleAmountOfReallocations;
    char* sentence1 = "Sed ut (ÄÖÜäöüß@µ) unde omnis iste natus error sit voluptatem accusantium doloremque laudantium, totam rem aperiam, eaque ipsa quae ab illo inventore veritatis et quasi architecto beatae vitae dicta sunt explicabo. Nemo enim ipsam voluptatem quia voluptas sit aspernatur aut odit aut fugit, sed quia consequuntur magni dolores eos qui ratione voluptatem sequi nesciunt. Neque porro quisquam est, qui dolorem ipsum quia dolor sit amet, consectetur, adipisci velit, sed quia non numquam eius modi tempora incidunt ut labore et dolore magnam aliquam quaerat voluptatem. Ut enim ad minima veniam, quis nostrum exercitationem ullam corporis suscipit laboriosam, nisi ut aliquid ex ea commodi consequatur? Quis autem vel eum iure reprehenderit qui in ea voluptate velit esse quam nihil molestiae consequatur, vel illum qui dolorem eum fugiat quo voluptas nulla pariatur?";

    int errorNumber = 42;
    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);

    if ((NULL == var1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    checkIfUnusedMemoryIsSetUpAsZero(titleFromTest, &var1, __FILE__, __LINE__);

    /* ### */
    errorNumber = 42;
    var1->set(&var1, sentence1, &errorNumber, __FILE__, __LINE__);

    if (0 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    checkIfUnusedMemoryIsSetUpAsZero(titleFromTest, &var1, __FILE__, __LINE__);

    /* ### */
    errorNumber = 42;
    if (
        (customStrlen(sentence1, &errorNumber) != var1->getLength(&var1, &errorNumber, __FILE__, __LINE__))
        || (0 != errorNumber)
    )
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    if (
        (0 != customStrncmp(var1->getBytesPointer(&var1, &errorNumber), sentence1, customStrlen(sentence1, &errorNumber)))
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
        && (oldAmountOfReallocations < globaleAmountOfReallocations)
        && (0 == globaleAmountOfAllocatedMemoryInBytes)
    )
    {
        printf("[SUCCESS] %s\n", titleFromTest);
        return;
    }

    abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
}


void
executePositiveTest6(void)
{
    char* titleFromTest = "#06 Set 2 large text to trigger 2 reallocations.";

    /* ### */
    int oldAmountOfReallocations = globaleAmountOfReallocations;
    char* sentence1 = "Lorem ipsum (ÄÖÜäöüß@µ) sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";
    char* sentence2 = "Sed ut (ÄÖÜäöüß@µ) unde omnis iste natus error sit voluptatem accusantium doloremque laudantium, totam rem aperiam, eaque ipsa quae ab illo inventore veritatis et quasi architecto beatae vitae dicta sunt explicabo. Nemo enim ipsam voluptatem quia voluptas sit aspernatur aut odit aut fugit, sed quia consequuntur magni dolores eos qui ratione voluptatem sequi nesciunt. Neque porro quisquam est, qui dolorem ipsum quia dolor sit amet, consectetur, adipisci velit, sed quia non numquam eius modi tempora incidunt ut labore et dolore magnam aliquam quaerat voluptatem. Ut enim ad minima veniam, quis nostrum exercitationem ullam corporis suscipit laboriosam, nisi ut aliquid ex ea commodi consequatur? Quis autem vel eum iure reprehenderit qui in ea voluptate velit esse quam nihil molestiae consequatur, vel illum qui dolorem eum fugiat quo voluptas nulla pariatur?";

    int errorNumber = 42;
    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);

    if ((NULL == var1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    checkIfUnusedMemoryIsSetUpAsZero(titleFromTest, &var1, __FILE__, __LINE__);

    /* ### */
    errorNumber = 42;
    var1->set(&var1, sentence1, &errorNumber, __FILE__, __LINE__);

    if (0 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    checkIfUnusedMemoryIsSetUpAsZero(titleFromTest, &var1, __FILE__, __LINE__);

    /* ### */
    errorNumber = 42;
    var1->set(&var1, sentence2, &errorNumber, __FILE__, __LINE__);

    if (0 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    checkIfUnusedMemoryIsSetUpAsZero(titleFromTest, &var1, __FILE__, __LINE__);

    /* ### */
    errorNumber = 42;
    if (
        (customStrlen(sentence2, &errorNumber) != var1->getLength(&var1, &errorNumber, __FILE__, __LINE__))
        || (0 != errorNumber)
    )
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    if (
        (0 != customStrncmp(var1->getBytesPointer(&var1, &errorNumber), sentence2, customStrlen(sentence2, &errorNumber)))
        || (0 != errorNumber)
    )
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
        && ((oldAmountOfReallocations + 2) <= globaleAmountOfReallocations)
        && (0 == globaleAmountOfAllocatedMemoryInBytes)
    )
    {
        printf("[SUCCESS] %s\n", titleFromTest);
        return;
    }

    abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
}


void
executePositiveTest7(void)
{
    char* titleFromTest = "#07 Set 3 texts which grow on every assignment.";

    /* ### */
    char* sentence1 = "Just (ÄÖÜäöüß@µ).";
    char* sentence2 = "Just some words (ÄÖÜäöüß@µ).";
    char* sentence3 = "Just some words for a sentence (ÄÖÜäöüß@µ).";

    int errorNumber = 42;
    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);

    if ((NULL == var1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    checkIfUnusedMemoryIsSetUpAsZero(titleFromTest, &var1, __FILE__, __LINE__);

    /* ### */
    errorNumber = 42;
    var1->set(&var1, sentence1, &errorNumber, __FILE__, __LINE__);

    if (0 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    checkIfUnusedMemoryIsSetUpAsZero(titleFromTest, &var1, __FILE__, __LINE__);

    /* ### */
    errorNumber = 42;
    if (
        (customStrlen(sentence1, &errorNumber) != var1->getLength(&var1, &errorNumber, __FILE__, __LINE__))
        || (0 != errorNumber)
    )
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    if (
        (0 != customStrncmp(var1->getBytesPointer(&var1, &errorNumber), sentence1, customStrlen(sentence1, &errorNumber)))
        || (0 != errorNumber)
    )
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    var1->set(&var1, sentence2, &errorNumber, __FILE__, __LINE__);

    if (0 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    checkIfUnusedMemoryIsSetUpAsZero(titleFromTest, &var1, __FILE__, __LINE__);

    /* ### */
    errorNumber = 42;
    if (
        (customStrlen(sentence2, &errorNumber) != var1->getLength(&var1, &errorNumber, __FILE__, __LINE__))
        || (0 != errorNumber)
    )
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    if (
        (0 != customStrncmp(var1->getBytesPointer(&var1, &errorNumber), sentence2, customStrlen(sentence2, &errorNumber)))
        || (0 != errorNumber)
    )
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    var1->set(&var1, sentence3, &errorNumber, __FILE__, __LINE__);

    if (0 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    checkIfUnusedMemoryIsSetUpAsZero(titleFromTest, &var1, __FILE__, __LINE__);

    /* ### */
    errorNumber = 42;
    if (
        (customStrlen(sentence3, &errorNumber) != var1->getLength(&var1, &errorNumber, __FILE__, __LINE__))
        || (0 != errorNumber)
    )
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    if (
        (0 != customStrncmp(var1->getBytesPointer(&var1, &errorNumber), sentence3, customStrlen(sentence3, &errorNumber)))
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


void
executePositiveTest8(void)
{
    char* titleFromTest = "#08 Set 3 texts which shrink on every assignment.";

    /* ### */
    char* sentence1 = "Just some words for a sentence (ÄÖÜäöüß@µ).";
    char* sentence2 = "Just some words (ÄÖÜäöüß@µ).";
    char* sentence3 = "Just (ÄÖÜäöüß@µ).";

    int errorNumber = 42;
    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);

    if ((NULL == var1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    checkIfUnusedMemoryIsSetUpAsZero(titleFromTest, &var1, __FILE__, __LINE__);

    /* ### */
    errorNumber = 42;
    var1->set(&var1, sentence1, &errorNumber, __FILE__, __LINE__);

    if (0 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    checkIfUnusedMemoryIsSetUpAsZero(titleFromTest, &var1, __FILE__, __LINE__);

    /* ### */
    errorNumber = 42;
    if (
        (customStrlen(sentence1, &errorNumber) != var1->getLength(&var1, &errorNumber, __FILE__, __LINE__))
        || (0 != errorNumber)
    )
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    if (
        (0 != customStrncmp(var1->getBytesPointer(&var1, &errorNumber), sentence1, customStrlen(sentence1, &errorNumber)))
        || (0 != errorNumber)
    )
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    var1->set(&var1, sentence2, &errorNumber, __FILE__, __LINE__);

    if (0 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    checkIfUnusedMemoryIsSetUpAsZero(titleFromTest, &var1, __FILE__, __LINE__);

    /* ### */
    errorNumber = 42;
    if (
        (customStrlen(sentence2, &errorNumber) != var1->getLength(&var1, &errorNumber, __FILE__, __LINE__))
        || (0 != errorNumber)
    )
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    if (
        (0 != customStrncmp(var1->getBytesPointer(&var1, &errorNumber), sentence2, customStrlen(sentence2, &errorNumber)))
        || (0 != errorNumber)
    )
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    var1->set(&var1, sentence3, &errorNumber, __FILE__, __LINE__);

    if (0 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    checkIfUnusedMemoryIsSetUpAsZero(titleFromTest, &var1, __FILE__, __LINE__);

    /* ### */
    errorNumber = 42;
    if (
        (customStrlen(sentence3, &errorNumber) != var1->getLength(&var1, &errorNumber, __FILE__, __LINE__))
        || (0 != errorNumber)
    )
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    if (
        (0 != customStrncmp(var1->getBytesPointer(&var1, &errorNumber), sentence3, customStrlen(sentence3, &errorNumber)))
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


void
executePositiveTest9(void)
{
    char* titleFromTest = "#09 Append an empty text.";

    /* ### */
    int errorNumber = 42;
    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);

    if ((NULL == var1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    checkIfUnusedMemoryIsSetUpAsZero(titleFromTest, &var1, __FILE__, __LINE__);

    /* ### */
    errorNumber = 42;
    var1->append(&var1, "", &errorNumber, __FILE__, __LINE__);

    if (0 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    checkIfUnusedMemoryIsSetUpAsZero(titleFromTest, &var1, __FILE__, __LINE__);

    /* ### */
    errorNumber = 42;
    if (
        (customStrlen("", &errorNumber) != var1->getLength(&var1, &errorNumber, __FILE__, __LINE__))
        || (0 != errorNumber)
    )
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    if (
        (0 != customStrncmp(var1->getBytesPointer(&var1, &errorNumber), "", customStrlen("", &errorNumber)))
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


void
executePositiveTest10(void)
{
    char* titleFromTest = "#10 Append an unicode text.";

    /* ### */
    char* sentence1 = "Just some words for a sentence (ÄÖÜäöüß@µ).";

    int errorNumber = 42;
    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);

    if ((NULL == var1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    checkIfUnusedMemoryIsSetUpAsZero(titleFromTest, &var1, __FILE__, __LINE__);

    /* ### */
    errorNumber = 42;
    var1->append(&var1, sentence1, &errorNumber, __FILE__, __LINE__);

    if (0 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    checkIfUnusedMemoryIsSetUpAsZero(titleFromTest, &var1, __FILE__, __LINE__);

    /* ### */
    errorNumber = 42;
    if (
        (customStrlen(sentence1, &errorNumber) != var1->getLength(&var1, &errorNumber, __FILE__, __LINE__))
        || (0 != errorNumber)
    )
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    if (
        (0 != customStrncmp(var1->getBytesPointer(&var1, &errorNumber), sentence1, customStrlen(sentence1, &errorNumber)))
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


void
executePositiveTest11(void)
{
    char* titleFromTest = "#11 Append 3 texts.";

    /* ### */
    char* sentence1 = "A new text (ÄÖÜäöüß@µ).";
    char* sentence2 = " This is the time for a better text (ÄÖÜäöüß@µ)!";
    char* sentence3 = " Three strings in a text is a text (ÄÖÜäöüß@µ)!";

    int errorNumber = 42;
    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);

    if ((NULL == var1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    checkIfUnusedMemoryIsSetUpAsZero(titleFromTest, &var1, __FILE__, __LINE__);

    /* ### */
    errorNumber = 42;
    var1->append(&var1, sentence1, &errorNumber, __FILE__, __LINE__);

    if (0 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    checkIfUnusedMemoryIsSetUpAsZero(titleFromTest, &var1, __FILE__, __LINE__);

    /* ### */
    errorNumber = 42;
    if (
        (customStrlen(sentence1, &errorNumber) != var1->getLength(&var1, &errorNumber, __FILE__, __LINE__))
        || (0 != errorNumber)
    )
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    if (
        (0 != customStrncmp(var1->getBytesPointer(&var1, &errorNumber), sentence1, customStrlen(sentence1, &errorNumber)))
        || (0 != errorNumber)
    )
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    var1->append(&var1, sentence2, &errorNumber, __FILE__, __LINE__);
    if (0 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    checkIfUnusedMemoryIsSetUpAsZero(titleFromTest, &var1, __FILE__, __LINE__);

    /* ### */
    errorNumber = 42;
    if (
        (customStrlen(sentence1, &errorNumber) + customStrlen(sentence2, &errorNumber)) != var1->getLength(&var1, &errorNumber, __FILE__, __LINE__)
        || (0 != errorNumber)
    )
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    var1->append(&var1, sentence3, &errorNumber, __FILE__, __LINE__);

    if (0 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    checkIfUnusedMemoryIsSetUpAsZero(titleFromTest, &var1, __FILE__, __LINE__);

    /* ### */
    errorNumber = 42;
    if (
        (customStrlen(sentence1, &errorNumber) + customStrlen(sentence2, &errorNumber) + customStrlen(sentence3, &errorNumber)) != var1->getLength(&var1, &errorNumber, __FILE__, __LINE__)
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


void
executePositiveTest12(void)
{
    char* titleFromTest = "#12 Append 2 large texts to trigger reallocations.";

    /* ### */
    char* sentence1 = "Lorem ipsum (ÄÖÜäöüß@µ) sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";
    char* sentence2 = "Sed ut (ÄÖÜäöüß@µ) unde omnis iste natus error sit voluptatem accusantium doloremque laudantium, totam rem aperiam, eaque ipsa quae ab illo inventore veritatis et quasi architecto beatae vitae dicta sunt explicabo. Nemo enim ipsam voluptatem quia voluptas sit aspernatur aut odit aut fugit, sed quia consequuntur magni dolores eos qui ratione voluptatem sequi nesciunt. Neque porro quisquam est, qui dolorem ipsum quia dolor sit amet, consectetur, adipisci velit, sed quia non numquam eius modi tempora incidunt ut labore et dolore magnam aliquam quaerat voluptatem. Ut enim ad minima veniam, quis nostrum exercitationem ullam corporis suscipit laboriosam, nisi ut aliquid ex ea commodi consequatur? Quis autem vel eum iure reprehenderit qui in ea voluptate velit esse quam nihil molestiae consequatur, vel illum qui dolorem eum fugiat quo voluptas nulla pariatur?";

    int errorNumber = 42;
    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);

    if ((NULL == var1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    checkIfUnusedMemoryIsSetUpAsZero(titleFromTest, &var1, __FILE__, __LINE__);

    /* ### */
    errorNumber = 42;
    var1->append(&var1, sentence1, &errorNumber, __FILE__, __LINE__);

    if (0 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    checkIfUnusedMemoryIsSetUpAsZero(titleFromTest, &var1, __FILE__, __LINE__);

    /* ### */
    errorNumber = 42;
    if (
        (customStrlen(sentence1, &errorNumber) != var1->getLength(&var1, &errorNumber, __FILE__, __LINE__))
        || (0 != errorNumber)
    )
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    errorNumber = 42;
    var1->append(&var1, sentence2, &errorNumber, __FILE__, __LINE__);

    if (0 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    checkIfUnusedMemoryIsSetUpAsZero(titleFromTest, &var1, __FILE__, __LINE__);

    /* ### */
    errorNumber = 42;
    if (
        (customStrlen(sentence1, &errorNumber) + customStrlen(sentence2, &errorNumber) != var1->getLength(&var1, &errorNumber, __FILE__, __LINE__))
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
        && (globaleAmountOfReallocations > 0)
        && (0 == globaleAmountOfAllocatedMemoryInBytes)
    )
    {
        printf("[SUCCESS] %s\n", titleFromTest);
        return;
    }

    abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
}


void
executePositiveTest13(void)
{
    char* titleFromTest = "#13 Manually resize 2x and fill all bytes with letters each time.";

    /* ### */
    int errorNumber = 42;
    int oldAmountOfReallocations = globaleAmountOfReallocations;
    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);

    if ((NULL == var1) || (0 != errorNumber))
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    checkIfUnusedMemoryIsSetUpAsZero(titleFromTest, &var1, __FILE__, __LINE__);

    /* ### */
    if (var1->minAmountOfBytes != var1->amountOfBytes)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    int newSize = 200;
    errorNumber = 42;
    var1->resize(&var1, newSize, &errorNumber, __FILE__, __LINE__);

    if (0 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    checkIfUnusedMemoryIsSetUpAsZero(titleFromTest, &var1, __FILE__, __LINE__);

    /* ### */
    if (newSize != var1->amountOfBytes)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    /* ### */
    newSize = 300;
    errorNumber = 42;
    var1->resize(&var1, newSize, &errorNumber, __FILE__, __LINE__);

    if (0 != errorNumber)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    checkIfUnusedMemoryIsSetUpAsZero(titleFromTest, &var1, __FILE__, __LINE__);

    /* ### */
    if (newSize != var1->amountOfBytes)
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
        && ((oldAmountOfReallocations + 2) == globaleAmountOfReallocations)
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
    printf("DynamicText.class.c\n\n");
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

    return EXIT_SUCCESS;
}
