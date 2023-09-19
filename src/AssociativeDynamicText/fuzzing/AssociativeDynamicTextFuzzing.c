/*
The MIT License (MIT)
Copyright (c) 2023 Thomas Krüger
See full details in LICENSE.txt file.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../../wrapperStdLib/wrappedStandardLibrary.c"
#include "../../../tests/mocks/wrappedFunctionForAllocation.c"
#include "../../wrapperStdLib/wrappedFunctionForReallocation.c"
#include "../../DynamicText/DynamicText.class.c"
#include "../AssociativeDynamicText.class.c"
#include "../../../tests/helper_for_tests.c"

#include "../../../fuzzing/fuzzing_helper.c"


int
main(void)
{
    printf("\n");
    printf("FUZZING:\n");
    printf("AssociativeDynamicText.class.c\n\n");

    srand(time(0));

    int32_t maxIndex = 10000;

    globaleDisableErrorLogging = 1;

    int32_t errorNumber = 0;
    struct AssociativeDynamicText* var1 = NULL;
    struct AssociativeDynamicText* var2 = allocateAssociativeDynamicTextByKey("abc", &errorNumber, __FILE__, __LINE__);

    /* RESET */
    globaleAmountOfAllocations = 0;
    globaleAmountOfFrees = 0;

    for (int32_t index = 1; index <= maxIndex; index++)
    {
        int32_t randomNumber = rand() % 1;

        switch (randomNumber)
        {
            case 0:
            {
                printf("[Run %i / %i]: free & allocate\n", index, maxIndex);

                var2->free(&var1, &errorNumber, __FILE__, __LINE__);

                if (globaleAmountOfAllocations != globaleAmountOfFrees)
                {
                    printf("[ERROR: globaleAmountOfAllocations = %i vs. globaleAmountOfFrees = %i]\n", globaleAmountOfAllocations, globaleAmountOfFrees);
                    exit(EXIT_FAILURE);
                }

                var1 = allocateAssociativeDynamicTextByKey("abc", &errorNumber, __FILE__, __LINE__);
            }
            break;






            default:
            {
                printf("randomNumber is unknown: %i\n", randomNumber);
                exit(EXIT_FAILURE);
            }
        }
    }

    var2->free(&var1, &errorNumber, __FILE__, __LINE__);
    var2->free(&var2, &errorNumber, __FILE__, __LINE__);

    return EXIT_SUCCESS;
}
