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
#include "../DynamicTextList.class.c"
#include "../../../tests/helper_for_tests.c"

#include "../../../fuzzing/fuzzing_helper.c"


int
main(void)
{
    printf("\n");
    printf("FUZZING:\n");
    printf("DynamicTextList.class.c\n\n");

    srand(time(0));

    int32_t maxIndex = 30000;

    globaleDisableErrorLogging = 1;

    int32_t errorNumber = 0;
    struct DynamicTextList* list1 = NULL;
    struct DynamicTextList* list2 = allocateDynamicTextList(&errorNumber, __FILE__, __LINE__);
    struct DynamicText* text = allocateDynamicText(&errorNumber, __FILE__, __LINE__);

    /* RESET */
    globaleAmountOfAllocations = 0;
    globaleAmountOfFrees = 0;

    for (int32_t index = 1; index <= maxIndex; index++)
    {
        int32_t randomNumber = rand() % 13;

        switch (randomNumber)
        {
            case 0:
            {
                printf("[Run %i / %i]: free & allocate\n", index, maxIndex);

                list2->free(&list1, &errorNumber, __FILE__, __LINE__);

                if (globaleAmountOfAllocations != globaleAmountOfFrees)
                {
                    printf("[ERROR: globaleAmountOfAllocations = %i vs. globaleAmountOfFrees = %i]\n", globaleAmountOfAllocations, globaleAmountOfFrees);
                    exit(EXIT_FAILURE);
                }

                list1 = allocateDynamicTextList(&errorNumber, __FILE__, __LINE__);
            }
            break;

            case 1:
            {
                printf("[Run %i / %i]: free(NULL, ...)\n", index, maxIndex);
                list2->free(NULL, &errorNumber, __FILE__, __LINE__);

                if (0 == errorNumber)
                {
                    printf("[ERROR: errorNumber is not 0!]\n");
                    exit(EXIT_FAILURE);
                }
            }
            break;

            case 2:
            {
                printf("[Run %i / %i]: free(&list1, ...)\n", index, maxIndex);
                list2->free(&list1, &errorNumber, __FILE__, __LINE__);

                if (globaleAmountOfAllocations != globaleAmountOfFrees)
                {
                    printf("[ERROR: globaleAmountOfAllocations = %i vs. globaleAmountOfFrees = %i]\n", globaleAmountOfAllocations, globaleAmountOfFrees);
                    exit(EXIT_FAILURE);
                }
            }
            break;

            case 3:
            {
                printf("[Run %i / %i]: countElements(NULL, ...)\n", index, maxIndex);
                list2->countElements(NULL, &errorNumber, __FILE__, __LINE__);

                if (0 == errorNumber)
                {
                    printf("[ERROR: errorNumber is not 0!]\n");
                    exit(EXIT_FAILURE);
                }
            }
            break;

            case 4:
            {
                printf("[Run %i / %i]: countElements(&list1, ...)\n", index, maxIndex);
                list2->countElements(&list1, &errorNumber, __FILE__, __LINE__);
            }
            break;

            case 5:
            {
                printf("[Run %i / %i]: getElementByIndex(NULL, ...)\n", index, maxIndex);
                list2->getElementByIndex(NULL, 0, &errorNumber, __FILE__, __LINE__);

                if (0 == errorNumber)
                {
                    printf("[ERROR: errorNumber is not 0!]\n");
                    exit(EXIT_FAILURE);
                }
            }
            break;

            case 6:
            {
                int32_t amount = 0;

                if (NULL != list1)
                {
                    int32_t amountOfElements = list2->countElements(&list1, &errorNumber, __FILE__, __LINE__);
                    if (amountOfElements > 0)
                    {
                        amount = rand() % amountOfElements;
                    }
                }

                printf("[Run %i / %i]: getElementByIndex(&list1, %i, ...)\n", index, maxIndex, amount);
                list2->getElementByIndex(&list1, amount, &errorNumber, __FILE__, __LINE__);
            }
            break;

            case 7:
            {
                printf("[Run %i / %i]: push(NULL, "", ...)\n", index, maxIndex);
                list2->push(NULL, "", &errorNumber, __FILE__, __LINE__);

                if (0 == errorNumber)
                {
                    printf("[ERROR: errorNumber is not 0!]\n");
                    exit(EXIT_FAILURE);
                }
            }
            break;

            case 8:
            {
                printf("[Run %i / %i]: push(&list1, "", ...)\n", index, maxIndex);
                list2->push(&list1, "", &errorNumber, __FILE__, __LINE__);
            }
            break;

            case 9:
            {
                char* smallRandomText = NULL;
                int32_t amountOfBytes = rand() % ((text->minAmountOfBytes) - 1);
                amountOfBytes++;

                setUpRandomFilledText(&smallRandomText, amountOfBytes);

                printf("[Run %i / %i]: push(&list1, smallText, ...)\n", index, maxIndex);
                list2->push(&list1, smallRandomText, &errorNumber, __FILE__, __LINE__);

                customFree(smallRandomText, amountOfBytes);
            }
            break;

            case 10:
            {
                char* largeRandomText = NULL;
                int32_t amountOfBytes = rand() % (text->maxAmountOfBytes - text->minAmountOfBytes);
                amountOfBytes += text->minAmountOfBytes;

                setUpRandomFilledText(&largeRandomText, amountOfBytes);

                printf("[Run %i / %i]: push(&list1, largeRandomText, ...)\n", index, maxIndex);
                list2->push(&list1, largeRandomText, &errorNumber, __FILE__, __LINE__);

                customFree(largeRandomText, amountOfBytes);
            }
            break;

            case 11:
            {
                printf("[Run %i / %i]: isEmpty(NULL, ...)\n", index, maxIndex);
                list2->isEmpty(NULL, &errorNumber, __FILE__, __LINE__);

                if (0 == errorNumber)
                {
                    printf("[ERROR: errorNumber is not 0!]\n");
                    exit(EXIT_FAILURE);
                }
            }
            break;

            case 12:
            {
                printf("[Run %i / %i]: isEmpty(&list1, ...)\n", index, maxIndex);
                list2->isEmpty(&list1, &errorNumber, __FILE__, __LINE__);
            }
            break;

            default:
            {
                printf("randomNumber is unknown: %i\n", randomNumber);
                exit(EXIT_FAILURE);
            }
        }
    }

    list2->free(&list1, &errorNumber, __FILE__, __LINE__);
    list2->free(&list2, &errorNumber, __FILE__, __LINE__);
    text->free(&text, &errorNumber, __FILE__, __LINE__);

    return EXIT_SUCCESS;
}
