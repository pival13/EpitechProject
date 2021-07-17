#! /usr/bin/env python3

import math
from base64 import b64encode, b64decode

from networkUtil import getSession, getBlockSize, URL
from breakAppendedStringAES_ECB import getPrefixLength

def insertWithAES_CBC(toInsert: bytes, prefixLength: int, url: str, blockSize: int=None):
    if not blockSize: blockSize = getBlockSize(url)
    extraLen = len(toInsert)
    extraLenRounded = math.ceil(extraLen / blockSize) * blockSize
    blockSize = extraLenRounded * 2 + (blockSize - (prefixLength % blockSize))

    data = b'Z' * (blockSize)
    result = list(b64decode(getSession().post(url=url, data=b64encode(data)).content))

    for i in range(extraLen):
        result[prefixLength + blockSize - extraLenRounded - extraLen + i] ^= ord(b'Z') ^ toInsert[i]
    return bytes(result)


from sys import stderr, exc_info

if __name__ == '__main__':
    try:
        blockSize = getBlockSize(URL + 'challenge13/encrypt')
        prefixLength = getPrefixLength(URL + 'challenge13/encrypt', blockSize)
        data = insertWithAES_CBC(b';admin=true;', prefixLength, URL+'challenge13/encrypt', blockSize)
        print(getSession().post(url=URL+'challenge13/decrypt', data=b64encode(data)).content.decode())
    except:
        print(str(exc_info()[1]).capitalize(), file=stderr)
        exit(84)