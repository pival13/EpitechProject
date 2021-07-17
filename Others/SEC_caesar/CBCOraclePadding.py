#! /usr/bin/env python3

import math
from base64 import b64encode, b64decode

from padder import unpad
from networkUtil import getSession, URL

def decryptOneOraclePadding(toDecrypt: bytes, IV: bytes, nb: int, url: str) -> (bytes, bytes):
    nb += 1
    for i in range(0x00, 0xFF+1):
        iv = IV[:-nb] + bytes([i]) + bytes([b ^ nb for b in IV[-(nb-1):]] if nb != 1 else [])
        res = getSession().post(url=url, data=b64encode(iv)+b'\n'+b64encode(toDecrypt))
        if res.ok:
            #if nb == 0:
            #    iv = IV[:-nb] + bytes([i+1]) + bytes([b ^ nb for b in IV[-(nb-1):]] if nb != 1 else [])
            #    res = getSession().post(url=url, data=b64encode(iv)+b'\n'+b64encode(toDecrypt))
            return bytes([i^nb]), bytes([i^IV[-nb]^nb])

def oraclePadding(encrypt: bytes, IV: bytes, url: str) -> bytes:
    blockSize = len(IV)
    nbBlock = math.ceil(len(encrypt) / blockSize)

    decrypt = b''
    for i in range(nbBlock-1, -1, -1):
        iv = IV if i == 0 else encrypt[(i-1)*blockSize:i*blockSize]
        toDecrypt = encrypt[i*blockSize:(i+1)*blockSize]
        for j in range(blockSize):
            usedXor, l = decryptOneOraclePadding(toDecrypt, iv, j, url)
            iv = iv[:-j-1] + usedXor + (iv[-j:] if j != 0 else bytes([]))
            decrypt = l + decrypt
    return unpad(decrypt)


from sys import stderr, exc_info

if __name__ == '__main__':
    try:
        data = getSession().get(url=URL+"challenge14/encrypt").content
        data = data.split(b'\n')
        IV = b64decode(data[0])
        cypher = b64decode(data[1])
        data = oraclePadding(cypher, IV, url=URL+'challenge14/decrypt')
        print(b64encode(data).decode())
    except:
        print(str(exc_info()[1]).capitalize(), file=stderr)
        exit(84)