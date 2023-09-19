#!/bin/bash

# Include configs for compiling.
. ../../../tests/config_for_compiling.sh

$PATH_FOR_GCC $PARAMETERS AssociativeDynamicTextFuzzing.c --output AssociativeDynamicTextFuzzing.out && ./AssociativeDynamicTextFuzzing.out
