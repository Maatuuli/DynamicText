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
executeTest1(void)
{
    char* titleFromTest = "#01 Implode a normal list with key value pairs.";

    int errorNumber = 0;
    struct DynamicText* var2 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);
    var2->set(&var2, "name1=value1&name2=value2&name3=value3&name4=value4", &errorNumber, __FILE__, __LINE__);

    struct DynamicTextList* list1 = allocateDynamicTextList(&errorNumber, __FILE__, __LINE__);
    explodeDynamicText(&var2, "&", &list1, __FILE__, __LINE__);

    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);
    implodeListForDynamicText(&list1, &var1, "&", __FILE__, __LINE__);

    if (
        (0 != var1->getLength(&var1, &errorNumber, __FILE__, __LINE__))
        || (0 != customStrncmp(var1->getBytesPointer(&var1, &errorNumber), "", 0))
    )
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    var1->free(&var1, &errorNumber, __FILE__, __LINE__);
    var2->free(&var2, &errorNumber, __FILE__, __LINE__);
    list1->free(&list1, &errorNumber, __FILE__, __LINE__);

    if (
        (NULL == var1)
        && (NULL == var2)
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
    printf("TEST SUITE: implodeListForDynamicText function\n");

    executeTest1();

    return EXIT_SUCCESS;
}
