#!/bin/bash

PARAMETERS_WITHOUT_ADDRESS_SANITIZER="-O3 -g -Wall -Werror -Wpedantic -Winline"
PARAMETERS="${PARAMETERS_WITHOUT_ADDRESS_SANITIZER} -fsanitize=address,undefined,leak -fsanitize-address-use-after-scope"

PATH_FOR_GCC="/usr/bin/gcc"

