#!/bin/bash

BUILD_DIR='build'

function gen_test_report {
    if [ -d "$BUILD_DIR" ]; then
        # Generate report
        lcov -c --directory $BUILD_DIR --output-file $BUILD_DIR/gtest_coverage.info

        # Convert to html
        genhtml $BUILD_DIR/gtest_coverage.info --output-directory $BUILD_DIR/out
    else
        echo "No build folder found!"
    fi
}

function rem_test_report {
    if [ -d "$BUILD_DIR" ]; then
        if [ -f "$BUILD_DIR/gtest_coverage.info" ]; then
            rm $BUILD_DIR/gtest_coverage.info
        fi
        if [ -d "$BUILD_DIR/out" ]; then
            rm -rf $BUILD_DIR/out
        fi
    fi
}

function usage {
    echo "Usage: gen_test_report.sh [options]"
    echo "  -g    Generate"
    echo "  -c    Clean"
    echo "  -h    Help"
}

if [ $# -eq 0 ]; then
    gen_test_report
    exit 1;
fi

while getopts "gch" opt; do
    case "${opt}" in
        g)
            gen_test_report
            ;;
        c)
            rem_test_report
            ;;
        h)
            usage
            ;;
    esac
done
