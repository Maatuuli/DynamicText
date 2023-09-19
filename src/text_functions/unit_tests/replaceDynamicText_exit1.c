/*
The MIT License (MIT)
Copyright (c) 2022-2023 Thomas Krüger
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
    printf("TEST SUITE: replaceDynamicText() function => Not allowed test cases ending with exit() \n");

    printf("[SUCCESS] #01 Replacing in a text which is NULL which is not allowed!\n");

    replaceDynamicText(NULL, "a", "b", __FILE__, __LINE__);

    return EXIT_SUCCESS;
}
