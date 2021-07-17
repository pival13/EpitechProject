#!/usr/bin/env python3

import sys
import collections
# import matplotlib.pyplot as plt
import math


def average(values, period=None):
    if not period:
        period = len(values)
    if len(values) < period:
        return math.nan
    average = 0
    for v in range(len(values) - period, len(values)):
        average += values[v]
    return average / period


def deviation(values, period=None):
    if not period:
        period = len(values)
    if len(values) < period:
        return math.nan
    ave = average(values, period)

    var = 0
    for v in range(len(values) - period, len(values)):
        var += math.pow(values[v] - ave, 2)
    return math.sqrt(var / period)


POURCENTAGE_EXPO = 0.90


def expoMovingAverage(values, lastValue, period, maxI=None):
    if maxI == None:
        maxI = len(values)
    a = 1 - pow(1 - POURCENTAGE_EXPO, 1 / period)
    if maxI == 0:
        return lastValue
    else:
        return a * values[maxI - 1] + (1 - a) * expoMovingAverage(values, lastValue, period, maxI - 1)


def doubleExpoMovingAverage(values, lastValue, period):
    l = collections.deque(maxlen=period + 1)
    for i in range(0, len(values)):
        if i >= period:
            l += [expoMovingAverage(values, l[0], period, i + 1)]
        else:
            l += [expoMovingAverage(values, values[0], period, i + 1)]
    return 2 * l[-1] - expoMovingAverage(l, lastValue, period)


def tripleExpoMovingAverage(values, lastValue, period):
    ema1 = []
    ema2 = []
    for i in range(len(values)):
        if i >= period:
            ema1 += [expoMovingAverage(values, ema1[i - period], period, i + 1)]
            ema2 += [expoMovingAverage(ema1, ema2[i - period], period)]
        else:
            ema1 += [expoMovingAverage(values, values[0], period, i + 1)]
            ema2 += [expoMovingAverage(ema1, ema1[0], period)]    
    return 3 * ema1[-1] - 3 * ema2[-1] + expoMovingAverage(ema2, lastValue, period)


def main(arg):
    if len(arg) == 2 and arg[1] == "-h":
        print(open("helper.txt").read())
        return
    elif len(arg) != 2 or not arg[1].isnumeric() or int(arg[1]) < 2:
        exit(84)

    period = int(arg[1])
    values = collections.deque(maxlen=period)
    # ema = collections.deque(maxlen=period+1)
   # dema = collections.deque(maxlen=period)
   # lastD = 0
    tema = collections.deque(maxlen=period)
    g = 0
    oldR = 0
    switch_count = 0

    while True:
        s = sys.stdin.readline()
        try:
           # old = len(values) == values.maxlen and values[0] or None
           # old = len(dema) == dema.maxlen and dema[0] or None
            old = len(tema) == tema.maxlen and tema[0] or None
            values += [float(s)]
            #lastD = len(dema) == dema.maxlen and dema[0] or values[0]
            # ema += [expoMovingAverage(values, len(ema) == ema.maxlen and ema[0] or values[0], period)]
           # if len(dema) == dema.maxlen:
           #     dema += [doubleExpoMovingAverage(values, dema[0], period)]
           # else:
           #     dema += [doubleExpoMovingAverage(values, values[0], period)]
            if len(tema) == tema.maxlen:
                tema += [tripleExpoMovingAverage(values, tema[0], period)]
            else:
                tema += [tripleExpoMovingAverage(values, values[0], period)]
            #dg = average(values, values.maxlen) - g
            #dg = average(dema, dema.maxlen) - g
            dg = average(tema, tema.maxlen) - g
            if dg < 0:
                dg = 0
           # r = old and (float(s) - old) / old * 100 or math.nan
           # r = old and (dema[-1] - old) / old * 100 or math.nan
            r = old and (tema[-1] - old) / old * 100 or math.nan
           # dev = deviation(values, values.maxlen)
           # dev = deviation(dema, dema.maxlen)
            dev = deviation(tema, tema.maxlen)
            print(f"""g={dg:.2f}        r={r:.0f}%        s={dev:.2f}{r * oldR < 0 and "      a switch occurs" or ""}""")
            if r * oldR < 0:
                switch_count += 1
           # g = average(values, values.maxlen)
           # g = average(dema, dema.maxlen)
            g = average(tema, tema.maxlen)
            oldR = r
        except ValueError:
            if s.replace("\n", "") == "STOP":
                break
            else:
                exit(84)
                # print("Enter only floats or \"STOP\"", file=sys.stderr)
    if len(values) != values.maxlen:
        exit(84)
    print("Global tendency switched", switch_count, "times")
    print(f"5 weirdest values are {[]}")
    # plt.plot(range(len(values)), values, label="values")
    # plt.plot(range(len(ema)), ema, label="ema")
    # plt.plot(range(len(dema)), dema, label="dema")
    # plt.plot(range(len(tema)), tema, label="tema")
    # plt.legend()
    # plt.show()
    return


if __name__ == "__main__":
    main(sys.argv)
