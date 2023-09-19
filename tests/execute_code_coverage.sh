#!/bin/bash

echo ""
echo ""
echo "### CREATE DATA FOR CODE COVERAGE:"

lcov --base-directory . --directory . --capture --output-file ./lcov_intermediate.info
lcov --remove ./lcov_intermediate.info '*/tests/*' -o ./lcov_result.info
lcov --remove ./lcov_result.info '*/unit_tests/*' -o ./lcov_result.info
lcov --remove ./lcov_result.info '*/usr/*' -o ./lcov_result.info

rm -rf ./html/*

genhtml -o html ./lcov_result.info

rm ./*.gcda ./*.gcno ./*.out ./*.info
