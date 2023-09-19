/*
Compile with:
cd ./examples
gcc DynamicTextList.c --output DynamicTextList.out
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../src/wrapperStdLib/wrappedStandardLibrary.c"
#include "../src/wrapperStdLib/wrappedFunctionForAllocation.c"
#include "../src/wrapperStdLib/wrappedFunctionForReallocation.c"
#include "../src/DynamicText/DynamicText.class.c"
#include "../src/DynamicTextList/DynamicTextList.class.c"


int
main(void)
{
    int errorNumber = 42;
    struct DynamicTextList* list1 = allocateDynamicTextList(&errorNumber, __FILE__, __LINE__);

    if (list1->isEmpty(&list1, &errorNumber, __FILE__, __LINE__))
    {
        printf("Empty list? => yes\n\n");
    }

    list1->push(&list1, "Sentence from first element (äöüÄÖÜß@µ).", &errorNumber, __FILE__, __LINE__);
    list1->push(&list1, "Sentence from second element (äöüÄÖÜß@µ).", &errorNumber, __FILE__, __LINE__);
    list1->push(&list1, "Sentence from third element (äöüÄÖÜß@µ).", &errorNumber, __FILE__, __LINE__);

    int countForList1 = list1->countElements(&list1, &errorNumber, __FILE__, __LINE__);
    printf("Amount of list elements: %i\n\n", countForList1);

    struct DynamicText* text = list1->getElementByIndex(&list1, 1, &errorNumber, __FILE__, __LINE__);
    printf("Text from second list element:\n\"%s\"\n", text->getBytesPointer(&text, &errorNumber));

    list1->free(&list1, &errorNumber, __FILE__, __LINE__);

    return EXIT_SUCCESS;
}
