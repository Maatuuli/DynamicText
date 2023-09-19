#!/bin/bash

# Include configs for compiling.
. ../../../tests/config_for_compiling.sh

$PATH_FOR_GCC $PARAMETERS ../unit_tests/AssociativeDynamicTextPositiveTests.c --output AssociativeDynamicTextPositiveTests.out
$PATH_FOR_GCC $PARAMETERS ../unit_tests/AssociativeDynamicTextNegativeTests.c --output AssociativeDynamicTextNegativeTests.out
