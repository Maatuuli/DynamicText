/*
Compile with:
cd ./examples
gcc AssociativeDynamicText.c --output AssociativeDynamicText.out
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../src/wrapperStdLib/wrappedStandardLibrary.c"
#include "../src/wrapperStdLib/wrappedFunctionForAllocation.c"
#include "../src/wrapperStdLib/wrappedFunctionForReallocation.c"
#include "../src/DynamicText/DynamicText.class.c"
#include "../src/AssociativeDynamicText/AssociativeDynamicText.class.c"


int
main(void)
{
    int errorNumber = 42;
    struct AssociativeDynamicText* var1 = allocateAssociativeDynamicTextByKey("key1", &errorNumber, __FILE__, __LINE__);

    var1->set(&var1, "This is a sentence (ÄÖÜäöüß@µ).", &errorNumber, __FILE__, __LINE__);

    struct DynamicText* key = var1->getKey(&var1, &errorNumber, __FILE__, __LINE__);
    printf("KEY:\n\"%s\"\n\n", key->getBytesPointer(&key, &errorNumber));

    struct DynamicText* value = var1->getValue(&var1, &errorNumber, __FILE__, __LINE__);
    printf("VALUE:\n\"%s\"\n", value->getBytesPointer(&value, &errorNumber));

    var1->free(&var1, &errorNumber, __FILE__, __LINE__);

    return EXIT_SUCCESS;
}
