#!/bin/bash

var=$true
if [ $var ]; then
  echo "This won't print, var is false!"
fi
