#!/usr/bin/python3

from sys import argv
import re

if __name__ == "__main__":
    if len(argv) != 2:
        exit(1)
    with open(argv[1]) as file:
        content = file.read()
    if not content:
        exit(1)
    
    btcEth = []
    dtEth = []
    dtBtc = []
    for line in content.split('\n'):
        line = re.sub(r"\"(\d+),(\d+)\"", r"\1.\2", line)
        if line[:line.find(',')] == 'USDT_BTC':
            dtBtc += [line]
        elif line[:line.find(',')] == 'USDT_ETH':
            dtEth += [line]
        elif line[:line.find(',')] == 'BTC_ETH':
            btcEth += [line]
    
    if len(btcEth) != len(dtEth) and len(btcEth) != len(dtBtc):
        exit(1)
    
    for i in range(len(btcEth)):
        print(f"{btcEth[i]};{dtEth[i]};{dtBtc[i]}")