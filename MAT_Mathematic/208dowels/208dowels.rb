#! /usr/bin/env ruby

$x2Distribution = [
    {99 => 0, 90 => 0, 80 => 0, 70 => 0, 60 => 0, 50 => 0, 40 => 0, 30 => 0, 20 => 0, 10 => 0, 05 => 0, 02 => 0, 01 => 0},
    {99 => 0.00, 90 => 0.02, 80 => 0.06, 70 => 0.15, 60 => 0.27, 50 => 0.45, 40 => 0.71, 30 => 1.07, 20 => 1.64, 10 => 2.71, 05 => 3.84, 02 => 5.41, 01 => 6.63},
    {99 => 0.02, 90 => 0.21, 80 => 0.45, 70 => 0.71, 60 => 1.02, 50 => 1.39, 40 => 1.83, 30 => 2.41, 20 => 3.22, 10 => 4.61, 05 => 5.99, 02 => 7.82, 01 => 9.21},
    {99 => 0.11, 90 => 0.58, 80 => 1.01, 70 => 1.42, 60 => 1.87, 50 => 2.37, 40 => 2.95, 30 => 3.66, 20 => 4.64, 10 => 6.25, 05 => 7.81, 02 => 9.84, 01 => 11.34},
    {99 => 0.30, 90 => 1.06, 80 => 1.65, 70 => 2.19, 60 => 2.75, 50 => 3.36, 40 => 4.04, 30 => 4.88, 20 => 5.99, 10 => 7.78, 05 => 9.49, 02 => 11.67, 01 => 13.28},
    {99 => 0.55, 90 => 1.61, 80 => 2.34, 70 => 3.00, 60 => 3.66, 50 => 4.35, 40 => 5.13, 30 => 6.06, 20 => 7.29, 10 => 9.24, 05 => 11.07, 02 => 13.39, 01 => 15.09},
    {99 => 0.87, 90 => 2.20, 80 => 3.07, 70 => 3.83, 60 => 4.57, 50 => 5.35, 40 => 6.21, 30 => 7.23, 20 => 8.56, 10 => 10.64, 05 => 12.59, 02 => 15.03, 01 => 16.81},
    {99 => 1.24, 90 => 2.83, 80 => 3.82, 70 => 4.67, 60 => 5.49, 50 => 6.35, 40 => 7.28, 30 => 8.38, 20 => 9.80, 10 => 12.02, 05 => 14.07, 02 => 16.62, 01 => 18.48},
    {99 => 1.65, 90 => 3.49, 80 => 4.59, 70 => 5.53, 60 => 6.42, 50 => 7.34, 40 => 8.35, 30 => 9.52, 20 => 11.03, 10 => 13.36, 05 => 15.51, 02 => 18.17, 01 => 20.09},
    {99 => 2.09, 90 => 4.17, 80 => 5.38, 70 => 6.39, 60 => 7.36, 50 => 8.34, 40 => 9.41, 30 => 10.66, 20 => 12.24, 10 => 14.68, 05 => 16.92, 02 => 19.68, 01 => 21.67},
    {99 => 2.56, 90 => 4.87, 80 => 6.18, 70 => 7.27, 60 => 8.30, 50 => 9.34, 40 => 10.47, 30 => 11.78, 20 => 13.44, 10 => 15.99, 05 => 18.31, 02 => 21.16, 01 => 23.21}
]

def factorielle(x)
    v = 1.0
    for i in 0..x-1
        v *= i+1
    end
    return v
end

def coefBino(nb, total)
    return factorielle(total) / (factorielle(nb) * factorielle(total-nb))
end

def getFit(x2, v)
    fitLine = $x2Distribution[v]
    if x2 < fitLine[99] then return "P > 99%" end
    prev = 0
    for prct, pb in fitLine
        if x2 < pb then return "#{prct}% < P < #{prev}%" end
        prev = prct
    end
    return "P < 1%"
end

def completeValues(values)
    proba = (values.sum { |v| v['value'] * v['index'].to_i}).to_f / 100 / 100

    for i in 0..values.length-1
        values[i]['theory'] = 100 * coefBino(values[i]['index'].to_i, 100) * proba**values[i]['index'].to_i * (1-proba)**(100-values[i]['index'].to_i)
    end

    i = 0
    while 1
        if i >= values.length then break end
        if values[i]['value'] < 10
            j = i == 0 ? 1 : (i+1 >= values.length ? i-1 : (values[i-1]['value'] < values[i+1]['value'] ? i-1 : i+1))
            if j < i then i, j = j, i end
            values[i]['value'] += values[j]['value']
            values[i]['theory'] += values[j]['theory']
            values[i]['index'] = ("#{values[i]['index'][0]}-#{values[j]['index'][-1]}")
            values.delete_at(j)
        else
            i += 1
        end
    end
    values[-1]['index'] = values[-1]['index'][0] + "+"
    values[-1]['theory'] = 100.0 - values.sum { |value| value != values[-1] ? value['theory'] : 0 }

    return values, proba
end

if __FILE__ == $0 # If __name__ == "__main__"
    args = $*
    if args.length != 9 or args.any? { |s| s.scan(/\D/).length != 0 } or args.sum { |v| v.to_i } != 100
        exit 84
    end
    
    values = []
    args.each_index { |i| values += [{"value"=>args[i].to_i, "index"=>i.to_s}] }
    values, proba = completeValues(values)

    print "   x    | "
    values.each { |value| print "#{value['index'].ljust(5)} | " }
    puts "Total"
    print "  Ox    | "
    values.each { |value| print "#{value['value'].to_s.ljust(5)} | " }
    puts args.sum { |v| v.to_i }
    print "  Tx    | "
    values.each { |value| print "#{value['theory'].round(1).to_s.ljust(5)} | " }
    puts 100

    puts "Distribution:           B(100, #{proba.round(4).to_s.ljust(6,'0')})"
    x2 = values.sum { |v| (v['value'] - v['theory'])**2 / v['theory'] }
    puts "Chi-squared:            #{x2.round(3).to_s.ljust(4+(x2.floor.to_s.length), '0')}"
    puts "Degrees of freedom:     #{values.length-2}"
    puts "Fit validity:           #{getFit(x2, values.length-2)}"
end