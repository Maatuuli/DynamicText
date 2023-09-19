#!/bin/bash

# Include configs for compiling.
. ../../../tests/config_for_compiling.sh

$PATH_FOR_GCC $PARAMETERS ../unit_tests/DynamicTextListPositiveTests.c --output DynamicTextListPositiveTests.out
$PATH_FOR_GCC $PARAMETERS ../unit_tests/DynamicTextListNegativeTests.c --output DynamicTextListNegativeTests.out
