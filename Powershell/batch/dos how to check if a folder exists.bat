@echo off
: y, 2019.10.18
: http://www.computerhope.com/batch.htm
: http://en.wikibooks.org/wiki/Windows_Programming/Programming_CMD

set git_folder=.\git_folder
if exits %git_folder% (
   echo 'existed'
) else (
   echo 'created'
)
