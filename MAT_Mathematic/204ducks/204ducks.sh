#!/bin/bash

displayTime() {
    nb=$(echo "$1 + 0.5" | bc)
    echo -n "$(echo "$nb / 60" | bc)m "
    if [ $(echo "$nb % 60 / 1" | bc) -lt 10 ]; then
        echo -n "0"
    fi
    echo "$(echo "$nb % 60 /1" | bc)s"
}

displayPercent() {
    nb=$(echo "$1+0.0005" | bc)
    echo "$(echo "$nb * 100 / 1" | bc).$(echo "$nb * 1000 % 10 / 1" | bc)%"
}

if [ $# -eq 1 ] && ([[ "$1" =~ ^[01](\.[0-9]+)?$ ]] || [[ "$1" =~ ^2(\.([0-4][0-9]*|50*))?$ ]]); then
    echo -n "Average return time: "
    displayTime $(echo "`./funct esperance $1` * 60" | bc)
    echo "Standard deviation:" `./funct deviation $1`
    echo -n "Time after which 50% of the ducks are back: "
    displayTime `./funct percent $1 50`
    echo -n "Time after which 99% of the ducks are back: "
    displayTime `./funct percent $1 99`
    echo -n "Percentage of ducks back after 1 minute: "
    displayPercent `./funct integral $1 0 1`
    echo -n "Percentage of ducks back after 2 minutes: "
    displayPercent `./funct integral $1 0 2`
else
    echo "Expected a single number between 0 and 2.5"
    exit 84
fi
