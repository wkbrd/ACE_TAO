#!/bin/sh
#
# $Id$
#
# This simple script is used to gather compile time metrics.  You can use
# it with make like this:
#
#  $ make CXX=g++_metric.sh
#

commandline=$@
# find the target and save it to a variable
until [ -z "$1" ] # test all command line parameters
do
  if [ "-o" = "$1" ]
  then
    shift
    target=$1
  break
  fi  
  shift
done

#unfortunately, time only goes down to seconds, so do it by hand...
start=`date +%s%N`
g++ $commandline
stop=`date +%s%N`

let "total = (${stop}-${start})"

# convert to microseconds even though we will only use milliseconds in the 
# graphs
let "total = ($total)/1000"

# add the path, relative to $ACE_ROOT, to the beginning of the object name
# so that it can be used to name the object when it's processed.  
echo "compile time: ${PWD#$ACE_ROOT/}/${target} $total"
