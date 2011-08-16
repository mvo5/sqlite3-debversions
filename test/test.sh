#!/bin/sh

EXPECTED=$(cat test.expected)
res=$(sqlite3 < test.sql)
if [ "$res" != "$EXPECTED" ]; then
    echo "test failed, got:"
    echo "$res"
    echo "expected:"
    echo "$EXPECTED"
    exit 1
fi
