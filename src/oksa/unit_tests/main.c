/*
The MIT License (MIT)
Copyright (c) 2021-2023 Thomas Krüger
See full details in LICENSE.txt file.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>

#include "../../wrapperStdLib/wrappedStandardLibrary.c"
#include "../../wrapperStdLib/wrappedFunctionForAllocation.c"
#include "../../wrapperStdLib/wrappedFunctionForReallocation.c"
#include "../../DynamicText/DynamicText.class.c"
#include "../../DynamicTextList/DynamicTextList.class.c"
#include "../../text_functions/text_functions.c"
#include "../../AssociativeDynamicText/AssociativeDynamicText.class.c"
#include "../../AssociativeDynamicTextList/AssociativeDynamicTextList.class.c"
#include "../../cgi_functions/cgi_functions.c"
#include "../oksa.c"

#include "../../../tests/helper_for_tests.c"


static void
executeTest1(void)
{
    char* titleFromTest = "#01 ???.";

    int errorNumber = 0;
    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);

    renderOksaFile("../src/oksa/unit_tests/master.twig.html", &var1, NULL, __FILE__, __LINE__);

    if (var1->getByteLength(&var1, &errorNumber, __FILE__, __LINE__) < 1)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    var1->free(&var1, &errorNumber, __FILE__, __LINE__);

    if (
        (NULL == var1)
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
    char* titleFromTest = "#02 ???.";

    int errorNumber = 0;
    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);

    struct AssociativeDynamicTextList* list1 = allocateAssociativeDynamicTextList(&errorNumber, __FILE__, __LINE__);
    list1->addElement(&list1, "{{ meta-title }}", "text for meta title", &errorNumber, __FILE__, __LINE__);
    list1->addElement(&list1, "{{ meta-description }}", "text for meta description", &errorNumber, __FILE__, __LINE__);

    renderOksaFile("../src/oksa/unit_tests/master.twig.html", &var1, &list1, __FILE__, __LINE__);

    if (var1->getByteLength(&var1, &errorNumber, __FILE__, __LINE__) < 1)
    {
        abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
    }

    list1->free(&list1, &errorNumber, __FILE__, __LINE__);
    var1->free(&var1, &errorNumber, __FILE__, __LINE__);

    if (
        (NULL == var1)
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
    printf("TEST SUITE: Oksa functions\n");

    executeTest1();
    executeTest2();

    return EXIT_SUCCESS;
}
