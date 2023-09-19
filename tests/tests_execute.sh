#!/bin/bash

echo ""
echo "### TEST SUITES:"

./tests_for_AssociativeDynamicTextPositive.out &&
./tests_for_AssociativeDynamicTextNegative.out &&
./tests_for_AssociativeDynamicTextListPositive.out &&
./tests_for_AssociativeDynamicTextListNegative.out &&
./tests_for_DynamicTextPositive.out &&
./tests_for_DynamicTextNegative.out &&
./tests_for_DynamicTextListPositive.out &&
./tests_for_DynamicTextListNegative.out &&
./tests_for_cgi_functions.out
./tests_for_oksa.out
./tests_for_oksa_exit1.out
./tests_for_explodeDynamicText.out
./tests_for_explodeDynamicText_exit1.out
./tests_for_explodeDynamicText_exit2.out
./tests_for_findPositionInDynamicTextPositive.out
./tests_for_findPositionInDynamicTextNegative.out
./tests_for_getSubstringInBytesFromDynamicText.out
./tests_for_getSubstringInBytesFromDynamicText_exit1.out
./tests_for_getSubstringInBytesFromDynamicText_exit2.out
./tests_for_getSubstringInBytesFromDynamicText_exit3.out
./tests_for_getSubstringInBytesFromDynamicText_exit4.out
./tests_for_getSubstringInBytesFromDynamicText_exit5.out
./tests_for_getSubstringInBytesFromDynamicText_exit6.out
./tests_for_getSubstringInBytesFromDynamicText_exit7.out
./tests_for_getSubstringInBytesFromDynamicText_exit8.out
./tests_for_implodeListForDynamicText.out
./tests_for_replaceDynamicText.out
./tests_for_replaceDynamicText_exit1.out
./tests_for_replaceDynamicText_exit2.out
./tests_for_replaceDynamicText_exit3.out
./tests_for_replaceDynamicText_exit4.out
./tests_for_replaceDynamicText_exit5.out
./tests_for_replaceDynamicText_exit6.out
./tests_for_stripTagsInDynamicText.out


echo ""
echo "END OF TESTING:"
echo "All tests were executed!"
