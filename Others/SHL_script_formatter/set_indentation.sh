#!/bin/sh

# Test Variable
spacesOption=true
declare -i indentationOption=8

# Needed variable for set_indent()
declare -a indentation="\t\t"

set_indent()
{
	indentation=""
	if [ $spacesOption = true ]
	then
		for (( i = 1; i <= $indentationOption; i++ ))
		do
			indentation+=" "
		done
	else
		for (( i = 4; i <= $indentationOption; i+=4 ))
		do
			indentation+="\t"
		done
	fi

}

set_indent

echo -e "$indentation"   # Quotes are important here, without,
					     # the spaces are ignored.