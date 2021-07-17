#! /usr/bin/env bash

ERROR="\e[1;31mFAILURE\e[0m"
SUCCESS="\e[1;32mSUCCESS\e[0m"
TITLE="\n\t\e[1;35m"
NAME="\e[1;36m"
ENDTITLE="\e[0m\n"
ENDNAME="\e[0m\t"

DIR_TEST=`echo "$0" | sed -r "s#/[^/]+\\$##"`
HAL="${DIR_TEST}/../hal"

testHALError() # title files...
{
    title="$1"
    shift 1

    args=""
    for words; do
        args+=" ${DIR_TEST}/${words}"
    done

    result=`${HAL} $args`
    ret=$?

    if [ $ret -ne 84 ]; then
        echo -e "${NAME}${title}${ENDNAME} ${ERROR}: Expected exit status 84, got $ret"
    else
        echo -e "${NAME}${title}${ENDNAME} ${SUCCESS}"
    fi
}

testHAL() # title result files...
{
    title="$1"
    expect="$2"
    shift 2

    args=""
    for words; do
        args+=" ${DIR_TEST}/${words}"
    done

    result=`${HAL} $args`
    ret=$?

    if [ $ret -ne 0 ]; then
        echo -e "${NAME}${title}${ENDNAME} ${ERROR}: Unexpected exit status $ret"
    elif [[ "$result" = "$expect" ]]; then
        echo -e "${NAME}${title}${ENDNAME} ${SUCCESS}"
    else
        echo -e "${NAME}${title}${ENDNAME} ${ERROR}: Expected \"${expect}\", but got \"$result\""
    fi
}

echo -e "${TITLE}Error Management${ENDTITLE}"
    testHALError "No argument"
    testHALError "Not a file" "."
    testHALError "Empty file" "error/empty"
    testHALError "Invalid file" "error/error"
    testHALError "One good file and one bad file" "defineA" "error/error"
    testHALError "Unknow symbol" "justA"
    testHALError "Valid expression + invalid expression" "error/validInvalid"

echo -e "${TITLE}Basic Test${ENDTITLE}"
    testHAL "Basic number 1" "42" "basics/number1"
    testHAL "Basic number 2" "-1241562" "basics/number2"
    testHAL "Basic boolean 1" "#t" "basics/bool1"
    testHAL "Basic boolean 2" "#f" "basics/bool2"
    testHAL "Basic list 1" "(1 2 3 4 5)" "basics/list1"
    testHAL "Basic list 2" "()" "basics/list2"
    testHAL "Basic list 3" "(4 #t a 6 . 2)" "basics/list3"
    testHAL "Complex list" "((4) #t (1 . 3) 6 . 2)" "basics/complexList"
    testHAL "Several commands" "42
1" "basics/basicsx2"
    testHAL "Several files" "42
#f" "basics/number1" "basics/bool2"
    testHAL "Symbol keeps" "5" "defineA" "justA"
    testHAL "Quote number" "1" "basics/quoteNb"
    testHAL "Quote list" "()" "basics/quoteList"
    testHAL "Quote function" "(cons 1 2)" "basics/quoteFn"
    testHAL "Quote quote" "'1" "basics/quoteQuote"
    testHAL "SugarQuote quote" "'1" "basics/quoteQuote2"
    testHALError "Error Quote: no argument" "basics/errorQuote1"
    testHALError "Error Quote: too much argument" "basics/errorQuote2"

echo -e "${TITLE}Test List${ENDTITLE}"
    testHAL "Cons 1" "(1 . 2)" "list/defineAList1" "justA"
    testHAL "Cons 2" "(1 2 3)" "list/defineAList2" "justA"
    testHAL "Cons 3" "((1 2 . 3) 4)" "list/defineAList3" "justA"
    testHAL "Cons 4" "(1)" "list/defineAList4" "justA"
    testHAL "Car 1" "1" "list/defineAList1" "list/carA"
    testHAL "Car 2" "1" "list/defineAList2" "list/carA"
    testHAL "Car 3" "(1 2 . 3)" "list/defineAList3" "list/carA"
    testHAL "Car 4" "1" "list/defineAList4" "list/carA"
    testHAL "Cdr 1" "2" "list/defineAList1" "list/cdrA"
    testHAL "Cdr 2" "(2 3)" "list/defineAList2" "list/cdrA"
    testHAL "Cdr 3" "(4)" "list/defineAList3" "list/cdrA"
    testHAL "Cdr 4" "()" "list/defineAList4" "list/cdrA"
    testHALError "Error cons: not enough arg" "list/errorCons1"
    testHALError "Error cons: not enough arg 2" "list/errorCons2"
    testHALError "Error cons: too much arg" "list/errorCons3"
    testHALError "Error car: not enough arg" "list/errorCar1"
    testHALError "Error car: too much arg" "list/errorCar4"
    testHALError "Error car: not a list" "list/errorCar2"
    testHALError "Error car: empty list" "list/errorCar3"
    testHALError "Error cdr: not enough arg" "list/errorCdr1"
    testHALError "Error cdr: too much arg" "list/errorCdr4"
    testHALError "Error cdr: not a list" "list/errorCdr2"
    testHALError "Error cdr: empty list" "list/errorCdr3"

echo -e "${TITLE}Test Arithmetic${ENDTITLE}"
    testHAL "Plus: one number" "1" "arithm/plus5"
    testHAL "Plus: two numbers" "3" "arithm/plus1"
    testHAL "Plus: five numbers" "15" "arithm/plus2"
    testHAL "Plus: negativ number" "-2" "arithm/plus3"
    testHAL "Plus: no number" "0" "arithm/plus4"
    testHAL "Plus: with variables" "6" "defineA" "arithm/plus6"
    testHAL "Minus: one number" "-1" "arithm/minus4"
    testHAL "Minus: two numbers" "4" "arithm/minus1"
    testHAL "Minus: five numbers" "46" "arithm/minus2"
    testHAL "Minus: negativ number" "2" "arithm/minus3"
    testHAL "Minus: with variables" "7" "defineA" "arithm/minus5"
    testHAL "Times: one number" "5" "arithm/times4"
    testHAL "Times: two numbers" "10" "arithm/times1"
    testHAL "Times: five numbers" "2310" "arithm/times2"
    testHAL "Times: negativ number" "-10" "arithm/times3"
    testHAL "Times: no number" "1" "arithm/times6"
    testHAL "Times: with variables" "20" "defineA" "arithm/times5"
    testHAL "Div: no round result" "5" "arithm/div1"
    testHAL "Div: with round result 1" "3" "arithm/div2"
    testHAL "Div: with round result 2" "6" "arithm/div3"
    testHAL "Div: negativ number" "-3" "arithm/div4"
    testHAL "Div: with variable" "19" "defineA" "arithm/div5"
    testHAL "Mod: simple 1" "0" "arithm/mod1"
    testHAL "Mod: simple 2" "1" "arithm/mod2"
    testHAL "Mod: modulo 1" "0" "arithm/mod7"
    testHAL "Mod: left negativ number" "2" "arithm/mod3"
    testHAL "Mod: right negativ number" "1" "arithm/mod4"
    testHAL "Mod: both negativs numbers" "2" "arithm/mod5"
    testHAL "Mod: with variable" "2" "defineA" "arithm/mod6"
    testHALError "Error Plus: not a number" "arithm/errorPlus1"
    testHALError "Error Plus: numbers with not a number" "arithm/errorPlus2"
    testHALError "Error Minus: no number" "arithm/errorMinus1"
    testHALError "Error Minus: not a number" "arithm/errorMinus2"
    testHALError "Error Times: not a number" "arithm/errorTimes"
    testHALError "Error Div: not a number" "arithm/errorDiv1"
    testHALError "Error Div: not enough numbers" "arithm/errorDiv2"
    testHALError "Error Div: not enough numbers 2" "arithm/errorDiv3"
    testHALError "Error Div: too much numbers" "arithm/errorDiv4"
    testHALError "Error Div: division by 0" "arithm/errorDiv5"
    testHALError "Error Mod: not a number" "arithm/errorMod1"
    testHALError "Error Mod: not enough numbers" "arithm/errorMod2"
    testHALError "Error Mod: not enough numbers 2" "arithm/errorMod3"
    testHALError "Error Mod: too much numbers" "arithm/errorMod4"
    testHALError "Error Mod: modulo 0" "arithm/errorMod5"

echo -e "${TITLE}Test Condition${ENDTITLE}"
    testHAL "Eq?: Same: numbers" "#t" "cond/eqSame1"
    testHAL "Eq?: Same: symbols" "#t" "cond/eqSame2"
    testHAL "Eq?: Same: number + quoted number" "#t" "cond/eqSame3"
    testHAL "Eq?: Same: variable + number" "#t" "defineA" "cond/eqSame4"
    testHAL "Eq?: Diff: different number" "#f" "cond/eqDiff1"
    testHAL "Eq?: Diff: different symbols" "#f" "cond/eqDiff5"
    testHAL "Eq?: Diff: 0 and False" "#f" "cond/eqDiff2"
    testHAL "Eq?: Diff: number + number as list" "#f" "cond/eqDiff3"
    testHAL "Eq?: Diff: variable + var's symbol" "#f" "defineA" "cond/eqDiff4"
    testHAL "Eq?: differents lists" "#f" "cond/eqList1"
    testHAL "Eq?: same lists" "#f" "cond/eqList2"
    testHAL "Eq?: empty lists" "#t" "cond/eqList3"
    testHAL "Eq?: empty list + non-empty list 1" "#f" "cond/eqList4"
    testHAL "Eq?: empty list + non-empty list 2" "#f" "cond/eqList5"
    testHAL "Lower Than: lower" "#t" "cond/lt1"
    testHAL "Lower Than: equal" "#f" "cond/lt2"
    testHAL "Lower Than: greater" "#f" "cond/lt3"
    testHAL "Lower Than: negativ number 1" "#t" "cond/lt4"
    testHAL "Lower Than: negativ number 2" "#f" "cond/lt5"
    testHAL "Lower Than: variable" "#t" "defineA" "cond/lt6"
    testHAL "Atom?: bool" "#t" "cond/atom1"
    testHAL "Atom?: number" "#t" "cond/atom2"
    testHAL "Atom?: symbol" "#t" "cond/atom3"
    testHAL "Atom?: empty list" "#t" "cond/atom4"
    testHAL "Atom?: non-empty list" "#f" "cond/atom5"
    testHAL "Atom?: quote" "#f" "cond/atom6"
    testHAL "Atom?: variable" "#t" "defineA" "cond/atom7"
    testHAL "Cond: if true" "first" 'cond/cond1'
    testHAL "Cond: if false elsif true" "second" 'cond/cond2'
    testHAL "Cond: if false elsif false elsif true" "third" 'cond/cond3'
    testHAL "Cond: if true elsif false" "first" 'cond/cond4'
    testHAL "Cond: if true elsif true" "first" 'cond/cond5'
    testHAL "Cond: if 1" "first" "defineB" 'cond/cond6'
    testHAL "Cond: if 0" "first" "defineB" 'cond/cond7'
    testHAL "Cond: if false" "" 'cond/cond8'
    testHAL "Cond: condition without body" "#t" 'cond/cond9'
    testHALError "Error Eq?: not enough arguments" "cond/errorEq1"
    testHALError "Error Eq?: too much arguments" "cond/errorEq2"
    testHALError "Error Lower Than: not enough arguments" "cond/errorLt1"
    testHALError "Error Lower Than: too much arguments" "cond/errorLt2"
    testHALError "Error Lower Than: not a number" "cond/errorLt3"
    testHALError "Error Atom?: not enough arguments" "cond/errorAtom1"
    testHALError "Error Atom?: too much arguments" "cond/errorAtom2"
    testHALError "Error Cond: no argument" "cond/errorCond1"
    testHALError "Error Cond: argument not a non-empty list" "cond/errorCond2"
    testHALError "Error Cond: argument is a list-dotted" "cond/errorCond3"
    testHALError "Error Cond: argument's size > 2" "cond/errorCond4"

echo -e "${TITLE}Test Define Let Lambda${ENDTITLE}"
    testHAL "Let: simple execute" "3" "special/let1"
    testHAL "Let: two arguments" "-3" "special/let2"
    testHAL "Let: function" "3" "special/let3"
    testHAL "Lambda: simple add" "#<procedure>" "special/lambda1"
    testHAL "Lambda: simple add with args" "#<procedure>" "special/lambda2"
    testHAL "Lambda: define and execute lambda without args" "3" "special/lambda3"
    testHAL "Lambda: define and execute lambda with args" "32" "special/lambda4"
    testHAL "Define: simple var 1" "5" "defineA" "justA"
    testHAL "Define: simple var 2" "((1 2 . 3) 4)" "list/defineAList3" "justA"
    testHAL "Define: lambda without args" "#<procedure>" "special/defineALambda1" "justA"
    testHAL "Define: execute lambda without args" "3" "special/defineALambda1" "special/execA"
    testHAL "Define: execute lambda with args" "15" "special/defineALambda2" "special/execAArgs"
    testHAL "Define: function without args" "#<procedure>" "special/defineAFunct1" "justA"
    testHAL "Define: execute function without args" "HelloWorld" "special/defineAFunct1" "special/execA"
    testHAL "Define: execute function with args" "-5" "special/defineAFunct2" "special/execAArgs"

echo -e "${TITLE}Test Execution${ENDTITLE}"
    testHAL "Factoriel" "3628800" "factoriel"
    testHAL "Fibonacci" "10946" "fibonacci"
    testHAL "Merge Sort" "(1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42)" "mergeSort"