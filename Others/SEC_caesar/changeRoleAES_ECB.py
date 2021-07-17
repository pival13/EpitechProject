#! /usr/bin/env python3

import math
from base64 import b64decode, b64encode

from networkUtil import URL, getSession, getBlockSize

from sys import exc_info, stderr

if __name__ == '__main__':
    try:
        blockSize = getBlockSize(URL+'challenge11/new_profile')
        
        strSize = blockSize - 23 + len(r'user') - len(b'@caesar.com')
        while strSize < 0: strSize += blockSize
        s = b'a' * strSize + b'@caesar.com'
        
        strSize2 = blockSize - 6 + len(b'admin')
        while strSize2 < 0: strSize2 += blockSize
        s2 = b'a' * (strSize2 - len(b'admin')) + b'admin' + bytes([blockSize-5]) * (blockSize-5)

        part1 = b64decode(getSession().post(url=URL+'challenge11/new_profile', data=b64encode(s)).content)[:strSize+30]
        part2 = b64decode(getSession().post(url=URL+'challenge11/new_profile', data=b64encode(s2)).content)[strSize2+1:strSize2+1+blockSize]
        print(getSession().post(url=URL+'challenge11/validate', data=b64encode(part1+part2)).content.decode())
    except:
        print(str(exc_info()[1]).capitalize(), file=stderr)
        exit(84)
