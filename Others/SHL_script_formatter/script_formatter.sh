#!/bin/sh

declare -A shebang
declare -A header
declare -A lines

declare -a headerContent=""
declare -a oldHeaderContent=""

declare -a indentation="\t"

declare -i indentationOption=8
declare -a outputOption=stdout
extendOption=false
headerOption=false
spacesOption=false

writeToFile()
{
    if [[ $outputOption == "stdout" ]]
    then
        echo -e "$1"
    else
        echo -e "$1" >> $outputOption
    fi
}

display_out()
{
    ix=0
    while [ $ix -lt ${#lines[*]} ]; do
        writeToFile "${lines[$ix]}"
        ix=$(($ix+1))
    done
}

initiate_array()
{
    IFS='
'
    isHeader=1
    for line in $(<$1); do
        if [[ "$line" =~ ^\# ]]; then
            if [[ "$line" =~ ^\#\s*\! ]]; then
                shebang[${#shebang[*]}]="$line"
            elif [ $isHeader -eq 1 ]; then
                header[${#header[*]}]="$line"
            else
                lines[${#lines[*]}]="$line"
            fi
        else
            isHeader=0
            lines[${#lines[*]}]="$line"
        fi
    done
    IFS=' '
}

append()
{
    tmp="$1"
    tmp2=""
    ix=0
    while [ $ix -lt ${#lines[*]} ]; do
        if [ $ix -ge $2 ]; then
            tmp2="${lines[$ix]}"
            lines[$ix]=$tmp
            tmp=$tmp2
        fi
        ix=$(($ix+1))
    done
    lines[$ix]=$tmp2
}

remove()
{
    ix=0
    while [ $ix -lt ${#lines[*]} ]; do
        if [ $ix -ge $1 ]; then
            lines[$ix]=${lines[$(($ix+1))]}
        fi
        ix=$(($ix+1))
    done
    unset lines[$((${#lines[*]}-1))]
}

set_indent()
{
    indentation=""
    i=$indentationOption
    if [ $spacesOption = true ]
    then
        for ((; i != 0; i-- ))
        do
            indentation+=" "
        done
    else
        for ((; i >= 8; i-=8 ))
        do
            indentation+="\t"
        done
        for ((; i != 0; i-- ))
        do
            indentation+=" "
        done
    fi
}

help()
{
    echo -e "Usage:  script_formatter.sh in [-h] [-s] [-i nb_char] [-e] [-o out]\n"
    echo -e "        in                        input file"
    echo -e "        -h, --header              header generation"
    echo -e "        -s, --spaces              force spaces instead of tabulations for indentation"
    echo -e "        -i, --indentation=nb_char number of characters for indentation (8 by default)"
    echo -e "        -e, --expand              force do and then keywords on new lines"
    echo -e "        -o, --output=out          output file (stdout by default)"
}

set_options()
{
    argTab=("$@")
    declare -i x=0
    for ((i = 0; i < $#; ++i))
    do
        param=${argTab[i]}
        param2=${argTab[i+1]}
        param3=${argTab[i+2]}
        if [[ $param == "--"* ]]; then
            if [[ $param == "--help" ]]; then
                help
                exit 0
            fi
            if [[ $param == "--extend" ]]
            then
                extendOption=true
            elif [[ $param == "--header" ]]
            then
                headerOption=true
            elif [[ $param == "--spaces" ]]
                then
                spacesOption=true
            elif [[ $param == "--indentation="* ]]
                then
                indentationOption=$(echo $param | cut -c 15)
                if [ $indentationOption -le 0 ]
                then
                    exit 84
                fi
            elif [[ $param == "--output="* ]]
                then
                outputOption=$(echo $param | cut -c 10)
                if [[ $outputOption == "" ]]
                then
                    exit 84
                fi
                rm -f $param2
            fi
        elif [[ $param == "-"* ]]
        then
            if [[ $param == *"e"* ]]
            then
                extendOption=true
            fi
            if [[ $param == *"h"* ]]
            then
                headerOption=true
            fi
            if [[ $param == *"s"* ]]
            then
                spacesOption=true
            fi
            if [[ $param == *"i"* ]]
            then
                indentationOption=$param2
                if [ $indentationOption = 0 ]; then
                    indentationOption=$param3
                    x=0
                else
                    x=1
                fi
                if [ $indentationOption = 0 ]; then
                    indentationOption=$param2
                    x=1
                fi
                if [ $indentationOption -le 0 ]
                then
                    exit 84
                fi
            fi
            if [[ $param == *"o"* ]]
            then
                outputOption=$param2
                if [ $x = 1 ]; then
                    outputOption=$param3
                fi
                if [[ $outputOption == "" ]]
                then
                    exit 84
                fi
                rm -f $param2
            fi
        fi
        x=0
    done

    unset argTab
}

write_header()
{
    if [ $headerOption = false ]; then
        if [ ${#header[*]} -eq 0 ]; then
            return
        fi
        for (( x = 0; x < ${#header[*]}; x++ )); do
            headerContent+="${header[$x]}\n"
        done
        writeToFile "$headerContent"
        unset headerContent
        return
    fi

    formatDate=$(LC_TIME=en_EN date +"%d %B, %Y")

    if [ "{formatDate:0:2}" = "01" ]; then
        formatDate=$(LC_TIME=en_EN date +"%dst %B, %Y")
    elif [ "${formatDate:0:2}" = "02" ]; then
        formatDate=$(LC_TIME=en_EN date +"%dnd %B, %Y")
    elif [ "${formatDate:0:2}" = "03" ]; then
        formatDate=$(LC_TIME=en_EN date +"%drd %B, %Y")
    else
        formatDate=$(LC_TIME=en_EN date +"%dth %B, %Y")
    fi

    headerContent+="#####################"
    headerContent+="\n#"
    headerContent+="\n# "
    if [[ $outputOption != stdout ]]; then
        headerContent+=$outputOption
    else
        headerContent+="no filename"
    fi
    headerContent+="\n# "
    headerContent+=$formatDate
    headerContent+="\n# "
    for (( x = 0; x < ${#header[*]}; x++ )); do
        headerContent+="${header[$x]}"
        if [ $(($x+1)) != ${#header[*]} ]; then
            headerContent+="\n"
        fi
    done
    headerContent+="\n#####################"
    headerContent+="\n"

    writeToFile "$headerContent"

    unset formatDate
    unset headerContent
}

write_shebang()
{
    shebang_content=""

    for ((i=0; i < ${#shebang[@]}; i++))
    do
        if [[ $shebang_content != "" && ${shebang_content: -1} != "\n" ]]; then
            shebang_content+="\n"
        fi
        if [[ ${shebang[$i]} =~ \#\!\s*([^\ ]+) ]]; then
            actual_shebang=${BASH_REMATCH[1]}
        fi
        if [[ -f "$actual_shebang" ]] && [[ -x "$actual_shebang" ]]; then
            shebang_content+=$(echo -e ${shebang[$i]} | egrep '^#!([ \t\n\f\r]+|)/[^ \t\n\f\r]+')
        fi
    done

    if [[ ${shebang_content: -1} == "\n" ]]; then
        shebang_content=${shebang_content: : -1}
    fi

    if [[ $shebang_content == "" ]]; then
        if [[ -f "/bin/sh" ]] && [[ -x "/bin/sh" ]]; then
            shebang_content="#!/bin/sh"
        elif [[ -f "/bin/bash" ]] && [[ -x "/bin/bash" ]]; then
            shebang_content="#!/bin/bash"
        fi
    fi

    shebang_content+="\n"

    writeToFile $shebang_content
    
    unset shebang_content
}

cut_do_then_expand()
{
    if [[ "${lines[$i]}" =~ (;[^;]*(do|then).*)$ ]]; then
        occurence="${BASH_REMATCH[1]}"
        occurence="${occurence:2:${#occurence}}"
        append "$occurence" $(($i+1))
        lines[$i]="${lines[$i]:0:${#lines[$i]} - ${#occurence}-2}"
    fi
}

cut_do_then_not_expand()
{
    if [[ "${lines[$i]}" == "do" ]] || [[ "${lines[$i]}" == "then" ]]; then
        lines[$(($i-1))]+="; ${lines[$i]}"
        remove $i
        i=$(($i-1))
    fi
}

cut_do_then()
{
    while [ "${lines[$i]::1}" = " " ] || [ "${lines[$i]::1}" = "\t" ]; do
        lines[$i]="${lines[$i]:1}"
    done
    while [ "${lines[$i]:$((${#lines[$i]}-1))}" = " " ] || [ "${lines[$i]:$((${#lines[$i]}-1))}" = "\t" ]; do
        lines[$i]="${lines[$i]::-1}"
    done

    if [ $extendOption = true ]; then
        cut_do_then_expand
    else
        cut_do_then_not_expand
    fi
}

cut_line()
{
    stringMode=false
    valueMode=false

    if [[ "${lines[$i]}" != *"{"* ]] && [[ "${lines[$i]}" != *"}"* ]]; then
        return
    fi

    if [ ${#lines[$i]} != 1 ] && [[ "${lines[$i]:$((1)):1}" != "\n" ]] && ([[ "${lines[$i]}" == "{"* ]] || [[ "${lines[$i]}" == "}"* ]]); then
        append "${lines[$i]:1}" $(($i+1))
        lines[$i]="${lines[$i]:0:1}"
        unset stringMode
        return
    fi

    for (( j=0; j < ${#lines[$i]} ; j++ )); do
        char="${lines[$i]:$(($j)):1}"
        if [[ $j > 0 ]]; then
            charb="${lines[$i]:$(($j-1)):1}"
        fi

        if [ "${char:-"_"}" = \" ]; then
            if [ $stringMode = false ]; then
                stringMode=true
            elif [ $stringMode = true ]; then
                stringMode=false
            fi
        fi
        

        if [ "${charb:-"_"}" = "$" ] && [ "${char:-"_"}" = "{" ]; then
            valueMode=true
        fi

        if ([ "${char:-"_"}" = "{" ] || [ "${char:-"_"}" = "}" ]) && [ $j != 0 ]; then
            if [ "${charb:-"_"}" != "\\" ] && [ $stringMode = false ] && [ $valueMode = false ]; then
                append "${lines[$i]:$j}" $(($i+1))
                lines[$i]="${lines[$i]:0:$(($j-1))}"
                unset stringMode
                unset char
                unset charb
                return
            fi
        fi

        if [ "${char:-"_"}" = "}" ] && [ $valueMode = true ]; then
            valueMode=false
        fi
    done
    unset stringMode
    unset char
    unset charb
}

parse_lines() 
{ 
    i=0
    nb_indent=0
    is_comment=false

    while [ $i -lt ${#lines[*]} ]; do
        while [[ "${lines[$i]}" =~ ^[[:blank:]]+ ]]; do
            lines[$i]="${lines[$i]:1}"
        done

        while [[ "${lines[$i]}" =~ [[:blank:]]$ ]]; do
            lines[$i]="${lines[$i]::-1}"
        done
        
        if [ "${lines[$i]}" != "" ] && [[ "${lines[$i]}" != "#"* ]]; then
            cut_line
            cut_do_then
        elif [ "${lines[$i]}" = "" ]; then
            remove $i
            i=$(($i-1))
        fi

        i=$(($i+1))
    done

    i=0
    while [ $i -lt ${#lines[*]} ]; do
        
        for (( j=0; j < ${#lines[$i]}; j++ )); do
            if [ "${lines[$i]:$j:1}" == "\\" ]; then
                lines[$i]=${lines[$i]::$j}\\${lines[$i]:$j}
                j=$(($j+1))
            fi
        done

        if [[ "${lines[$i]}" =~ ^\s*\# ]]; then
            is_comment=true
        fi

        for (( j=0; j<$nb_indent; j++ )); do
            lines[$i]=${indentation}${lines[$i]}
        done

        if [ $is_comment = false ]; then
            if [[ "${lines[$i]}" =~ (.*)(then|do|in|else|\{)$ ]]; then
                tmp=${BASH_REMATCH[1]:$((${#BASH_REMATCH[1]}-1))}
                if [ ${#BASH_REMATCH[1]} -eq 0 ] || [[ ${tmp} = " " ]] || [ ${tmp} = \t ]; then
                    nb_indent=$(($nb_indent+1))
                fi
            fi

            if [[ "${lines[$(($i+1))]}" =~ ^\s*(fi|done|esac|else|elif .+|\})$ ]]; then
                nb_indent=$(($nb_indent-1))
            fi
        fi

        if [ "${lines[$i]}" = "{" ] && [ $i -ne 1 ] && [ "${#lines[$(($i-2))]}" -ne 0 ]; then
            append "" $(($i-1))
            i=$(($i+1))
        fi
        if [ "${lines[$i]}" = "}" ] && [ "${#lines[$(($i+1))]}" -ne 0 ]; then
            if [ "${#lines[$(($i+1))]}" -ne 1 ] || [[ "${lines[$(($i+1))]}" =~ [\w\{\}] ]]; then
                append "" $(($i+1))
                i=$(($i+1))
            fi
        fi

        is_comment=false
        i=$(($i+1))
    done
}

initiate_array $1

set_options $@
set_indent

write_shebang
write_header

parse_lines

display_out