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
#include "../../../tests/helper_for_tests.c"


struct ComparisonTexts {
    char assignment[512];
    char search[512];
    char replace[512];
    char result[512];
};


static void
executeTest1(void)
{
    char* titleFromTest = "#01 Different search texts with empty text for replace in a 1-letter text.";

    int errorNumber = 0;
    struct ComparisonTexts texts[] = {
        { .assignment = "a", .search = "a",         .replace = "", .result = "" },
        { .assignment = "a", .search = "b",         .replace = "", .result = "a" },
        { .assignment = "a", .search = "Ä",         .replace = "", .result = "a" },
        { .assignment = "a", .search = "ÄÖÜäöü",    .replace = "", .result = "a" },
        { .assignment = "a", .search = "Lorem ipsum (ÄÖÜäöüß@µ) sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.", .replace = "", .result = "a" },
        { .assignment = "Ä", .search = "Ä",         .replace = "", .result = "" },
        { .assignment = "Ä", .search = "a",         .replace = "", .result = "Ä" },
        { .assignment = "Ä", .search = "ÄÖÜäöü",    .replace = "", .result = "Ä" },
        { .assignment = "Ä", .search = "Lorem ipsum (ÄÖÜäöüß@µ) sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.", .replace = "", .result = "Ä" },
    };

    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);
    int length = sizeof(texts) / sizeof(struct ComparisonTexts);

    for (int i = 0; i < length; i++)
    {
        var1->set(&var1, texts[i].assignment, &errorNumber, __FILE__, __LINE__);
        replaceDynamicText(&var1, texts[i].search, texts[i].replace, __FILE__, __LINE__);

        if (0 == isExactTextMatch(var1->getBytesPointer(&var1, &errorNumber), texts[i].result, __FILE__, __LINE__))
        {
            abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
        }
    }

    var1->free(&var1, &errorNumber, __FILE__, __LINE__);

    if (
        (NULL == var1)
        && (globaleAmountOfAllocations == globaleAmountOfFrees)
        && (0 == globaleAmountOfAllocatedMemoryInBytes)
    )
    {
        printf("[SUCCESS] %s\n", titleFromTest);
        return;
    }

    abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
}

static void
executeTest2(void)
{
    char* titleFromTest = "#02 Different search texts with a 1-letter replace in a 1-letter text.";

    int errorNumber = 0;
    struct ComparisonTexts texts[] = {
        { .assignment = "a", .search = "a",         .replace = "a", .result = "a" },
        { .assignment = "a", .search = "a",         .replace = "1", .result = "1" },
        { .assignment = "a", .search = "a",         .replace = "Ü", .result = "Ü" },
        { .assignment = "a", .search = "b",         .replace = "1", .result = "a" },
        { .assignment = "a", .search = "Ä",         .replace = "1", .result = "a" },
        { .assignment = "a", .search = "ÄÖÜäöü",    .replace = "1", .result = "a" },
        { .assignment = "a", .search = "Lorem ipsum (ÄÖÜäöüß@µ) sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.", .replace = "1", .result = "a" },
        { .assignment = "Ä", .search = "a",         .replace = "1", .result = "Ä" },
        { .assignment = "Ä", .search = "Ä",         .replace = "1", .result = "1" },
        { .assignment = "Ä", .search = "Ä",         .replace = "Ü", .result = "Ü" },
        { .assignment = "Ä", .search = "Ö",         .replace = "Ü", .result = "Ä" },
        { .assignment = "Ä", .search = "ÄÖÜäöü",    .replace = "1", .result = "Ä" },
        { .assignment = "Ä", .search = "Lorem ipsum (ÄÖÜäöüß@µ) sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.", .replace = "1", .result = "Ä" },
    };

    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);
    int length = sizeof(texts) / sizeof(struct ComparisonTexts);

    for (int i = 0; i < length; i++)
    {
        var1->set(&var1, texts[i].assignment, &errorNumber, __FILE__, __LINE__);
        replaceDynamicText(&var1, texts[i].search, texts[i].replace, __FILE__, __LINE__);

        if (0 == isExactTextMatch(var1->getBytesPointer(&var1, &errorNumber), texts[i].result, __FILE__, __LINE__))
        {
            abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
        }
    }

    var1->free(&var1, &errorNumber, __FILE__, __LINE__);

    if (
        (NULL == var1)
        && (globaleAmountOfAllocations == globaleAmountOfFrees)
        && (0 == globaleAmountOfAllocatedMemoryInBytes)
    )
    {
        printf("[SUCCESS] %s\n", titleFromTest);
        return;
    }

    abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
}

static void
executeTest3(void)
{
    char* titleFromTest = "#03 Different search texts with a multi-letter replace in a 1-letter text.";

    int errorNumber = 0;
    struct ComparisonTexts texts[] = {
        { .assignment = "a", .search = "a",      .replace = "aÜÖÄüöäµ", .result = "aÜÖÄüöäµ" },
        { .assignment = "a", .search = "a",      .replace = "1234567890", .result = "1234567890" },
        { .assignment = "a", .search = "a",      .replace = "Lorem ipsum (ÄÖÜäöüß@µ) sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.", .result = "Lorem ipsum (ÄÖÜäöüß@µ) sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua." },
        { .assignment = "a", .search = "b",      .replace = "1", .result = "a" },
        { .assignment = "a", .search = "Ä",      .replace = "1", .result = "a" },
        { .assignment = "a", .search = "ÄÖÜäöü", .replace = "1", .result = "a" },
        { .assignment = "a", .search = "Lorem ipsum (ÄÖÜäöüß@µ) sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.", .replace = "c", .result = "a" },
        { .assignment = "Ä", .search = "Ä",      .replace = "1", .result = "1" },
        { .assignment = "Ä", .search = "Ä",      .replace = "Ä", .result = "Ä" },
        { .assignment = "Ä", .search = "Ä",      .replace = "ÜÖÄüöäµ", .result = "ÜÖÄüöäµ" },
        { .assignment = "Ä", .search = "Ä",      .replace = "Lorem ipsum (ÄÖÜäöüß@µ) sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.", .result = "Lorem ipsum (ÄÖÜäöüß@µ) sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua." },
        { .assignment = "Ä", .search = "ÄÖÜäöü", .replace = "1", .result = "Ä" },
        { .assignment = "Ä", .search = "Lorem ipsum (ÄÖÜäöüß@µ) sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.", .replace = "c", .result = "Ä" },
    };

    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);
    int length = sizeof(texts) / sizeof(struct ComparisonTexts);

    for (int i = 0; i < length; i++)
    {
        var1->set(&var1, texts[i].assignment, &errorNumber, __FILE__, __LINE__);
        replaceDynamicText(&var1, texts[i].search, texts[i].replace, __FILE__, __LINE__);

        if (0 == isExactTextMatch(var1->getBytesPointer(&var1, &errorNumber), texts[i].result, __FILE__, __LINE__))
        {
            abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
        }
    }

    var1->free(&var1, &errorNumber, __FILE__, __LINE__);

    if (
        (NULL == var1)
        && (globaleAmountOfAllocations == globaleAmountOfFrees)
        && (0 == globaleAmountOfAllocatedMemoryInBytes)
    )
    {
        printf("[SUCCESS] %s\n", titleFromTest);
        return;
    }

    abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
}

static void
executeTest4(void)
{
    char* titleFromTest = "#04 Different search texts with empty text for replace in a multi-letter text.";

    int errorNumber = 0;
    struct ComparisonTexts texts[] = {
        { .assignment = "Ä1",      .search = "Ä",       .replace = "", .result = "1" },
        { .assignment = "1ÄÖÜäöü", .search = "1",       .replace = "", .result = "ÄÖÜäöü" },
        { .assignment = "ÄÖÜ1äöü", .search = "1",       .replace = "", .result = "ÄÖÜäöü" },
        { .assignment = "ÄÖÜäöü1", .search = "1",       .replace = "", .result = "ÄÖÜäöü" },
        { .assignment = "ÄÖÜäöü",  .search = "1",       .replace = "", .result = "ÄÖÜäöü" },
        { .assignment = "ÄÖÜäöü",  .search = "µ",       .replace = "", .result = "ÄÖÜäöü" },
        { .assignment = "ÄÖÜäöü",  .search = "Ä1ä1",    .replace = "", .result = "ÄÖÜäöü" },
        { .assignment = "ÄÖÜäöü",  .search = "Lorem ipsum (ÄÖÜäöüß@µ) sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.", .replace = "", .result = "ÄÖÜäöü" },
        { .assignment = "ÄÖÜäöü",  .search = "ÄÖÜäöü",  .replace = "", .result = "" },
        { .assignment = "ÄÖÜäöüÄ1Ä2Ä3Ä4Ä5ÄÖÜäöü",  .search = "Ä1Ä2Ä3Ä4Ä5", .replace = "", .result = "ÄÖÜäöüÄÖÜäöü" },
        { .assignment = "ÄÖÜäöü",  .search = "ÄÖÜäöü",  .replace = "", .result = "" },
        { .assignment = "12341234123", .search = "234", .replace = "", .result = "11123" },
        { .assignment = "234234234", .search = "234", .replace = "", .result = "" },
        { .assignment = "234_234", .search = "234", .replace = "", .result = "_" },
        { .assignment = "234_234_234", .search = "234", .replace = "", .result = "__" },
        { .assignment = "ÄÖÜäöü", .search = "ÄÖÜäöü_1", .replace = "", .result = "ÄÖÜäöü" },
        { .assignment = "ÄÖÜäöü", .search = "Lorem ipsum (ÄÖÜäöüß@µ) sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.", .replace = "", .result = "ÄÖÜäöü" },
    };

    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);
    int length = sizeof(texts) / sizeof(struct ComparisonTexts);

    for (int i = 0; i < length; i++)
    {
        var1->set(&var1, texts[i].assignment, &errorNumber, __FILE__, __LINE__);
        replaceDynamicText(&var1, texts[i].search, texts[i].replace, __FILE__, __LINE__);

        if (0 == isExactTextMatch(var1->getBytesPointer(&var1, &errorNumber), texts[i].result, __FILE__, __LINE__))
        {
            abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
        }
    }

    var1->free(&var1, &errorNumber, __FILE__, __LINE__);

    if (
        (NULL == var1)
        && (globaleAmountOfAllocations == globaleAmountOfFrees)
        && (0 == globaleAmountOfAllocatedMemoryInBytes)
    )
    {
        printf("[SUCCESS] %s\n", titleFromTest);
        return;
    }

    abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
}

static void
executeTest5(void)
{
    char* titleFromTest = "#05 Different search texts with a 1-letter replace in a multi-letter text.";

    int errorNumber = 0;
    struct ComparisonTexts texts[] = {
        { .assignment = "ÄÖÜäöü", .search = "ÄÖÜäöü",    .replace = "1", .result = "1" },
        { .assignment = "ÄÖÜäöü", .search = "ÄÖÜäöü",    .replace = "Ü", .result = "Ü" },
        { .assignment = "ÄÖÜäöü", .search = "b",         .replace = "1", .result = "ÄÖÜäöü" },
        { .assignment = "ÄÖÜäöü", .search = "ÄÄÄ",       .replace = "1", .result = "ÄÖÜäöü" },
        { .assignment = "ÄÖÜäöü", .search = "Lorem ipsum (ÄÖÜäöüß@µ) sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.", .replace = "1", .result = "ÄÖÜäöü" },
        { .assignment = "ÄÖÜäöü", .search = "a",         .replace = "1", .result = "ÄÖÜäöü" },
        { .assignment = "ÄÖÜäöü", .search = "ÄÖÜäöü",    .replace = "1", .result = "1" },
        { .assignment = "ÄÖÜäöü", .search = "Ä",         .replace = "Ü", .result = "ÜÖÜäöü" },
        { .assignment = "ÄÖÜäöü", .search = "Ö",         .replace = "Ü", .result = "ÄÜÜäöü" },
        { .assignment = "ÄÖÜäöü", .search = "Lorem ipsum (ÄÖÜäöüß@µ) sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.", .replace = "1", .result = "ÄÖÜäöü" },
    };

    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);
    int length = sizeof(texts) / sizeof(struct ComparisonTexts);

    for (int i = 0; i < length; i++)
    {
        var1->set(&var1, texts[i].assignment, &errorNumber, __FILE__, __LINE__);
        replaceDynamicText(&var1, texts[i].search, texts[i].replace, __FILE__, __LINE__);

        if (0 == isExactTextMatch(var1->getBytesPointer(&var1, &errorNumber), texts[i].result, __FILE__, __LINE__))
        {
            abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
        }
    }

    var1->free(&var1, &errorNumber, __FILE__, __LINE__);

    if (
        (NULL == var1)
        && (globaleAmountOfAllocations == globaleAmountOfFrees)
        && (0 == globaleAmountOfAllocatedMemoryInBytes)
    )
    {
        printf("[SUCCESS] %s\n", titleFromTest);
        return;
    }

    abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
}

static void
executeTest6(void)
{
    char* titleFromTest = "#06 Different search texts with a multi-letter replace in a multi-letter text.";

    int errorNumber = 0;
    struct ComparisonTexts texts[] = {
        { .assignment = "ÄÖÜäöü", .search = "ÄÖÜäöü",      .replace = "ÜÜÜÜÜ", .result = "ÜÜÜÜÜ" },
        { .assignment = "ÄÖÜäöüaaa", .search = "ÄÖÜäöü",      .replace = "ÜÜÜÜÜ", .result = "ÜÜÜÜÜaaa" },
        { .assignment = "aaaÄÖÜäöü", .search = "ÄÖÜäöü",      .replace = "ÜÜÜÜÜ", .result = "aaaÜÜÜÜÜ" },
        { .assignment = "aaaÄÖÜäöüaaa", .search = "ÄÖÜäöü",      .replace = "ÜÜÜÜÜ", .result = "aaaÜÜÜÜÜaaa" },
        { .assignment = "ÄÖÜäöü", .search = "ÄÖÜäöü",      .replace = "1234567890", .result = "1234567890" },
        { .assignment = "ÄÖÜäöü", .search = "ÄÖÜäöü",      .replace = "Lorem ipsum (ÄÖÜäöüß@µ) sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.", .result = "Lorem ipsum (ÄÖÜäöüß@µ) sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua." },
        { .assignment = "ÄÖÜäöü", .search = "ÄÄÄ",         .replace = "1", .result = "ÄÖÜäöü" },
        { .assignment = "ÄÖÜäöü", .search = "ÄÖÜäöü_1",    .replace = "1", .result = "ÄÖÜäöü" },
        { .assignment = "ÄÖÜäöü", .search = "Lorem ipsum (ÄÖÜäöüß@µ) sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.", .replace = "ÄÄÄ", .result = "ÄÖÜäöü" },
        { .assignment = "ÄÖÜäöü", .search = "ÄÖÜäöü",      .replace = "ÜÜÜ", .result = "ÜÜÜ" },
        { .assignment = "ÄÖÜäöü", .search = "ÄÖÜäöü",      .replace = "ÄÖÜäöü", .result = "ÄÖÜäöü" },
        { .assignment = "ÄÖÜäöü", .search = "ÄÖÜäöü",      .replace = "ÜÖÄüöäµ", .result = "ÜÖÄüöäµ" },
        { .assignment = "ÄÖÜäöü", .search = "Lorem ipsum (ÄÖÜäöüß@µ) sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.", .replace = "ÜÜÜÜÜÜ", .result = "ÄÖÜäöü" },
    };

    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);
    int length = sizeof(texts) / sizeof(struct ComparisonTexts);

    for (int i = 0; i < length; i++)
    {
        var1->set(&var1, texts[i].assignment, &errorNumber, __FILE__, __LINE__);
        replaceDynamicText(&var1, texts[i].search, texts[i].replace, __FILE__, __LINE__);

        if (0 == isExactTextMatch(var1->getBytesPointer(&var1, &errorNumber), texts[i].result, __FILE__, __LINE__))
        {
            abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
        }
    }

    var1->free(&var1, &errorNumber, __FILE__, __LINE__);

    if (
        (NULL == var1)
        && (globaleAmountOfAllocations == globaleAmountOfFrees)
        && (0 == globaleAmountOfAllocatedMemoryInBytes)
    )
    {
        printf("[SUCCESS] %s\n", titleFromTest);
        return;
    }

    abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
}


static void
executeTest7(void)
{
    char* titleFromTest = "#07 Recursive examples with multi-letter texts.";

    int errorNumber = 0;
    struct ComparisonTexts texts[] = {
        { .assignment = "wooden chair (red)", .search = "(red)",      .replace = "<span style=\"color: red; font-weight: bold;\">(red)</span>", .result = "wooden chair <span style=\"color: red; font-weight: bold;\">(red)</span>" },
        { .assignment = "This black chair is the 2nd variant of the red chair (ÜÖÄäöüµß@). Soluta nobis eleifend option congue nihil imperdiet doming id quod mazim placerat facer possim assum.", .search = "ü", .replace = "<span class=\"bold\">ü</span>", .result = "This black chair is the 2nd variant of the red chair (ÜÖÄäö<span class=\"bold\">ü</span>µß@). Soluta nobis eleifend option congue nihil imperdiet doming id quod mazim placerat facer possim assum." },
        { .assignment = "The name of the colour is green!", .search = "green", .replace = "<span>red</span>", .result = "The name of the colour is <span>red</span>!" },
    };

    struct DynamicText* var1 = allocateDynamicText(&errorNumber, __FILE__, __LINE__);
    int length = sizeof(texts) / sizeof(struct ComparisonTexts);

    for (int i = 0; i < length; i++)
    {
        var1->set(&var1, texts[i].assignment, &errorNumber, __FILE__, __LINE__);
        replaceDynamicText(&var1, texts[i].search, texts[i].replace, __FILE__, __LINE__);

        if (0 == isExactTextMatch(var1->getBytesPointer(&var1, &errorNumber), texts[i].result, __FILE__, __LINE__))
        {
            abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
        }
    }

    var1->free(&var1, &errorNumber, __FILE__, __LINE__);

    if (
        (NULL == var1)
        && (globaleAmountOfAllocations == globaleAmountOfFrees)
        && (0 == globaleAmountOfAllocatedMemoryInBytes)
    )
    {
        printf("[SUCCESS] %s\n", titleFromTest);
        return;
    }

    abortTestWithErrorMessage(titleFromTest, __func__, __FILE__, __LINE__);
}


int
main(void)
{
    printf("\n");
    printf("TEST SUITE: replaceDynamicText function\n");

    executeTest1();
    executeTest2();
    executeTest3();
    executeTest4();
    executeTest5();
    executeTest6();
    executeTest7();

    return EXIT_SUCCESS;
}
