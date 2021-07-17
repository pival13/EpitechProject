package main

import (
    "fmt"
    "strings"
    "os"
    "strconv"
    "math"
)

func neutrinos(nb int64, dev, aMean, sqMean, hMean, newValue float64) (int64, float64, float64, float64, float64) {
    nbF := float64(nb)
    aMean = (aMean*nbF + newValue) / (nbF+1)
    sqMean = math.Sqrt((nbF*math.Pow(sqMean, 2) + math.Pow(newValue, 2)) / (nbF+1))
    if nbF == 0 { hMean = newValue
    } else {
        hMean = math.Pow(math.Pow(hMean/nbF, -1) + math.Pow(newValue, -1), -1) * (nbF+1) }
    dev = math.Sqrt(math.Pow(sqMean, 2) - math.Pow(aMean, 2))
    return nb+1, dev, aMean, sqMean, hMean
}

func main() {
    if len(os.Args) != 5 { os.Exit(84) }

    nb, err := strconv.ParseInt(os.Args[1], 10, 64)
    aMean, err2 := strconv.ParseFloat(os.Args[2], 64)
    hMean, err3 := strconv.ParseFloat(os.Args[3], 64)
    dev, err4 := strconv.ParseFloat(os.Args[4], 64)
    if err != nil || err2 != nil || err3 != nil || err4 != nil || nb < 0 || dev < 0 || hMean == 0 { os.Exit(84) }
    sqMean := math.Sqrt(math.Pow(dev, 2)+math.Pow(aMean, 2))

    for true {
        fmt.Printf("Enter next value: ")
        var s string
        a, _ := fmt.Scanln(&s)
        if a == 0 { os.Exit(84) }
        strings.TrimSpace(s)
        if s == "END" { os.Exit(0) }

        value, err := strconv.ParseFloat(s, 64)
        if err == nil && value > 0 {
            nb, dev, aMean, sqMean, hMean = neutrinos(nb, dev, aMean, sqMean, hMean, value)
            fmt.Printf("    Number of values:   %d\n", nb)
            fmt.Printf("    Standard deviation: %.2f\n", dev)
            fmt.Printf("    Arithmetic mean:    %.2f\n", aMean)
            fmt.Printf("    Root mean square:   %.2f\n", sqMean)
            fmt.Printf("    Harmonic mean:      %.2f\n\n", hMean)
        } else {
            os.Exit(84)
        }
    }
}