#! /usr/bin/env python3

def basics1():
    page = list(open('data/index.html','r').read())
    repl = {
        'a': 'x', 'b': 'w', 'c': 'v', 'd': 'a', 'e': 'c',
        'f': 'f', 'g': 'z', 'h': 'm', 'i': 'l', 'j': 'd',
        'k': 'k', 'l': 'g', 'm': 'h', 'n': 'j', 'o': 'q',
        'p': 'b', 'q': 'r', 'r': 'e', 's': 'i', 't': 's',
        'u': 'n', 'v': 't', 'w': 'u', 'x': 'o', 'y': 'y',
        'z': 'p'
    }
    for i,c in enumerate(page):
        if c.lower() in repl:
            if c.lower() != c:
                page[i] = repl[c.lower()].upper()
            else:
                page[i] = repl[c.lower()]
    open('subject.md','w').write(''.join(page))

basics1()