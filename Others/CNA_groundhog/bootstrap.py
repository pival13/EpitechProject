#!/bin/python3

import sys
import matplotlib.pyplot as plt
import math
import collections

POURCENTAGE_EXPO = 0.90

def average(values, period):
    if len(values) < period:
        return math.nan
    average = 0
    for v in range(len(values)-period, len(values)):
        average += values[v]
    return average / period

def variance(values, period):
    if len(values) < period:
        return math.nan
    ave = average(values, period)

    var = 0
    for v in range(len(values)-period, len(values)):
        var += math.pow(values[v]-ave, 2)
    return math.sqrt(var / period)

def simpleMobileAverage(values, maxI, period):
    v = 0
    maxI = min(len(values), maxI)
    period = min(maxI, period)
    for i in range(period):
        v += values[maxI-period+i]
    return v / period

def expoMobileAverage(values, lastValue, maxI, period, nb=None):
    if nb == None:
        nb = period
    elif nb == 0:
        return lastValue
    a = 1 - pow(1-POURCENTAGE_EXPO, 1/period)
    maxI = min(len(values), maxI)
    return maxI == 1 and values[0] or a*values[maxI-1]+(1-a)*expoMobileAverage(values, lastValue, maxI-1, period, nb-1)

def doubleExpoMobileAverage(values, lastValue, maxI, period):
    l = []
    for i in range(min(len(values), maxI)):
        l += [expoMobileAverage(values, i >= period and l[i-period] or 0, i+1, period)]
    return 2 * l[-1] - expoMobileAverage(l, lastValue, maxI, period)

def tripleExpoMobileAverage(values, lastValue, maxI, period):
    l = []
    for i in range(min(len(values), maxI)):
        l += [expoMobileAverage(values, i >= period and l[i-period] or 0, i+1, period)]
    l2 = []
    for i in range(min(len(values), maxI)):
        l2 += [expoMobileAverage(l, i >= period and l2[i-period] or 0, i+1, period)]
    return 3 * l[-1] - 3 * l2[-1] + expoMobileAverage(l2, lastValue, maxI, period)

def weightMobileAverage(values, maxI, period):
    v = 0
    maxI = min(len(values), maxI)
    period = min(maxI, period)
    for i in range(period):
        v += (i+1) * values[maxI-period+i]
    return v / period / (period+1) * 2

def main():
    if len(sys.argv) == 1:
        return
    
    period = 7
    values = []
    sma = collections.deque(maxlen=period+1)
    wma = collections.deque(maxlen=period+1)
    ema = collections.deque(maxlen=period+1)
    dema = collections.deque(maxlen=period+1)
    tema = collections.deque(maxlen=period+1)
    var = []
    aveGrow = []
    relaEvo = []
    with open(sys.argv[1]) as f:
        while True:
            line = f.readline()
            if not line:
                break
            line = line.replace("\n", "")
            values += [float(line)]

    for i in range(len(values)):
        sma += [simpleMobileAverage(values, i+1, period)]
        wma += [weightMobileAverage(values, i+1, period)]
        ema += [expoMobileAverage(values, i >= period and ema[0] or 0, i+1, period)]
        dema += [doubleExpoMobileAverage(values, i >= period and dema[0] or 0, i+1, period)]
        tema += [tripleExpoMobileAverage(values, i >= period and tema[0] or 0, i+1, period)]
        var += [variance(sma, period)*5]
        aveGrow += [sma[-1] - average(sma, period)]
        relaEvo += i < period and [math.nan] or [(sma[-1] - sma[0]) / sma[0] * 100]
        print(values[i])
        print(f"g={aveGrow[i]:.2f}        r={relaEvo[i]:.0f}%        s={var[i]:.2f}")

    #plt.plot(range(len(values)), values, label="values")
    #plt.plot(range(len(sma)), sma, label="simple average")
    #plt.plot(range(len(values)-period-1, len(values)), wma, label="weighted average")
    plt.plot(range(len(values)-period-1, len(values)), ema, label="exponent average")
    plt.plot(range(len(values)-period-1, len(values)), dema, label="double exponent average")
    plt.plot(range(len(values)-period-1, len(values)), tema, label="triple exponent average")
    #plt.plot(range(len(sma)), var, label="deviance (*5)")
    #plt.plot(range(len(sma)), aveGrow, label="average increase (°C)")
    #plt.plot(range(len(sma)), relaEvo, label="relative increase (%)")
    plt.legend()
    plt.show()

if __name__ == "__main__":
    main()