#!/bin/bash

cat <<EOF >input
a
b
c
EOF

sed '2 a foobar' input > output

cat output
