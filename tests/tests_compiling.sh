#!/bin/bash

PARAMETERS_WITHOUT_ADDRESS_SANITIZER="-O3 -g -Wall -Wpedantic -Winline -fprofile-arcs -ftest-coverage -lgcov"
PARAMETERS="${PARAMETERS_WITHOUT_ADDRESS_SANITIZER} -fsanitize=address,undefined,leak -fsanitize-address-use-after-scope"

PATH_FOR_GCC="/usr/bin/gcc"

# Using subshells in Bash to compile all unit tests in parallel and usage of "wait" for syncing at the end!

$PATH_FOR_GCC $PARAMETERS ../src/DynamicText/unit_tests/DynamicTextPositiveTests.c --output tests_for_DynamicTextPositive.out &
$PATH_FOR_GCC $PARAMETERS ../src/DynamicText/unit_tests/DynamicTextNegativeTests.c --output tests_for_DynamicTextNegative.out &
$PATH_FOR_GCC $PARAMETERS ../src/DynamicTextList/unit_tests/DynamicTextListPositiveTests.c --output tests_for_DynamicTextListPositive.out &
$PATH_FOR_GCC $PARAMETERS ../src/DynamicTextList/unit_tests/DynamicTextListNegativeTests.c --output tests_for_DynamicTextListNegative.out &
$PATH_FOR_GCC $PARAMETERS ../src/AssociativeDynamicText/unit_tests/AssociativeDynamicTextPositiveTests.c --output tests_for_AssociativeDynamicTextPositive.out &
$PATH_FOR_GCC $PARAMETERS ../src/AssociativeDynamicText/unit_tests/AssociativeDynamicTextNegativeTests.c --output tests_for_AssociativeDynamicTextNegative.out &
$PATH_FOR_GCC $PARAMETERS ../src/AssociativeDynamicTextList/unit_tests/AssociativeDynamicTextListPositiveTests.c --output tests_for_AssociativeDynamicTextListPositive.out &
$PATH_FOR_GCC $PARAMETERS ../src/AssociativeDynamicTextList/unit_tests/AssociativeDynamicTextListNegativeTests.c --output tests_for_AssociativeDynamicTextListNegative.out &
$PATH_FOR_GCC $PARAMETERS ../src/oksa/unit_tests/main.c --output tests_for_oksa.out &
$PATH_FOR_GCC $PARAMETERS ../src/oksa/unit_tests/exit1.c --output tests_for_oksa_exit1.out &
$PATH_FOR_GCC $PARAMETERS ../src/cgi_functions/unit_tests/main.c --output tests_for_cgi_functions.out &
$PATH_FOR_GCC $PARAMETERS ../src/text_functions/unit_tests/explodeDynamicText.c --output tests_for_explodeDynamicText.out &
$PATH_FOR_GCC $PARAMETERS ../src/text_functions/unit_tests/explodeDynamicText_exit1.c --output tests_for_explodeDynamicText_exit1.out &
$PATH_FOR_GCC $PARAMETERS ../src/text_functions/unit_tests/explodeDynamicText_exit2.c --output tests_for_explodeDynamicText_exit2.out &
$PATH_FOR_GCC $PARAMETERS ../src/text_functions/unit_tests/findPositionInDynamicTextPositiveTests.c --output tests_for_findPositionInDynamicTextPositive.out &
$PATH_FOR_GCC $PARAMETERS ../src/text_functions/unit_tests/findPositionInDynamicTextNegativeTests.c --output tests_for_findPositionInDynamicTextNegative.out &
$PATH_FOR_GCC $PARAMETERS ../src/text_functions/unit_tests/getSubstringInBytesFromDynamicText.c --output tests_for_getSubstringInBytesFromDynamicText.out &
$PATH_FOR_GCC $PARAMETERS ../src/text_functions/unit_tests/getSubstringInBytesFromDynamicText_exit1.c --output tests_for_getSubstringInBytesFromDynamicText_exit1.out &
$PATH_FOR_GCC $PARAMETERS ../src/text_functions/unit_tests/getSubstringInBytesFromDynamicText_exit2.c --output tests_for_getSubstringInBytesFromDynamicText_exit2.out &
$PATH_FOR_GCC $PARAMETERS ../src/text_functions/unit_tests/getSubstringInBytesFromDynamicText_exit3.c --output tests_for_getSubstringInBytesFromDynamicText_exit3.out &
$PATH_FOR_GCC $PARAMETERS ../src/text_functions/unit_tests/getSubstringInBytesFromDynamicText_exit4.c --output tests_for_getSubstringInBytesFromDynamicText_exit4.out &
$PATH_FOR_GCC $PARAMETERS ../src/text_functions/unit_tests/getSubstringInBytesFromDynamicText_exit5.c --output tests_for_getSubstringInBytesFromDynamicText_exit5.out &
$PATH_FOR_GCC $PARAMETERS ../src/text_functions/unit_tests/getSubstringInBytesFromDynamicText_exit6.c --output tests_for_getSubstringInBytesFromDynamicText_exit6.out &
$PATH_FOR_GCC $PARAMETERS ../src/text_functions/unit_tests/getSubstringInBytesFromDynamicText_exit7.c --output tests_for_getSubstringInBytesFromDynamicText_exit7.out &
$PATH_FOR_GCC $PARAMETERS ../src/text_functions/unit_tests/getSubstringInBytesFromDynamicText_exit8.c --output tests_for_getSubstringInBytesFromDynamicText_exit8.out &
$PATH_FOR_GCC $PARAMETERS ../src/text_functions/unit_tests/implodeListForDynamicText.c --output tests_for_implodeListForDynamicText.out &
$PATH_FOR_GCC $PARAMETERS ../src/text_functions/unit_tests/replaceDynamicText.c --output tests_for_replaceDynamicText.out &
$PATH_FOR_GCC $PARAMETERS ../src/text_functions/unit_tests/replaceDynamicText_exit1.c --output tests_for_replaceDynamicText_exit1.out &
$PATH_FOR_GCC $PARAMETERS ../src/text_functions/unit_tests/replaceDynamicText_exit2.c --output tests_for_replaceDynamicText_exit2.out &
$PATH_FOR_GCC $PARAMETERS ../src/text_functions/unit_tests/replaceDynamicText_exit3.c --output tests_for_replaceDynamicText_exit3.out &
$PATH_FOR_GCC $PARAMETERS ../src/text_functions/unit_tests/replaceDynamicText_exit4.c --output tests_for_replaceDynamicText_exit4.out &
$PATH_FOR_GCC $PARAMETERS ../src/text_functions/unit_tests/replaceDynamicText_exit5.c --output tests_for_replaceDynamicText_exit5.out &
$PATH_FOR_GCC $PARAMETERS ../src/text_functions/unit_tests/replaceDynamicText_exit6.c --output tests_for_replaceDynamicText_exit6.out &
$PATH_FOR_GCC $PARAMETERS ../src/text_functions/unit_tests/stripTagsInDynamicText.c --output tests_for_stripTagsInDynamicText.out &

# Wait until all subshells are finished with compilation!
wait

