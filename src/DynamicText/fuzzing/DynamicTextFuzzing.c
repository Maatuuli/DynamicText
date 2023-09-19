/*
The MIT License (MIT)
Copyright (c) 2021-2023 Thomas Krüger
See full details in LICENSE.txt file.
*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>

#include "../../wrapperStdLib/wrappedStandardLibrary.c"
#include "../../../tests/mocks/wrappedFunctionForAllocation.c"
#include "../../../tests/mocks/wrappedFunctionForReallocation.c"
#include "../DynamicText.class.c"
#include "../../../tests/helper_for_tests.c"

#include "../../../fuzzing/fuzzing_helper.c"


int
main(void)
{
    printf("\n");
    printf("FUZZING:\n");
    printf("DynamicText.class.c\n\n");

    srand(time(0));

    int32_t maxIndex = 30000;

    globaleDisableErrorLogging = 1;

    int32_t errorNumber = 0;
    struct DynamicText* var1 = NULL;
    struct DynamicText* var2 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);

    /* RESET */
    globaleAmountOfAllocations = 0;
    globaleAmountOfFrees = 0;

    for (int32_t index = 1; index <= maxIndex; index++)
    {
        int32_t randomNumber = rand() % 15;

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

                var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);

                checkIfUnusedMemoryIsSetUpAsZero("Fuzzing", &var1, __FILE__, __LINE__);
            }
            break;

            case 1:
            {
                printf("[Run %i / %i]: free(NULL, ...)\n", index, maxIndex);
                var2->free(NULL, &errorNumber, __FILE__, __LINE__);

                if (0 == errorNumber)
                {
                    printf("[ERROR: errorNumber is not 0!]\n");
                    exit(EXIT_FAILURE);
                }
            }
            break;

            case 2:
            {
                printf("[Run %i / %i]: free(&var1, ...)\n", index, maxIndex);
                var2->free(&var1, &errorNumber, __FILE__, __LINE__);

                if (globaleAmountOfAllocations != globaleAmountOfFrees)
                {
                    printf("[ERROR: globaleAmountOfAllocations = %i vs. globaleAmountOfFrees = %i]\n", globaleAmountOfAllocations, globaleAmountOfFrees);
                    exit(EXIT_FAILURE);
                }
            }
            break;

            case 3:
            {
                printf("[Run %i / %i]: getBytesPointer(NULL, ...)\n", index, maxIndex);
                var2->getBytesPointer(NULL, &errorNumber);

                if (0 == errorNumber)
                {
                    printf("[ERROR: errorNumber is not 0!]\n");
                    exit(EXIT_FAILURE);
                }
            }
            break;

            case 4:
            {
                printf("[Run %i / %i]: getBytesPointer(&var1, ...)\n", index, maxIndex);
                var2->getBytesPointer(&var1, &errorNumber);
            }
            break;

            case 5:
            {
                printf("[Run %i / %i]: set(NULL, \"\", ...)\n", index, maxIndex);
                var2->set(NULL, "", &errorNumber, __FILE__, __LINE__);

                if (0 == errorNumber)
                {
                    printf("[ERROR: errorNumber is not 0!]\n");
                    exit(EXIT_FAILURE);
                }
            }
            break;

            case 6:
            {
                printf("[Run %i / %i]: set(&var1, \"\", ...)\n", index, maxIndex);
                var2->set(&var1, "", &errorNumber, __FILE__, __LINE__);
            }
            break;

            case 7:
            {
                char* smallRandomText = NULL;
                int32_t amountOfBytes = rand() % (var2->minAmountOfBytes - 1);
                amountOfBytes++;

                setUpRandomFilledText(&smallRandomText, amountOfBytes);

                printf("[Run %i / %i]: set(&var1, smallRandomText, ...)\n", index, maxIndex);
                var2->set(&var1, smallRandomText, &errorNumber, __FILE__, __LINE__);

                customFree(smallRandomText, amountOfBytes);
            }
            break;

            case 8:
            {
                char* largeRandomText = NULL;
                int32_t amountOfBytes = rand() % (var2->maxAmountOfBytes - var2->minAmountOfBytes);

                amountOfBytes += var2->minAmountOfBytes;

                setUpRandomFilledText(&largeRandomText, amountOfBytes);

                printf("[Run %i / %i]: set(&var1, largeRandomText, ...)\n", index, maxIndex);
                var2->set(&var1, largeRandomText, &errorNumber, __FILE__, __LINE__);

                customFree(largeRandomText, amountOfBytes);
            }
            break;

            case 9:
            {
                printf("[Run %i / %i]: append(NULL, \"\", ...)\n", index, maxIndex);
                var2->append(NULL, "", &errorNumber, __FILE__, __LINE__);

                if (0 == errorNumber)
                {
                    printf("[ERROR: errorNumber is not 0!]\n");
                    exit(EXIT_FAILURE);
                }
            }
            break;

            case 10:
            {
                printf("[Run %i / %i]: append(&var1, \"\", ...)\n", index, maxIndex);
                var2->append(&var1, "", &errorNumber, __FILE__, __LINE__);
            }
            break;

            case 11:
            {
                char* smallRandomText = NULL;
                int32_t amountOfBytes = rand() % (var2->minAmountOfBytes - 1);
                amountOfBytes++;

                setUpRandomFilledText(&smallRandomText, amountOfBytes);

                printf("[Run %i / %i]: append(&var1, smallRandomText, ...)\n", index, maxIndex);
                var2->append(&var1, smallRandomText, &errorNumber, __FILE__, __LINE__);

                customFree(smallRandomText, amountOfBytes);
            }
            break;

            case 12:
            {
                char* largeRandomText = NULL;
                int32_t amountOfBytes = rand() % (var2->maxAmountOfBytes - var2->minAmountOfBytes);
                amountOfBytes += var2->minAmountOfBytes;

                setUpRandomFilledText(&largeRandomText, amountOfBytes);

                printf("[Run %i / %i]: append(&var1, largeRandomText, ...)\n", index, maxIndex);
                var2->append(&var1, largeRandomText, &errorNumber, __FILE__, __LINE__);

                customFree(largeRandomText, amountOfBytes);
            }
            break;

            case 13:
            {
                int32_t newSize = 32;
                printf("[Run %i / %i]: resize(NULL, %i, ...)\n", index, maxIndex, newSize);
                var2->resize(NULL, newSize, &errorNumber, __FILE__, __LINE__);

                if (0 == errorNumber)
                {
                    printf("[ERROR: errorNumber is not 0!]\n");
                    exit(EXIT_FAILURE);
                }
            }
            break;

            case 14:
            {
                int32_t newSize = 12345;
                if (NULL != var1)
                {
                    newSize = var1->amountOfBytes * 2;
                }

                printf("[Run %i / %i]: resize(&var1, %i, ...)\n", index, maxIndex, newSize);
                var2->resize(&var1, newSize, &errorNumber, __FILE__, __LINE__);
            }
            break;

            default:
            {
                printf("randomNumber is unknown: %i\n", randomNumber);
                exit(EXIT_FAILURE);
            }
        }

        if (NULL != var1)
        {
            checkIfUnusedMemoryIsSetUpAsZero("Fuzzing", &var1, __FILE__, __LINE__);
        }
    }

    var2->free(&var1, &errorNumber, __FILE__, __LINE__);
    var2->free(&var2, &errorNumber, __FILE__, __LINE__);

    return EXIT_SUCCESS;
}
