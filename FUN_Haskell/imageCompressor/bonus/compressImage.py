#!/usr/bin/env python3

from PIL import Image
from sys import argv
from os import system
import numpy as np
import re

def recompos(path):
    with open(path) as f:
        arr = []
        i = -1
        x = 0
        y = 0
        while True:
            line = f.readline().replace("\n","")
            if len(line) == 0:
                break
            if line == "--":
                i += 1
                arr.insert(i, {})
                arr[i]['point'] = []
            elif re.compile(r"\(\d+,\d+,\d+\)").match(line):
                obj = re.compile(r"\((\d+),(\d+),(\d+)\)").match(line)
                arr[i]['color'] = [int(obj[1]), int(obj[2]), int(obj[3])]
            elif re.compile(r"\(\d+,\d+\) \(\d+,\d+,\d+\)").match(line):
                obj = re.compile(r"\((\d+),(\d+)\)").search(line)
                arr[i]['point'].insert(len(arr[i]['point']), [int(obj[1]), int(obj[2])])
                if int(obj[1])+1 > x:
                    x = int(obj[1])+1
                if int(obj[2])+1 > y:
                    y = int(obj[2])+1
                continue
        image = np.zeros((y, x, 3), dtype=np.uint8)
        for c in arr:
            for pt in c['point']:
                image[pt[1], pt[0]] = (c['color'][0], c['color'][1], c['color'][2])
        img = Image.fromarray(image)
        img.save("result.png")

def decompos(img, name):
    arr = np.array(Image.open(img))
    with open(".dec" + name, "w") as f:
        for y in range(len(arr)):
            for x in range(len(arr[y])):
                f.write(f"({x},{y}) ({arr[y][x][0]},{arr[y][x][1]},{arr[y][x][2]})\n")
    f.close()

if __name__ == "__main__":
    if len(argv) < 2:
        exit(0)
    s = argv[1].rsplit("/", 1)[-1]
    n = len(argv) >= 3 and int(argv[2]) or 5
    d = len(argv) >= 4 and float(argv[3]) or 0.2
    decompos(argv[1], s)
    system(f"time ../imageCompressor {n} {d} '.dec{s}' > '.rec{s}' && rm '.dec{s}'")
    recompos(".rec" + s)
    system(f"mv result.png 'new{s}' && rm '.rec{s}'")