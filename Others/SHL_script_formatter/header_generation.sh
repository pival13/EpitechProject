#!/bin/sh

# Test Variable
declare -a outputOption="test.sh"


# Needed Variable for write_header()
declare -a headerContent=""
declare -a oldHeaderContent=""

write_header()
{
	#
	# oldHeaderContent (actual header of the input file)
	# has to be read and assigned.
	#

	headerContent+="##\t"
	headerContent+=""
	headerContent+="\n##\t Filename : "
	headerContent+=$outputOption
	headerContent+="\n##\t Date : "
	headerContent+=$(date "+%A %B %d, %Y")
	headerContent+="\n##\t User : "
	headerContent+=$USER
	headerContent+="\n##\t"
	headerContent+="\n##\t Description : A program that $USER needs to describe."
	headerContent+="\n##\t"
	headerContent+="\n##\t"
	headerContent+=$oldHeaderContent	
	headerContent+="\n##\t"

	if [[ $outputOption == "stdout" ]]
	then
		echo -e $headerContent
	else
		echo -e $headerContent >> $outputOption
	fi
}

write_header