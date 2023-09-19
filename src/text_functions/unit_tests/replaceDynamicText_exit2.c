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
    printf("[SUCCESS] #02 Replacing in a text whose pointer is NULL which is not allowed!\n");

    struct DynamicText* var1 = NULL;
    replaceDynamicText(&var1, "a", "b", __FILE__, __LINE__);

    return EXIT_SUCCESS;
}
