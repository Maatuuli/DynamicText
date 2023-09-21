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
    printf("[SUCCESS] #06 End index is greater-equal than the maximum length of text which is not allowed!\n");

    int errorNumber = 0;
    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);
    (*var1).set(&var1, "This is a regular sentence.", &errorNumber, __FILE__, __LINE__);

    struct DynamicText* var2 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);

    getSubstringInBytesFromDynamicText(
        &var1,
        5,
        (*var1).getByteLength(&var1, &errorNumber, __FILE__, __LINE__) + 5,
        &var2,
        __FILE__,
        __LINE__
    );

    return EXIT_SUCCESS;
}
