#! /usr/bin/env python3

from xor import xor

from sys import argv, stderr, exc_info

if __name__ == '__main__':
    if len(argv) != 2:
        print(f"Expected 1 argument, but got {len(argv)-1}", file=stderr)
        exit(84)
    try:
        with open(argv[1]) as f:
            content = f.read().split('\n')
            if len(content) == 3 and len(content[2]) == 0: content = content[:2]
            if len(content) != 2 or len(content[0]) == 0 or len(content[1]) == 0:
                print("Invalid file: expected exactly 2 lines", file=stderr)
                exit(84)
            print(xor(bytes.fromhex(content[1]), bytes.fromhex(content[0])).hex().upper())
    except:
        print(str(exc_info()[1]).capitalize(), file=stderr)
        exit(84)