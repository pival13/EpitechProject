#! /usr/bin/env python3


import sys
import re

def check_file(file):
    try:
        open(file, "r")
        return True
    except IOError:
        return False

def check_args():
    lines = []
    if len(sys.argv) != 2 or check_file(sys.argv[1]) != True:
        print("Error: Please enter valid file")
        exit(84)
    file = open(sys.argv[1], "r")
    content = file.readlines()
    lines = content
    file.close()
    return lines

def detectxor(arrayofbyte):
    character_frequencies = {
        'a': .08167, 'b': .01492, 'c': .02782, 'd': .04253,
        'e': .12702, 'f': .02228, 'g': .02015, 'h': .06094,
        'i': .06094, 'j': .00153, 'k': .00772, 'l': .04025,
        'm': .02406, 'n': .06749, 'o': .07507, 'p': .01929,
        'q': .00095, 'r': .05987, 's': .06327, 't':  .09056,
        'u': .02758, 'v': .00978, 'w': .02360, 'x': .00150,
        'y': .01974, 'z': .00074, ' ': .13000
    }
    line, keyvalue = max(((line, key) for line in range(len(arrayofbyte)) for key in range(256)),
        key = lambda byte:
        sum(character_frequencies[count] for count in map(lambda count:
            chr(count ^ byte[1]), arrayofbyte[byte[0]]) if count in character_frequencies))
    keyvalue = bytes([keyvalue]).hex()
    line = str(line + 1)
    string = (line + " " + keyvalue)
    print(string.upper())

from sys import argv, stderr, exc_info

if __name__ == '__main__':
    if len(argv) != 2:
        print(f"Expected 1 argument, but got {len(argv)-1}", file=stderr)
        exit(84)
    try:
        lines = check_args()
        input = [bytes.fromhex(re.sub(r'\s', "", num)) for num in lines]
        detectxor(input)
    except:
        print(str(exc_info()[1]).capitalize(), file=stderr)
        exit(84)