#!/bin/bash

# Include configs for compiling.
. ../../../tests/config_for_compiling.sh

$PATH_FOR_GCC $PARAMETERS ../unit_tests/AssociativeDynamicTextListPositiveTests.c --output AssociativeDynamicTextListPositiveTests.out
$PATH_FOR_GCC $PARAMETERS ../unit_tests/AssociativeDynamicTextListNegativeTests.c --output AssociativeDynamicTextListNegativeTests.out
