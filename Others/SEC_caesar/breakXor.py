#! /usr/bin/env python3

from breakSingleXor import breakSingleXor
import math

def hammingDistance(s1: bytes, s2: bytes) -> int:
    if len(s1) != len(s2):
        raise ValueError('Hamming distance can only be calculated with two strings of same length.')
    dist = 0
    for c1, c2 in zip(s1, s2):
        b = bin(c1 ^ c2)
        dist += b.count('1')
    return dist

def estimatedKeySize(s: bytes) -> int:
    sizes = {}
    for i in range(1, 64):
        dists = []
        for maxBlock in range(1, min(math.floor(len(s) / i), 16)):
            for minBlock in range(maxBlock):
                dists += [hammingDistance(s[i*minBlock:i*(minBlock+1)], s[i*maxBlock:i*(maxBlock+1)])]
        if len(dists) == 0: continue
        sizes[i] = (sum(dists) / len(dists)) / i
    l = list(sizes.keys())
    l.sort(key=lambda i: sizes[i])
    return l[0]

def breakXor(s: bytes) -> bytes:
    keySize = estimatedKeySize(s)
    blocks = [[s[i] for i in range(len(s)) if i % keySize == iBlock] for iBlock in range(keySize)]
    keys = b''
    for i in range(keySize):
        keys += breakSingleXor(blocks[i]) or bytes([0])
    return keys

from sys import argv, stderr, exc_info

if __name__ == '__main__':
    if len(argv) != 2:
        print(f"Expected 1 argument, but got {len(argv)-1}", file=stderr)
        exit(84)
    try:
        with open(argv[1]) as f:
            content = f.read()
            print(breakXor(bytes.fromhex(content)).hex().upper())
    except:
        print(str(exc_info()[1]).capitalize(), file=stderr)
        exit(84)