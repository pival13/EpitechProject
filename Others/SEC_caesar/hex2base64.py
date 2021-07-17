#! /usr/bin/env python3

import base64

def hex2b64(data: str) -> str:
    data = bytes.fromhex(data)
    data = base64.encodebytes(data).replace(b'\n',b'')
    return data.decode()

from sys import argv, exc_info, stderr

if __name__ == '__main__':
    if len(argv) != 2:
        print(f"Expected 1 argument, but got {len(argv)-1}", file=stderr)
        exit(84)
    try:
        with open(argv[1]) as f:
            content = f.read()
            if len(content) == 0: raise ValueError(f'File {argv[1]} is empty')
            print(hex2b64(content))
    except:
        print(str(exc_info()[1]).capitalize(), file=stderr)
        exit(84)