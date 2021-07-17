#!/usr/bin/python3

import sys
import re
import json
from datetime import datetime
from collections import deque
import matplotlib.pyplot as plt

import indicator

def dictToList(datas, key):
    return [v[key] for v in datas]

def main():
    fig, (dataAxe, percentAxe, otherAxe) = plt.subplots(3, 1, sharex=True)
    btc_eth = []
    usdt_eth = []
    usdt_btc = []

    rsi10 = []
    rsi20 = []
    rsi50 = []
    demaRsi10 = []
    demaRsi20 = []
    demaRsi50 = []
    macd = []
    bb20 = []

    while True:
        s = str(sys.stdin.readline())
        if not s:
            break

        values = [kind.split(',') for kind in s.split(';')]
        btc_eth += [{"open": float(values[0][4]), "close": float(values[0][5]), "high": float(values[0][2]), "low": float(values[0][3])}]
        usdt_eth += [{"open": float(values[1][4]), "close": float(values[1][5]), "high": float(values[1][2]), "low": float(values[1][3])}]
        usdt_btc += [{"open": float(values[2][4]), "close": float(values[2][5]), "high": float(values[2][2]), "low": float(values[2][3])}]
        data = [
            [v['open'] for v in usdt_btc],
            [v['close'] for v in usdt_btc],
            [v['high'] for v in usdt_btc],
            [v['low'] for v in usdt_btc]
        ]
       
        rsi10 += [indicator.relativeStrengthIndex(data[1], 10)]
        rsi20 += [indicator.relativeStrengthIndex(data[1], 20)]
        rsi50 += [indicator.relativeStrengthIndex(data[1], 50)]
        demaRsi10 += [indicator.expoMovingAverage(rsi10, 20)]
        demaRsi20 += [indicator.expoMovingAverage(rsi20, 20)]
        demaRsi50 += [indicator.expoMovingAverage(rsi50, 20)]
        macd += [indicator.movingAverageConvDiv(data[1], 12, 26, 9)]
        bb20 += [indicator.bollingerBands(data[1], 20)]




    size = len(usdt_btc)
    sizeM = size-len(rsi10)
    #dataAxe.plot(range(len(btc_eth)), [v['close'] for v in btc_eth], label="Ethereum (Bitcoin)")
    dataAxe.plot(range(size), data[1], label="Bitcoin ($)")
    #dataAxe.plot(range(len(usdt_eth)), [v['close'] for v in usdt_eth], label="Etherum ($)")
    
    # Simple Moving Average
    #dataAxe.plot(range(size), sma20, label="SMA 20")
    #dataAxe.plot(range(size), sma50, label="SMA 50")
    #dataAxe.plot(range(size), sma200, label="SMA 200")
    
    # Expo Moving Average
    #dataAxe.plot(range(size), ema20, label="EMA 20")
    #dataAxe.plot(range(size), ema50, label="EMA 50")
    #dataAxe.plot(range(size), ema200, label="EMA 200")

    # Relative Strength Index
    #percentAxe.plot(range(size), rsi20, label='RSI Close')
    percentAxe.plot(range(sizeM,size), rsi10, label='DEMA RSI 10')
    percentAxe.plot(range(sizeM,size), rsi20, label='DEMA RSI 20')
    percentAxe.plot(range(sizeM,size), rsi50, label='DEMA RSI 50')
    #percentAxe.bar(range(size), [50 if macd[i]['Histogram'] <= 0 and macd[i-1]['Histogram'] > 0 else -50 if macd[i]['Histogram'] >= 0 and macd[i-1]['Histogram'] < 0 else 0 for i in range(len(macd))], bottom=50, width=0.5, label='Other signal crossing')
    #   prix += (demaRsi50 - 50) /5 *5 + (demaRsi20-50) / 10 * 5 + (demaRsi10-50) / 15 * 5 %

    # Stochastic Oscillator
    #percentAxe.plot(range(size), oscillator, label='Stochastic Oscillator')

    # Moving Average Conv/Div
    otherAxe.plot(range(sizeM,size), dictToList(macd, 'MACD'), label="MACD(12,26,9)")
    otherAxe.plot(range(sizeM,size), dictToList(macd, 'Signal'), label='MACD Signal')
    #percentAxe.bar(range(size), [v['Histogram'] for v in macd], color='red', label="MACD Histogram")

    # Bollinger Bands
    dataAxe.plot(range(sizeM,size), [v['Lower'] for v in bb20], label='Lower BB')
    dataAxe.plot(range(sizeM,size), [v['Upper'] for v in bb20], label='Upper BB')
    dataAxe.plot(range(sizeM,size), [v['Middle'] for v in bb20], label='Middle BB (SMA 20)')
    percentAxe.plot(range(sizeM,size), [v['PercentB'] for v in bb20], label='Percent B') # Prix par rapport à la moyenne et à l'écart-type.
    percentAxe.plot(range(sizeM,size), [v['Bandwidth']+50 for v in bb20], label='BB Bandwidth')

    # Ichimoku Cloud
    #dataAxe.plot(range(size), dictToList(ichimoku, 'Tenkan'), label='Tenkan-sen')
    #dataAxe.plot(range(size), dictToList(ichimoku, 'Kijun'), label='Kijun-sen')
    #dataAxe.plot(range(size), dictToList(ichimoku, 'Senkou span A'), label='Senkou span A')
    #dataAxe.plot(range(size), dictToList(ichimoku, 'Senkou span B'), label='Senkou span B')

    # Directional Movement Index
    #percentAxe.plot(range(size), dictToList(dxi, 'ADX'), label="ADX")
    #percentAxe.plot(range(size), dictToList(dxi, 'DXI'), label="DXI")
    #ercentAxe.plot(range(size), dictToList(dxi, 'DI+'), label="DI+")
    #ercentAxe.plot(range(size), dictToList(dxi, 'DI-'), label="DI-")

    # Fractal
    #percentAxe.bar(range(-5, size-5), [v * 50 for v in fract], bottom=50)
    
    percentAxe.plot(range(size), [50]*size)
    otherAxe.plot(range(size), [0]*size)

    dataAxe.legend()
    percentAxe.legend()
    otherAxe.legend()
    plt.show()


if __name__ == "__main__":
    main()

# Fibonacci

#json.dump([{'devise': 'USDT_ETH', 'time': int(datetime.strptime(v['time_open'], '%Y-%m-%dT%H:%M:%S.%fZ').timestamp()), 'high': v['quote']['USD']['high'], 'low': v['quote']['USD']['low'], 'open': v['quote']['USD']['open'], 'close': v['quote']['USD']['close'], 'volume': v['quote']['USD']['volume']} for v in data['data']['quotes']], open(, 'w'), indent=2))
#https://web-api.coinmarketcap.com/v1/cryptocurrency/ohlcv/historical?convert=USD&slug=bitcoin&time_end=1589846400&time_start=1438898400