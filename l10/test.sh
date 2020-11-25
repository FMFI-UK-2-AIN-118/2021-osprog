#!/usr/bin/env /bin/bash

source ../test/common.sh

[[ -r exploit.png ]] || die "No exploit present!"

echo "Running ./pnginfo exploit.png"
trap 'rm -f output' EXIT

# Force stdout to be unbuffered, otherwise the message won't be printed
# because the program will crash while the message is in the buffer.
# (stdout is line-buffered iff it is connected to an "interactive console")
# Note: a better solution would be to print to stderr (always line-buffered)
# or to explicitly flush the output, but I don't want to change the binary at
# this time.
./pnginfo exploit.png >output 2>&1

echo -e "Output:\n-----"
cat output
echo "-----"

if grep -q "Well done" output ; then
	msg "OK"
	exit 0
else
	err "Fail"
	exit 1
fi

# vim: set sw=4 sts=4 ts=4 noet :
