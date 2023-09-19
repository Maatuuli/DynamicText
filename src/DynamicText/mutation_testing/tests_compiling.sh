#!/bin/bash

# Include configs for compiling.
. ../../../tests/config_for_compiling.sh

$PATH_FOR_GCC $PARAMETERS ../unit_tests/DynamicTextPositiveTests.c --output DynamicTextPositiveTests.out
$PATH_FOR_GCC $PARAMETERS ../unit_tests/DynamicTextNegativeTests.c --output DynamicTextNegativeTests.out
