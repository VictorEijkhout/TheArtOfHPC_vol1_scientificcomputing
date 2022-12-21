#!/bin/bash

cat <<EOF >input
a
b
c
EOF

cat input \
    | sed -e '/b/i\
foo
' \
	  -e '/b/a\
bar
' \
	  >output

cat output
