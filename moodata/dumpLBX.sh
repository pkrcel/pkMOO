#!/bin/bash

# helper function  - straight copy from StackOverflow (still a bash noob here!)
die () {
    echo >&2 "$@"
    exit 1
}

# preliminary usage checks, should be enuff safe for us
[ "$#" -le 1 ] && die "This script needs two parameters, $# provided"
[ -d "$1" ] || die "Source directory not found or invalid"
[ -d "$2" ] || die "non-existent or invalid Destination Directory"

# the meat of the deal, all found LBX containers in the source directory are 
# dumped in a txt files with offsets and (eventually) names
# will probably enhance this as we enhance the LBX handler.

for file in $1/*; do
	filename=$(basename "$file")
	extension="${filename##*.}"
	filename="${filename%.*}"
	if [ $extension = "LBX" ]; then
		echo $filename "-" $extension "- OK!"
			./moo1LBXHandler.exe $1/$filename.$extension $2/$filename.txt
	else
		echo "Skipped non-LBX Container File: " $filename
	fi
done
