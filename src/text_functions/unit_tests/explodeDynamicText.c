/*
The MIT License (MIT)
Copyright (c) 2021 Thomas Krüger
See full details in LICENSE.txt file.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
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
executeTest1(void)
{
    char* titleFromTest = "#01 Explode a text with an one-letter separator which do not exist.";

    int errorNumber = 0;
    char* expectedText = "name1";

    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);
    var1->set(&var1, "name1", &errorNumber, __FILE__, __LINE__);

    struct DynamicTextList* list1 = allocateDynamicTextList(&errorNumber, __FILE__, __LINE__);
    explodeDynamicText(&var1, "&", &list1, __FILE__, __LINE__);

    struct DynamicText* var2 = list1->getElementByIndex(&list1, 0, &errorNumber, __FILE__, __LINE__);

    if (
        (NULL == list1)
        || (1 != list1->countElements(&list1, &errorNumber, __FILE__, __LINE__))
        || (customStrlen(expectedText, &errorNumber) != var2->getLength(&var2, &errorNumber, __FILE__, __LINE__))
        || (0 != customStrncmp(var2->getBytesPointer(&var2, &errorNumber), expectedText, customStrlen(expectedText, &errorNumber)))
    )
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    var1->free(&var1, &errorNumber, __FILE__, __LINE__);
    list1->free(&list1, &errorNumber, __FILE__, __LINE__);

    if (
        (NULL == list1)
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
executeTest2(void)
{
    char* titleFromTest = "#02 Explode a text with a normal text which do not exist.";

    int errorNumber = 0;
    char* expectedText = "name1";

    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);
    var1->set(&var1, "name1", &errorNumber, __FILE__, __LINE__);

    struct DynamicTextList* list1 = allocateDynamicTextList(&errorNumber, __FILE__, __LINE__);
    explodeDynamicText(&var1, "ein", &list1, __FILE__, __LINE__);

    struct DynamicText* var2 = list1->getElementByIndex(&list1, 0, &errorNumber, __FILE__, __LINE__);

    if (
        (NULL == list1)
        || (1 != list1->countElements(&list1, &errorNumber, __FILE__, __LINE__))
        || (customStrlen(expectedText, &errorNumber) != var2->getLength(&var2, &errorNumber, __FILE__, __LINE__))
        || (0 != customStrncmp(var2->getBytesPointer(&var2, &errorNumber), expectedText, customStrlen(expectedText, &errorNumber)))
    )
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    var1->free(&var1, &errorNumber, __FILE__, __LINE__);
    list1->free(&list1, &errorNumber, __FILE__, __LINE__);

    if (
        (NULL == list1)
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
executeTest3(void)
{
    char* titleFromTest = "#03 Explode a text with a multi-byte separator which do not exist.";

    int errorNumber = 0;
    char* expectedText = "name1";

    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);
    var1->set(&var1, "name1", &errorNumber, __FILE__, __LINE__);

    struct DynamicTextList* list1 = allocateDynamicTextList(&errorNumber, __FILE__, __LINE__);
    explodeDynamicText(&var1, "ü", &list1, __FILE__, __LINE__);

    struct DynamicText* var2 = list1->getElementByIndex(&list1, 0, &errorNumber, __FILE__, __LINE__);

    if (
        (NULL == list1)
        || (1 != list1->countElements(&list1, &errorNumber, __FILE__, __LINE__))
        || (customStrlen(expectedText, &errorNumber) != var2->getLength(&var2, &errorNumber, __FILE__, __LINE__))
        || (0 != customStrncmp(var2->getBytesPointer(&var2, &errorNumber), expectedText, customStrlen(expectedText, &errorNumber)))
    )
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    var1->free(&var1, &errorNumber, __FILE__, __LINE__);
    list1->free(&list1, &errorNumber, __FILE__, __LINE__);

    if (
        (NULL == list1)
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
executeTest4(void)
{
    char* titleFromTest = "#04 Explode a text with a multi-byte text which do not exist.";

    int errorNumber = 0;
    char* expectedText = "name1";

    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);
    var1->set(&var1, "name1", &errorNumber, __FILE__, __LINE__);

    struct DynamicTextList* list1 = allocateDynamicTextList(&errorNumber, __FILE__, __LINE__);
    explodeDynamicText(&var1, "üäö", &list1, __FILE__, __LINE__);

    struct DynamicText* var2 = list1->getElementByIndex(&list1, 0, &errorNumber, __FILE__, __LINE__);

    if (
        (NULL == list1)
        || (1 != list1->countElements(&list1, &errorNumber, __FILE__, __LINE__))
        || (customStrlen(expectedText, &errorNumber) != var2->getLength(&var2, &errorNumber, __FILE__, __LINE__))
        || (0 != customStrncmp(var2->getBytesPointer(&var2, &errorNumber), expectedText, customStrlen(expectedText, &errorNumber)))
    )
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    var1->free(&var1, &errorNumber, __FILE__, __LINE__);
    list1->free(&list1, &errorNumber, __FILE__, __LINE__);

    if (
        (NULL == list1)
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
executeTest5(void)
{
    char* titleFromTest = "#05 Explode a classical key value text which one parameter pair.";

    int errorNumber = 0;
    char* expectedText1 = "name";
    char* expectedText2 = "value";

    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);
    var1->set(&var1, "name=value", &errorNumber, __FILE__, __LINE__);

    struct DynamicTextList* list1 = allocateDynamicTextList(&errorNumber, __FILE__, __LINE__);
    explodeDynamicText(&var1, "=", &list1, __FILE__, __LINE__);

    struct DynamicText* element1 = list1->getElementByIndex(&list1, 0, &errorNumber, __FILE__, __LINE__);
    struct DynamicText* element2 = list1->getElementByIndex(&list1, 1, &errorNumber, __FILE__, __LINE__);

    if (
        (NULL == list1)
        || (2 != list1->countElements(&list1, &errorNumber, __FILE__, __LINE__))
        || (customStrlen(expectedText1, &errorNumber) != element1->getLength(&element1, &errorNumber, __FILE__, __LINE__))
        || (0 != customStrncmp(element1->getBytesPointer(&element1, &errorNumber), expectedText1, customStrlen(expectedText1, &errorNumber)))
        || (customStrlen(expectedText2, &errorNumber) != element2->getLength(&element2, &errorNumber, __FILE__, __LINE__))
        || (0 != customStrncmp(element2->getBytesPointer(&element2, &errorNumber), expectedText2, customStrlen(expectedText2, &errorNumber)))
    )
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    var1->free(&var1, &errorNumber, __FILE__, __LINE__);
    list1->free(&list1, &errorNumber, __FILE__, __LINE__);

    if (
        (NULL == list1)
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
executeTest6(void)
{
    char* titleFromTest = "#06 Explode a classical key value text with many parameter pairs.";

    int errorNumber = 0;
    char* expectedText1 = "name1=value1";
    char* expectedText2 = "name2=value2";
    char* expectedText3 = "name3=value3";
    char* expectedText4 = "name4=value4";

    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);
    var1->set(&var1, "name1=value1&name2=value2&name3=value3&name4=value4", &errorNumber, __FILE__, __LINE__);

    struct DynamicTextList* list1 = allocateDynamicTextList(&errorNumber, __FILE__, __LINE__);
    explodeDynamicText(&var1, "&", &list1, __FILE__, __LINE__);

    struct DynamicText* element1 = list1->getElementByIndex(&list1, 0, &errorNumber, __FILE__, __LINE__);
    struct DynamicText* element2 = list1->getElementByIndex(&list1, 1, &errorNumber, __FILE__, __LINE__);
    struct DynamicText* element3 = list1->getElementByIndex(&list1, 2, &errorNumber, __FILE__, __LINE__);
    struct DynamicText* element4 = list1->getElementByIndex(&list1, 3, &errorNumber, __FILE__, __LINE__);

    if (
        (NULL == list1)
        || (4 != list1->countElements(&list1, &errorNumber, __FILE__, __LINE__))
        || (customStrlen(expectedText1, &errorNumber) != element1->getLength(&element1, &errorNumber, __FILE__, __LINE__))
        || (0 != customStrncmp(element1->getBytesPointer(&element1, &errorNumber), expectedText1, customStrlen(expectedText1, &errorNumber)))
        || (customStrlen(expectedText2, &errorNumber) != element2->getLength(&element2, &errorNumber, __FILE__, __LINE__))
        || (0 != customStrncmp(element2->getBytesPointer(&element2, &errorNumber), expectedText2, customStrlen(expectedText2, &errorNumber)))
        || (customStrlen(expectedText3, &errorNumber) != element3->getLength(&element3, &errorNumber, __FILE__, __LINE__))
        || (0 != customStrncmp(element3->getBytesPointer(&element3, &errorNumber), expectedText3, customStrlen(expectedText3, &errorNumber)))
        || (customStrlen(expectedText4, &errorNumber) != element4->getLength(&element4, &errorNumber, __FILE__, __LINE__))
        || (0 != customStrncmp(element4->getBytesPointer(&element4, &errorNumber), expectedText4, customStrlen(expectedText4, &errorNumber)))
    )
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    var1->free(&var1, &errorNumber, __FILE__, __LINE__);
    list1->free(&list1, &errorNumber, __FILE__, __LINE__);

    if (
        (NULL == list1)
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
executeTest7(void)
{
    char* titleFromTest = "#07 Explode a classical key value text which has only key part.";

    int errorNumber = 0;
    char* expectedText1 = "key";
    char* expectedText2 = "";

    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);
    var1->set(&var1, "key=", &errorNumber, __FILE__, __LINE__);

    struct DynamicTextList* list1 = allocateDynamicTextList(&errorNumber, __FILE__, __LINE__);
    explodeDynamicText(&var1, "=", &list1, __FILE__, __LINE__);

    struct DynamicText* element1 = list1->getElementByIndex(&list1, 0, &errorNumber, __FILE__, __LINE__);
    struct DynamicText* element2 = list1->getElementByIndex(&list1, 1, &errorNumber, __FILE__, __LINE__);

    if (
        (NULL == list1)
        || (2 != list1->countElements(&list1, &errorNumber, __FILE__, __LINE__))
        || (customStrlen(expectedText1, &errorNumber) != element1->getLength(&element1, &errorNumber, __FILE__, __LINE__))
        || (0 != customStrncmp(element1->getBytesPointer(&element1, &errorNumber), expectedText1, customStrlen(expectedText1, &errorNumber)))
        || (customStrlen(expectedText2, &errorNumber) != element2->getLength(&element2, &errorNumber, __FILE__, __LINE__))
        || (0 != customStrncmp(element2->getBytesPointer(&element2, &errorNumber), expectedText2, customStrlen(expectedText2, &errorNumber)))
    )
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    var1->free(&var1, &errorNumber, __FILE__, __LINE__);
    list1->free(&list1, &errorNumber, __FILE__, __LINE__);

    if (
        (NULL == list1)
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
executeTest8(void)
{
    char* titleFromTest = "#08 Explode a classical key value text which has only value part.";

    int errorNumber = 0;
    char* expectedText1 = "";
    char* expectedText2 = "value";

    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);
    var1->set(&var1, "=value", &errorNumber, __FILE__, __LINE__);

    struct DynamicTextList* list1 = allocateDynamicTextList(&errorNumber, __FILE__, __LINE__);
    explodeDynamicText(&var1, "=", &list1, __FILE__, __LINE__);

    struct DynamicText* element1 = list1->getElementByIndex(&list1, 0, &errorNumber, __FILE__, __LINE__);
    struct DynamicText* element2 = list1->getElementByIndex(&list1, 1, &errorNumber, __FILE__, __LINE__);

    if (
        (NULL == list1)
        || (2 != list1->countElements(&list1, &errorNumber, __FILE__, __LINE__))
        || (customStrlen(expectedText1, &errorNumber) != element1->getLength(&element1, &errorNumber, __FILE__, __LINE__))
        || (0 != customStrncmp(element1->getBytesPointer(&element1, &errorNumber), expectedText1, customStrlen(expectedText1, &errorNumber)))
        || (customStrlen(expectedText2, &errorNumber) != element2->getLength(&element2, &errorNumber, __FILE__, __LINE__))
        || (0 != customStrncmp(element2->getBytesPointer(&element2, &errorNumber), expectedText2, customStrlen(expectedText2, &errorNumber)))
    )
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    var1->free(&var1, &errorNumber, __FILE__, __LINE__);
    list1->free(&list1, &errorNumber, __FILE__, __LINE__);

    if (
        (NULL == list1)
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
executeTest9(void)
{
    char* titleFromTest = "#09 Explode a classical key value text which has different configured pairs.";

    int errorNumber = 0;
    char* expectedText1 = "key1=value1";
    char* expectedText2 = "key2=";
    char* expectedText3 = "key3";

    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);
    var1->set(&var1, "key1=value1&key2=&key3", &errorNumber, __FILE__, __LINE__);

    struct DynamicTextList* list1 = allocateDynamicTextList(&errorNumber, __FILE__, __LINE__);
    explodeDynamicText(&var1, "&", &list1, __FILE__, __LINE__);

    struct DynamicText* element1 = list1->getElementByIndex(&list1, 0, &errorNumber, __FILE__, __LINE__);
    struct DynamicText* element2 = list1->getElementByIndex(&list1, 1, &errorNumber, __FILE__, __LINE__);
    struct DynamicText* element3 = list1->getElementByIndex(&list1, 2, &errorNumber, __FILE__, __LINE__);

    if (
        (NULL == list1)
        || (3 != list1->countElements(&list1, &errorNumber, __FILE__, __LINE__))
        || (customStrlen(expectedText1, &errorNumber) != element1->getLength(&element1, &errorNumber, __FILE__, __LINE__))
        || (0 != customStrncmp(element1->getBytesPointer(&element1, &errorNumber), expectedText1, customStrlen(expectedText1, &errorNumber)))
        || (customStrlen(expectedText2, &errorNumber) != element2->getLength(&element2, &errorNumber, __FILE__, __LINE__))
        || (0 != customStrncmp(element2->getBytesPointer(&element2, &errorNumber), expectedText2, customStrlen(expectedText2, &errorNumber)))
        || (customStrlen(expectedText3, &errorNumber) != element3->getLength(&element3, &errorNumber, __FILE__, __LINE__))
        || (0 != customStrncmp(element3->getBytesPointer(&element3, &errorNumber), expectedText3, customStrlen(expectedText3, &errorNumber)))
    )
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    var1->free(&var1, &errorNumber, __FILE__, __LINE__);
    list1->free(&list1, &errorNumber, __FILE__, __LINE__);

    if (
        (NULL == list1)
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
executeTest10(void)
{
    char* titleFromTest = "#10 Explode an one-byte text with a multi-byte letter.";

    int errorNumber = 0;
    char* expectedText1 = " ";

    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);
    var1->set(&var1, " ", &errorNumber, __FILE__, __LINE__);

    struct DynamicTextList* list1 = allocateDynamicTextList(&errorNumber, __FILE__, __LINE__);
    explodeDynamicText(&var1, "ü", &list1, __FILE__, __LINE__);

    struct DynamicText* element1 = list1->getElementByIndex(&list1, 0, &errorNumber, __FILE__, __LINE__);

    if (
        (NULL == list1)
        || (1 != list1->countElements(&list1, &errorNumber, __FILE__, __LINE__))
        || (customStrlen(expectedText1, &errorNumber) != element1->getLength(&element1, &errorNumber, __FILE__, __LINE__))
        || (0 != customStrncmp(element1->getBytesPointer(&element1, &errorNumber), expectedText1, customStrlen(expectedText1, &errorNumber)))
    )
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    var1->free(&var1, &errorNumber, __FILE__, __LINE__);
    list1->free(&list1, &errorNumber, __FILE__, __LINE__);

    if (
        (NULL == list1)
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
executeTest11(void)
{
    char* titleFromTest = "#11 Explode an one-byte text with a multi-byte text.";

    int errorNumber = 0;
    char* expectedText1 = "üüä";

    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);
    var1->set(&var1, "üüä", &errorNumber, __FILE__, __LINE__);

    struct DynamicTextList* list1 = allocateDynamicTextList(&errorNumber, __FILE__, __LINE__);
    explodeDynamicText(&var1, " ", &list1, __FILE__, __LINE__);

    struct DynamicText* element1 = list1->getElementByIndex(&list1, 0, &errorNumber, __FILE__, __LINE__);

    if (
        (NULL == list1)
        || (1 != list1->countElements(&list1, &errorNumber, __FILE__, __LINE__))
        || (customStrlen(expectedText1, &errorNumber) != element1->getLength(&element1, &errorNumber, __FILE__, __LINE__))
        || (0 != customStrncmp(element1->getBytesPointer(&element1, &errorNumber), expectedText1, customStrlen(expectedText1, &errorNumber)))
    )
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    var1->free(&var1, &errorNumber, __FILE__, __LINE__);
    list1->free(&list1, &errorNumber, __FILE__, __LINE__);

    if (
        (NULL == list1)
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
executeTest12(void)
{
    char* titleFromTest = "#12 Explode a large text with a multi byte text.";

    int errorNumber = 0;
    char* expectedText1 = "This is a chair description. Duis autem vel eum iriure dolor in hendrerit in vulputate velit esse molestie consequat, vel illum dolore eu feugiat nulla facilisis at vero eros et accumsan et iusto odio dignissim qui blandit praesent luptatum zzril delenit augue duis dolore te feugait nulla facilisi.";

    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);
    var1->set(&var1, "This is a chair description. Duis autem vel eum iriure dolor in hendrerit in vulputate velit esse molestie consequat, vel illum dolore eu feugiat nulla facilisis at vero eros et accumsan et iusto odio dignissim qui blandit praesent luptatum zzril delenit augue duis dolore te feugait nulla facilisi.", &errorNumber, __FILE__, __LINE__);

    struct DynamicTextList* list1 = allocateDynamicTextList(&errorNumber, __FILE__, __LINE__);
    explodeDynamicText(&var1, "INC", &list1, __FILE__, __LINE__);

    struct DynamicText* element1 = list1->getElementByIndex(&list1, 0, &errorNumber, __FILE__, __LINE__);

    if (
        (NULL == list1)
        || (1 != list1->countElements(&list1, &errorNumber, __FILE__, __LINE__))
        || (customStrlen(expectedText1, &errorNumber) != element1->getLength(&element1, &errorNumber, __FILE__, __LINE__))
        || (0 != customStrncmp(element1->getBytesPointer(&element1, &errorNumber), expectedText1, customStrlen(expectedText1, &errorNumber)))
    )
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    var1->free(&var1, &errorNumber, __FILE__, __LINE__);
    list1->free(&list1, &errorNumber, __FILE__, __LINE__);

    if (
        (NULL == list1)
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
executeTest13(void)
{
    char* titleFromTest = "#13 ???.";

    int errorNumber = 0;
    // char* expectedText1 = "routing=/url/new";

    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);

    for (int i = 0; i < (var1->amountOfBytes - 1); i++)
    {
        var1->bytes[i] = 'a';
    }

    var1->bytes[var1->amountOfBytes - 2] = '&';

    struct DynamicTextList* list1 = allocateDynamicTextList(&errorNumber, __FILE__, __LINE__);
    explodeDynamicText(&var1, "&", &list1, __FILE__, __LINE__);

    var1->free(&var1, &errorNumber, __FILE__, __LINE__);
    list1->free(&list1, &errorNumber, __FILE__, __LINE__);

    if (
        (NULL == list1)
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
executeTest14(void)
{
    char* titleFromTest = "#14 ???.";

    int errorNumber = 0;
    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);
    var1->set(&var1, "aaaei", &errorNumber, __FILE__, __LINE__);

    struct DynamicTextList* list1 = allocateDynamicTextList(&errorNumber, __FILE__, __LINE__);
    explodeDynamicText(&var1, "ein", &list1, __FILE__, __LINE__);

    var1->free(&var1, &errorNumber, __FILE__, __LINE__);
    list1->free(&list1, &errorNumber, __FILE__, __LINE__);

    if (
        (NULL == list1)
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
executeTest15(void)
{
    char* titleFromTest = "#15 ???.";

    int errorNumber = 0;
    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);
    var1->set(&var1, "aaaein", &errorNumber, __FILE__, __LINE__);

    struct DynamicTextList* list1 = allocateDynamicTextList(&errorNumber, __FILE__, __LINE__);
    explodeDynamicText(&var1, "ein", &list1, __FILE__, __LINE__);

    var1->free(&var1, &errorNumber, __FILE__, __LINE__);
    list1->free(&list1, &errorNumber, __FILE__, __LINE__);

    if (
        (NULL == list1)
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
    printf("TEST SUITE: explodeDynamicText function\n");

    executeTest1();
    executeTest2();
    executeTest3();
    executeTest4();
    executeTest5();
    executeTest6();
    executeTest7();
    executeTest8();
    executeTest9();
    executeTest10();
    executeTest11();
    executeTest12();
    executeTest13();
    executeTest14();
    executeTest15();

    return EXIT_SUCCESS;
}
