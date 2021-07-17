#! /usr/bin/env python3

def xor(s: bytes, key: bytes) -> bytes:
    result = [s[i] ^ key[i % len(key)] for i in range(len(s))]
    return bytes(result)

from sys import argv, stderr, exc_info

if __name__ == '__main__':
    if len(argv) != 2:
        print(f"Expected 1 argument, but got {len(argv)-1}", file=stderr)
        exit(84)
    try:
        with open(argv[1]) as f:
            content = f.read().split('\n')
            if len(content) == 3 and len(content[2]) == 0: content = content[:2]
            if len(content) != 2:
                print("Invalid file: expected exactly 2 lines", file=stderr)
                exit(84)
            if len(content[0]) != len(content[1]): raise ValueError('Cannot XOR two elements of different size')
            print(xor(bytes.fromhex(content[0]), bytes.fromhex(content[1])).hex().upper())
    except:
        print(str(exc_info()[1]).capitalize(), file=stderr)
        exit(84)