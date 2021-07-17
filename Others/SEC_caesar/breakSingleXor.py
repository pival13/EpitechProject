#! /usr/bin/env python3

def breakSingleXor(s: bytes) -> bytes:
    isValidChara = lambda c: chr(c) in " \t\n" or (c >= ord(' ') and c <= ord('~'))
    isCommonChara = lambda c: chr(c) in " ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
    
    valids = {}
    for i in range(0x00, 0xFF+1):
        xored = bytes([c ^ i for c in s])
        if all([isValidChara(c) for c in xored]) and len([True for c in xored if isCommonChara(c)]) >= 0.8*len(s):
            valids[i] = len([True for c in xored if isCommonChara(c)])
    if len(valids) == 0: return
    l = list(valids.keys())
    l.sort(key=lambda k: valids[k], reverse=True)
    #print([len([True for c in bytes([c ^ key for c in s]) if isCommonChara(c)]) / len(s) for key in l[:5]])
    #print(bytes([c ^ l[0] for c in s])
    return bytes([l[0]])
        
    #    if all([isValidChara(c) for c in xored]) and len([True for c in xored if chr(c) in "etaoiETAOI"]) >= len(xored) * 0.40:#44.8%
    #        return bytes([i])


from sys import argv, stderr, exc_info

if __name__ == '__main__':
    if len(argv) != 2:
        print(f"Expected 1 argument, but got {len(argv)-1}", file=stderr)
        exit(84)
    try:
        with open(argv[1]) as f:
            content = f.read()
            if len(content) == 0: raise ValueError(f'File {argv[1]} is empty')
            print(breakSingleXor(bytes.fromhex(content)).hex().upper())
    except:
        print(str(exc_info()[1]).capitalize(), file=stderr)
        exit(84)