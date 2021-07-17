#! /usr/bin/env python3

def simpleMovingAverage(data, period):
    v = 0
    for i in range(0,-min(period, len(data)), -1):
        v += data[i-1]
    return v / min(period, len(data))

def standardDeviation(data, period):
    sma = simpleMovingAverage(data, period)
    v = 0
    for i in range(-min(period, len(data)), 0):
        v += pow(data[i] - sma, 2)
    return pow(v / min(period, len(data)), 0.5)

def expoMovingAverage(data, period, weightPercent=0.865):
    multi = 1 - pow(1-weightPercent, 1/period)
    v = simpleMovingAverage(data, period)
    for i in range(-min(period, len(data)), 0):
        v = data[i] * multi + v * (1-multi)
    return v

def doubleExpoMovingAverage(data, period, weightPercent=0.865):
    ema = [expoMovingAverage(data[:i] if i != 0 else data, period, weightPercent) for i in range(-min(period, len(data))+1, 1)]
    return 2 * ema[-1] - expoMovingAverage(ema, period, weightPercent)

def tripleExpoMovingAverage(data, period, weightPercent=0.865):
    ema = [expoMovingAverage(data[:i] if i != 0 else data, period, weightPercent) for i in range(-min(period, len(data))+1, 1)]
    dema = [expoMovingAverage(ema[:i] if i != 0 else ema, period, weightPercent) for i in range(-min(period, len(ema))+1, 1)]
    return 3 * ema[-1] - 3 * dema[-1] + expoMovingAverage(dema, period, weightPercent)

def movingAverageConvDiv(data, lowPeriod, highPeriod, signalPeriod):
    """Return a dict with keys ["MACD", "Signal", "Histogram"]"""
    macd = [expoMovingAverage(data[:i], lowPeriod) - expoMovingAverage(data[:i], highPeriod) for i in range(-min(signalPeriod, len(data))+1, 0)]
    macd += [expoMovingAverage(data, lowPeriod) - expoMovingAverage(data, highPeriod)]
    signal = expoMovingAverage(macd, signalPeriod)

    return {
        "MACD": macd[-1],
        "Signal": signal,
        "Histogram": macd[-1] - signal
    }

def relativeStrengthIndex(data, period):
    up, down = 0, 0
    for i in range(-min(period, len(data)-1), 0):
        up += data[i] - data[i-1] if data[i] > data[i-1] else 0
        down += data[i-1] - data[i] if data[i] < data[i-1] else 0
    return 100 * up / (up + down) if up != down else 50

def stochasticOscillator(datas, period, period2=3):
    """'datas' may be either: a list on the form [open, close, high, low]
                              a dict with keys 'open', 'close', 'high' and 'low'
    """
    if not isinstance(datas, dict):
        datas = {'open': datas[0], 'close': datas[1], 'high': datas[2], 'low': datas[3]}
    
    k = [100 * (datas['close'][i-1] - min(datas['low'][i-period:i])) / (max(datas['high'][i-period:i]) - min(datas['low'][i-period:i])) for i in range(1-min(period2, len(datas['low'])), 0)]
    k += [100 * (datas['close'][-1] - min(datas['low'][-period:])) / (max(datas['high'][-period:]) - min(datas['low'][-period:]))]
    return simpleMovingAverage(k, period2)

def bollingerBands(data, period, delta=2):
    """Return a dict with keys 'Lower', 'Upper', 'Middle', 'PercentB' and 'Bandwidth'"""
    sma = simpleMovingAverage(data, period)
    dev = standardDeviation(data, period)

    return {
        'Lower': sma - delta * dev,
        'MidLower': sma - delta/2 * dev,
        'Middle': sma,
        'MidUpper': sma + delta/2 * dev,
        'Upper': sma + delta * dev,
        'PercentB': 100 * (data[-1] - sma + delta * dev) / (2 * delta * dev) if dev != 0 else 0,
        'Bandwidth': 100 * (2 * delta * dev) / sma if sma != 0 else 0
    }
    #return {
    #    'Lower': sma - delta * dev,
    #    'Upper': sma + delta * dev,
    #    'Middle': sma,
    #    'PercentB': 100 * (data[-1] - sma + delta * dev) / (2 * delta * dev) if dev != 0 else 0,
    #    'Bandwidth': 100 * (2 * delta * dev) / sma if sma != 0 else 0
    #}

#def fibonacciRetracement(data, dataHigh, dataLow)

def ichimokuCloud(datas, p1, p2, p3):
    """'datas' may be either: a list on the form [open, close, high, low]
                              a dict with keys 'open', 'close', 'high' and 'low'
                              
        Return a dict with keys 'Tenkan', 'Kijun', 'Senkou span A', 'Senkou span B'"""
    if not isinstance(datas, dict):
        datas = {'open': datas[0], 'close': datas[1], 'high': datas[2], 'low': datas[3]}
    
    pastTenkan = (max(datas['high'][-min(p1+p2, len(datas['high'])):]) + min(datas['low'][-min(p1+p2, len(datas['low'])):])) / 2
    pastKijun = (max(datas['high'][-min(p2+p2, len(datas['high'])):]) + min(datas['low'][-min(p2+p2, len(datas['low'])):])) / 2
    
    Tenkan = (max(datas['high'][-min(p1, len(datas['high'])):]) + min(datas['low'][-min(p1, len(datas['low'])):])) / 2
    Kijun = (max(datas['high'][-min(p2, len(datas['high'])):]) + min(datas['low'][-min(p2, len(datas['low'])):])) / 2
    SenkouA = (pastKijun + pastTenkan) / 2
    SenkouB = (max(datas['high'][-min(p3+p2, len(datas['high'])):]) + min(datas['low'][-min(p3+p2, len(datas['low'])):])) / 2

    return { 'Tenkan': Tenkan, 'Kijun': Kijun, 'Senkou span A': SenkouA, 'Senkou span B': SenkouB }

def directionalMovementIndicator(datas, period, period2=100):
    """'datas' may be either: a list on the form [open, close, high, low]
                            a dict with keys 'open', 'close', 'high' and 'low'
                              
        Return a dict with keys 'ADX', 'DI+', 'DI-', 'DXI'"""
    if not isinstance(datas, dict):
        datas = {'open': datas[0], 'close': datas[1], 'high': datas[2], 'low': datas[3]}
    
    if len(datas['high']) < 2:
        return {'ADX': 0, 'DI+': 0, 'DI-': 0, 'DXI': 0}
    
    dmP = [max(datas['high'][n+1]-datas['high'][n], 0) for n in range(len(datas['high'])-1)]
    dmM = [max(datas['low'][n]-datas['low'][n+1], 0) for n in range(len(datas['low'])-1)]
    tr = [max(datas['high'][n+1], datas['close'][n]) - min(datas['low'][n+1], datas['close'][n]) for n in range(len(datas['high'])-1)]

    dxI = []
    for i in range(-min(period2, len(tr))+1, 1):
        trA = expoMovingAverage(tr[:i] if i != 0 else tr, period)
        diP = 100 * expoMovingAverage(dmP[:i] if i != 0 else dmP, period) / trA
        diM = 100 * expoMovingAverage(dmM[:i] if i != 0 else dmM, period) / trA

        dxI += [100 * abs(diP - diM) / (diP + diM)]
    
    return {'ADX': expoMovingAverage(dxI, period2), 'DI+': diP, 'DI-': diM, 'DXI': dxI[-1]}

def fractale(datas, period, middle=0.5):
    """'datas' may be either: a list on the form [open, close, high, low]
                            a dict with keys 'open', 'close', 'high' and 'low'
                            
        Return 1 if `middle`x`period` days ago was a climax
               -1 if it was a anticlimax
               0 otherwise"""
    if not isinstance(datas, dict):
        datas = {'open': datas[0], 'close': datas[1], 'high': datas[2], 'low': datas[3]}
    
    if (len(datas['high']) < period):
        return 0

    midHigh = datas['high'][-int((period+1)*middle)]
    midLow = datas['low'][-int((period+1)*middle)]

    return 1 if max(datas['high'][-period:]) == midHigh else \
           -1 if min(datas['low'][-period:]) == midLow else \
           0