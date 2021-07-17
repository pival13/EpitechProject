#!/usr/bin/env python3

import main

def rsi_indicator(rsi25: float, last_rsi25: float) -> float:
    if last_rsi25 > 70 and rsi25 < last_rsi25:
        return(-5.0)
    if rsi25 > 70 and rsi25 > last_rsi25:
        return(-20.0)
    if last_rsi25 < 30 and rsi25 > last_rsi25:
        return(5.0)
    if rsi25 < 30 and rsi25 < last_rsi25:
        return (20.0)
    return (0.0)

def doublebb_indicator(value: float, bb20: dict) -> float:
    if bb20[-1]['Lower'] < value < bb20[-1]['MidLower']:
        return (60.0)
    if bb20[-1]['Upper'] > value > bb20[-1]['MidUpper']:
        return (-60.0)
    return (0.0)

def buy_sell_order(value: float, rsi25:float, last_rsi25: float, bb20: dict, currency: str) -> dict:
    indicator: float = rsi_indicator(rsi25, last_rsi25) * 4 + doublebb_indicator(value, bb20) * 5
    indicator /= 9
    selling: bool = False
    if (indicator < 0):
        selling = True
        indicator *= -1
    if indicator == 0:
        return {
            'type': 0,
            'currency': None,
            'indicator': 0
        }
    return {
        'type': 2 if selling is True else 1,
        'currency': currency,
        'indicator': indicator / 100
    }


import indicator
from sys import stderr

def determine_action_to_do(values, rsi10, rsi20, rsi50, bb, macd):
    kind = -1 if bb[-1]['PercentB'] < 50 else 1
    maxBBW = max([v['Bandwidth'] for v in bb])
    minBBW = min([v['Bandwidth'] for v in bb])
    percentBBW = (bb[-1]['Bandwidth'] - minBBW) / (maxBBW - minBBW) * 100 if maxBBW != minBBW else 0
    percentBBP = abs(bb[-1]['PercentB']-50) / 50 * 100
    percentRSI = (indicator.doubleExpoMovingAverage(list(rsi50), 20) - 50) / 5 * 5 + \
                 (indicator.doubleExpoMovingAverage(list(rsi20), 20) - 50) / 15 * 5 + \
                 (indicator.doubleExpoMovingAverage(list(rsi10), 20) - 50) / 25 * 5

    if percentBBW < 25 or percentBBP < 50:
        return 0
    #print(kind, "bbw", percentBBW, "bbp", percentBBP, "rsi", percentRSI, file=stderr, flush=True)
    return (percentBBW * 0.2 + (percentBBP-50) * 0.3) * kind + percentRSI * 0.5

if __name__ == "__main__":
    determine_action_to_do(range(0,50), [10 for _ in range(50)], [10 for _ in range(50)], [10 for _ in range(50)], [indicator.bollingerBands(range(1,50), 20) for _ in range(50)], None)