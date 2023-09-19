/*
Compile with:
cd ./examples
gcc AssociativeDynamicTextList.c --output AssociativeDynamicTextList.out
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
#include "../src/text_functions/text_functions.c"
#include "../src/AssociativeDynamicText/AssociativeDynamicText.class.c"
#include "../src/AssociativeDynamicTextList/AssociativeDynamicTextList.class.c"


int
main(void)
{
    int errorNumber = 42;
    struct AssociativeDynamicTextList* list1 = allocateAssociativeDynamicTextList(&errorNumber, __FILE__, __LINE__);

    if (list1->isEmpty(&list1, &errorNumber, __FILE__, __LINE__))
    {
        printf("Empty associative list? => yes\n\n");
    }

    list1->addElement(&list1, "key1", "value 1 (äöüÄÖÜß@µ)", &errorNumber, __FILE__, __LINE__);
    list1->addElement(&list1, "key2", "value 2 (äöüÄÖÜß@µ)", &errorNumber, __FILE__, __LINE__);
    list1->addElement(&list1, "key3", "value 3 (äöüÄÖÜß@µ)", &errorNumber, __FILE__, __LINE__);

    int countForList1 = list1->countElements(&list1, &errorNumber, __FILE__, __LINE__);
    printf("Amount of associative list elements: %i\n\n", countForList1);

    if (list1->isKeyExisting(&list1, "key2", &errorNumber, __FILE__, __LINE__))
    {
        struct AssociativeDynamicText* element = list1->getElement(&list1, "key2", &errorNumber, __FILE__, __LINE__);
        struct DynamicText* text = element->internalValue;
        printf("Text from second list element:\n\"%s\"\n", text->getBytesPointer(&text, &errorNumber));
    }

    list1->free(&list1, &errorNumber, __FILE__, __LINE__);

    return EXIT_SUCCESS;
}
