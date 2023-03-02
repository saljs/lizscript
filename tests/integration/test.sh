#!/bin/bash

# test.sh
# Test runner for integration tests

FAILED=0
TOTAL=0

for SCRIPT in tests/integration/*.ls
do
    echo -n "$SCRIPT"
    EVAL=$(./build/liz $SCRIPT)
    EXP="tests/integration/expected/$(basename $SCRIPT | sed 's/\.ls$/.txt/')"
    
    if [[ "$EVAL" == "$(cat $EXP)" ]]
    then
        echo -e "\t\e[32mPASSED\e[0m"
    else
        echo -e "\t\e[31mFAILED\e[0m"
        let "FAILED=FAILED+1"
    fi
    let "TOTAL=TOTAL+1"
done

if [[ $FAILED > 0 ]]
then
    echo "$FAILED tests failed out of $TOTAL."
    exit 1
else
    echo "All tests pass"
fi

exit 0
