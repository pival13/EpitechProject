#! /usr/bin/env python3

import math
from base64 import b64encode, b64decode

from networkUtil import getSession, getBlockSize, URL
from breakAppendedStringAES_ECB import getAppendedString

from sys import stderr, exc_info

if __name__ == '__main__':
    try:
        print(b64encode(getAppendedString(URL + "challenge12")).decode())
    except:
        print(str(exc_info()[1]).capitalize(), file=stderr)
        exit(84)