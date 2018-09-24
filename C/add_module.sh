#!/bin/sh

CP="cp -ar"

if [ $# -lt 1 ]; then
    echo "usage: $0 module_name"
    exit 1
fi

cd `dirname $0`

mkdir -p $1/{bin,obj,include,src}

touch .gitkeep

${CP} .gitkeep $1/bin
${CP} .gitkeep $1/obj
${CP} .gitkeep $1/include
${CP} .gitkeep $1/src

rm .gitkeep

echo "success"