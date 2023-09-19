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


int
main(void)
{
    printf("\n");
    printf("TEST SUITE: explodeDynamicText function => Not allowed test cases ending with exit() \n");

    printf("[SUCCESS] #01 Explode text from a NULL parameter is not allowed!\n");

    int errorNumber = 0;
    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);
    var1->set(&var1, "", &errorNumber, __FILE__, __LINE__);

    explodeDynamicText(&var1, "", NULL, __FILE__, __LINE__);

    return EXIT_SUCCESS;
}
