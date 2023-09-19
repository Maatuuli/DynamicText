/*
Compile with:
cd ./examples
gcc DynamicText.c --output DynamicText.out
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../src/wrapperStdLib/wrappedStandardLibrary.c"
#include "../src/wrapperStdLib/wrappedFunctionForAllocation.c"
#include "../src/wrapperStdLib/wrappedFunctionForReallocation.c"
#include "../src/DynamicText/DynamicText.class.c"

int
main(void)
{
    int errorNumber = 42;
    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);

    var1->resize(&var1, 9999, &errorNumber, __FILE__, __LINE__);
    var1->set(&var1, "At vero eos et accusam et justo duo dolores et ea rebum.", &errorNumber, __FILE__, __LINE__);

    printf("Text: %s\n", var1->getBytesPointer(&var1, &errorNumber));

    var1->set(&var1, "Hello", &errorNumber, __FILE__, __LINE__);
    var1->append(&var1, " World! (äöüÄÖÜß@µ)", &errorNumber, __FILE__, __LINE__);

    printf("Text: %s\n", var1->getBytesPointer(&var1, &errorNumber));
    printf("Amount of Bytes: %i\n", var1->getLength(&var1, &errorNumber, __FILE__, __LINE__));

    var1->free(&var1, &errorNumber, __FILE__, __LINE__);

    return EXIT_SUCCESS;
}
