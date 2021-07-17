#! /usr/bin/env python3

import math
from base64 import b64encode, b64decode

from networkUtil import getSession, getBlockSize, URL

def getPrefixLength(url: str, blockSize: int=None):
    if not blockSize: blockSize = getBlockSize(url)
    prev = b64decode(getSession().post(url=url, data=b64encode(b'a')).content)
    prev2 = b64decode(getSession().post(url=url, data=b64encode(b'b')).content)
    blockI = 0
    for i in range(int(len(prev) / blockSize)):
        if prev[i*blockSize:(i+1)*blockSize] != prev2[i*blockSize:(i+1)*blockSize]:
            blockI = i
            break
    for i in range(2, blockSize+1):
        cur = b64decode(getSession().post(url=url, data=b64encode(b'a'*i)).content)
        if cur[blockI*blockSize:(blockI+1)*blockSize] == prev[blockI*blockSize:(blockI+1)*blockSize]:
            return blockSize * blockI + blockSize - i + 1
        prev = cur
    return blockSize * blockI

def getNthByte(n: int, blockSize: int, alreadyDecrypt: bytes, url: str) -> bytes:
    sess = getSession()
    
    blockNb = math.ceil((n+1) / blockSize)
    block = b'A' * (blockSize * blockNb - (n+1))
    
    expected = b64decode(sess.post(url=url, data=b64encode(block)).content)

    block += alreadyDecrypt
    for v in range(0x00, 0xFF+1):
        result = b64decode(sess.post(url=url, data=b64encode(block + bytes([v]))).content)
        if expected[(blockNb-1)*blockSize:blockNb*blockSize] == result[(blockNb-1)*blockSize:blockNb*blockSize]:
            return bytes([v])

def getAppendedString(url: str) -> bytes:
    blockSize = getBlockSize(url)
    prefixLength = getPrefixLength(url, blockSize)
    decoded = b''
    i = 0
    while True:
        b = getNthByte(i+prefixLength, blockSize, decoded, url)
        if b == b'\x01':
            if getNthByte(i+1+prefixLength, blockSize, decoded+b'\x02', url) == b'\x02':
                return decoded
        decoded += b
        i += 1

from sys import argv, stderr, exc_info
if __name__ == '__main__':
    try:
        print(b64encode(getAppendedString(URL + "challenge10")).decode())
    except:
        print(str(exc_info()[1]).capitalize(), file=stderr)
        exit(84)
    
        
