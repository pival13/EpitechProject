#! /usr/bin/env python3

import matplotlib.pyplot as plt
from matplotlib import cm
from matplotlib.ticker import LinearLocator
import numpy as np

import lupa
import re

lua = lupa.LuaRuntime()

def drawData(tbl, step):
    sizeX = max(len(r) for r in tbl)
    sizeY = len(tbl)
    X = np.arange(0, sizeX-1+step, step)
    Y = np.arange(0, sizeY-1+step, step)
    Z = []
    for y in Y:
        tmp = []
        for x in X:
            tmp += [lua.eval(f'bezierPlane(tbl, {x}, {y})')]
        Z += [np.asarray(tmp)]
    Z = np.asanyarray(Z)
    X, Y = np.meshgrid(X, Y)
    
    X2 = np.arange(0, sizeX)
    Y2 = np.arange(0, sizeY)
    Z2 = np.asanyarray([np.asarray([tbl[y][x] if x < len(tbl[y]) else 0 for x in range(sizeX)]) for y in range(sizeY)])
    X2, Y2 = np.meshgrid(X2, Y2)

    """lua.execute(f'''
        for y = #tbl-1, 0, -{step} do
            for x = 0, #tbl[1]-1, {step} do
                io.write(("%0.2f\t"):format(bezierPlane(tbl, x, y)))
            end
            print()
        end
    ''')"""

    fig, ax = plt.subplots(subplot_kw={"projection": "3d"})
    ax.set_zlim(0, 100)
    ax.zaxis.set_major_formatter('{x:.02f}')
    #Calculated surface 
    surf = ax.plot_surface(X, Y, Z, cmap=cm.coolwarm, linewidth=0, antialiased=False)
    fig.colorbar(surf)
    #Initial points
    ax.scatter(X2, Y2, Z2, c='C2')
    ax.plot_wireframe(X2, Y2, Z2, linewidth=1, colors='C2')

    plt.show()


from sys import argv

if __name__ == '__main__':
    if len(argv) < 2: exit("Expected one argument")
    
    tbl = []
    with open(argv[1]) as f:
        for l in f.readlines():
            m = re.match(r'^(\d+);(\d+);(\d+(?:\.\d+)?)$', l)
            if not m:
                exit(f"Invalid format for file '{argv[1]}'")
            while int(m[2]) >= len(tbl): tbl += [[]]
            while int(m[1]) >= len(tbl[int(m[2])]): tbl[int(m[2])] += [0]
            tbl[int(m[2])][int(m[1])] = float(m[3])
    
    lua.execute('tbl = {}')
    maxX = max(len(r) for r in tbl)
    for i, row in enumerate(tbl):
        lua.execute(f'tbl[{i+1}] = {{}}')
        for j in range(maxX):
            lua.execute(f'tbl[{i+1}][{j+1}] = {tbl[i][j] if j < len(tbl[i]) else 0}')
    
    """lua.execute('''
    for y = #tbl, 1, -1 do
        for x = 1, #tbl[y] do
            io.write(("%0.2f\t"):format(tbl[y][x]))--, bezierPlane(tbl, x, y)))
        end
        print()
    end
    ''')"""

    with open('309pollution.lua') as f:
        f.readline()
        lua.execute('arg = {}')
        lua.execute(f.read())

    drawData(tbl, float(argv[2]) if len(argv) >= 3 and re.match(r'^\d+(\.\d+)?$', argv[2]) else 0.2)