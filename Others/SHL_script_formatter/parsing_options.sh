#!/bin/sh

argTab=("$@")

extendOption=false
headerOption=false
spacesOption=false
declare -i indentationOption=8
declare -a outputOption=stdout

set_options()
{
	for ((i = 0; i < $#; ++i))
	do
		param=${argTab[i]}
		param2=${argTab[i+1]}
	
		if [[ $param == "--"* ]]
			then
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
				if [ $indentationOption -le 0 ]
				then
					exit 84
				fi
			fi
			if [[ $param == *"o"* ]]
			then
				outputOption=$param2
				if [[ $outputOption == "" ]]
				then
					exit 84
				fi
			fi
		fi
		
	done
}

echo -e "extendOption \t\t=" $extendOption
echo -e "headerOption \t\t=" $headerOption
echo -e "spacesOption \t\t=" $spacesOption
echo -e "indentationOption \t=" $indentationOption
echo -e "outputOption \t\t=" $outputOption