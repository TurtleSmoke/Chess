#!/usr/bin/env bash
while IFS= read -r line
do
    touch "clang-tidy-tmp"

    if echo "$line" | grep -q "llvm" ; then
        IFS= read -r "actual"
        IFS= read -r "tild"
        IFS= read -r "expected"
        actualFiltered=$(echo "$actual" | grep -oE '[^ ]+$')
        expectedFiltered=$(echo "$expected" | grep -oE 'CHESS.*$')

        if [ "$actualFiltered" = "$expectedFiltered" ]; then
            continue
        else
            {
                echo "$line"
                echo "$actual"
                echo "$tild"
                echo "$expected" | sed 's/[^ ]*CHESS/CHESS/g'
            } >> clang-tidy-tmp
        fi
    else
        echo "$line" >> clang-tidy-tmp
    fi
done < clang-tidy-output

if [ -f clang-tidy-tmp ]; then
  mv clang-tidy-tmp clang-tidy-output
fi
