while IFS= read -r line
do
    echo "$line" | grep -q "llvm"
    if [ $? -eq 0 ]; then
        IFS= read "actual"
        IFS= read "tild"
        IFS= read "expected"
        actualFiltered=$(echo $actual | grep -oE '[^ ]+$')
        expectedFiltered=$(echo $expected | grep -oE 'CHESS.*$')

        if [ "$actualFiltered" = "$expectedFiltered" ]; then
            continue
        else
            echo "$line" >> clang-tidy-tmp
            echo "$actual" >> clang-tidy-tmp
            echo "$tild" >> clang-tidy-tmp
            echo "$expected" | sed 's/[^ ]*CHESS/CHESS/g' >> clang-tidy-tmp
        fi
    else
        echo "$line"
    fi
done < clang-tidy-output

mv clang-tidy-tmp clang-tidy-output
