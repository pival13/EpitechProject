#! /usr/bin/env ruby

def parseContent(content)
    graph = {}
    compiled = nil
    content.split(/\n/).map { |l|
        m = l.match(/^(.+):\s*(.+)$/)
        if m then
            compiled, args = m[1], m[2]
            if not graph.has_key?(compiled)
                graph[compiled] = {"comm" => [], "dep" => []}
            end
            args.split.map { |v|
                if graph.has_key?(v)
                    graph[v]["dep"].append compiled
                else
                    graph[v] = {"comm" => [], "dep" => [compiled]}
                end
            }
        elsif compiled and l != ""
            graph[compiled]["comm"].append l
        end
    }
    return graph
end

def drawMatrix(graph)
    keys = graph.keys.sort
    keys.each { |key|
        print("[")
        print(keys.map { |key2| graph[key]["dep"].include?(key2) ? 1 : 0 }.join(' '))
        puts(']')
    }
end

def drawCompilation2(graph, key, before)
    if graph[key]["dep"].empty?
        puts before
    else
        graph[key]["dep"].sort.each { |key2|
            drawCompilation2(graph, key2, before + ' -> ' + key2)
        }
    end
end

def drawCompilation(graph)
    graph.keys.sort.each { |key|
        if not graph[key]["dep"].empty? then drawCompilation2(graph, key, key) end
    }
end

def drawCommands(graph, comm)
    deps = graph[comm]["dep"].sort

    comms = []
    deps.each { |dep|
        if graph.include?(dep)
            deps += graph[dep]["dep"].sort
            deps.uniq!
        end
    }
    deps.each { |dep|
        if graph.include?(dep)
            comms.append(graph[dep]["comm"])
        end
    }
    puts comms
end

if __FILE__ == $0
    args = $*
    if args.length != 1 and args.length != 2
        exit 84
    end
    if not File.exist?(args[0]) then exit 84 end
    file = File.open(args[0])
    content = file.read

    graph = parseContent(content)
    if args.length == 1
        drawMatrix(graph)
        puts
        drawCompilation(graph)
    elsif args.length == 2
        if not graph.include? args[1] then exit 84 end
        drawCommands(graph, args[1])
    end
    exit 0
end