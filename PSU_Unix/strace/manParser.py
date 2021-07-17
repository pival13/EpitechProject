#!/usr/bin/python3

import sys
import os
import time
import re

def main():
    with open("file.txt") as file:
        lines = file.readlines()
        for line in lines:
            line = line.replace('\n', '')
            with os.popen("man 2 " + line) as man:
                manLines = man.read(1000)
                mobj = re.search("(\\w+ \*?\*?)"+line+"\(([^\)]*)\);", manLines)
                if mobj:
                    print(line, mobj.groups()[0].strip(), line+",", mobj.groups()[1].replace("\n","").strip())
                else:
                    print(line)

if __name__ == '__main__':
    main()