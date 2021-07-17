#!/bin/python3

import sys
import re

def factorial(nb):
    if nb <= 0:
        return 1
    else:
        return nb * factorial(nb-1)

def proba_yams(n, total):
    return factorial(total) / (factorial(n) * factorial(total-n)) * pow(1/6, n) * pow(5/6, total-n) * 100

def pair(dices, value):
    rm = 0
    for i in dices:
        if i == value:
            rm = rm + 1

    proba = rm < 2 and proba_yams(2-rm, 5-rm) + proba_yams(3-rm, 5-rm) + proba_yams(4-rm, 5-rm) + proba_yams(5-rm, 5-rm) or 100
    print(f"Chances to get a {value} pair: {proba:.02f}%")

def three(dices, value):
    rm = 0
    for i in dices:
        if i == value:
            rm = rm + 1

    proba = rm < 3 and proba_yams(3-rm, 5-rm) + proba_yams(4-rm, 5-rm) + proba_yams(5-rm, 5-rm) or 100
    print(f"Chances to get a {value} three-of-a-kind: {proba:.02f}%")

def four(dices, value):
    rm = 0
    for i in dices:
        if i == value:
            rm = rm + 1

    proba = rm < 4 and proba_yams(4-rm, 5-rm) + proba_yams(5-rm, 5-rm) or 100
    print(f"Chances to get a {value} four-of-a-kind: {proba:.02f}%")

def five(dices, value):
    rm = 0
    for i in dices:
        if i == value:
            rm = rm + 1

    print(f"Chances to get a {value} yams: {proba_yams(5-rm,5-rm):.02f}%")

def straight(dices, value):
    v = {1:1,2:1,3:1,4:1,5:1,6:1}
    v[value == 5 and 6 or 1] = None
    l = 5

    for i in dices:
        if i in v and v[i] == 1:
            v[i] = 0 
            l = l-1

    proba = factorial(l) * pow(1/6, l) * 100
    print(f"Chances to get a {value} straight: {proba:.02f}%")

def full_house(dices, value, value2):
    if value == value2:
        exit(84)
    v = {}
    v[value] = 3
    v[value2] = 2
    l = 5

    for i in dices:
        if i in v and v[i] > 0:
            v[i] = v[i] - 1; l = l-1


    proba = factorial(l) / (factorial(v[value]) * factorial(v[value2])) * pow(1/6, l) * 100
    print(f"Chances to get a {value} full of {value2}: {proba:.02f}%")

def yams():

    if (len(sys.argv) != 7):
        exit(84)

    try:
        dice = [int(sys.argv[1]), int(sys.argv[2]), int(sys.argv[3]), int(sys.argv[4]), int(sys.argv[5])]
    except:
        print("Unexpected character while number expected")
        exit(84)

    for d in dice:
        if d < 0 or d > 6:
            exit(84)

    value = re.search("\\d", sys.argv[6])
    if (re.match("pair_[1-6]$", sys.argv[6])):
        pair(dice, int(value.group()))
    elif (re.match("three_[1-6]$", sys.argv[6])):
        three(dice, int(value.group()))
    elif (re.match("four_[1-6]$", sys.argv[6])):
        four(dice, int(value.group()))
    elif (re.match("yams_[1-6]$", sys.argv[6])):
        five(dice, int(value.group()))
    elif (re.match("straight_[56]$", sys.argv[6])):
        straight(dice, int(value.group()))
    elif (re.match("full_[1-6]_[1-6]$", sys.argv[6])):
        value2 = re.search("\\d$", sys.argv[6])
        full_house(dice, int(value.group()), int(value2.group()))
    else:
        exit(84)

yams()
