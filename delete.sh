#!/bin/bash

trash=$(pwd)
echo "Deleting $trash"
cd ..
rm -r "$trash"