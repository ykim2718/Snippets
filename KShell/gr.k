#!/bin/ksh -x
#960405,0913(c)shik

#########1#########2#########3#########4#########5#########6#########7#########8
beg="dc transfer curves"
end="job concluded"
#########1#########2#########3#########4#########5#########6#########7#########8

tmpFile="/tmp/tmp-gr.k"
function extractFrFile { # $1  : file
                         # $2  : begin comment
                         # $3  : end comment
                         # out : standard out
   integer FOUND=0
   while read line
   do
      if [[ $line = *"$2"* ]] then
         FOUND=1
      elif [[ $line = *"$3"* ]] then
         FOUND=0
      fi
      if (( $FOUND == 1 ))
      then
         print -u1 -- $line
      fi
   done < $1
}

if [[ ! -a $1 ]] then
   echo "Error, \"$1\" not found ..."
   exit
fi
IFS=''
extractFrFile $1 $beg $end > $tmpFile
IFS=' '
grx -s  $0 -geometry 800x800+0+0 &
exit

Do not modify anything below this line !

%gBeg_
 .glob
       gtxt txt="HSPICE" t.size=15 t.color=red
 .plot
       attr xlin ylin
       data name="/tmp/tmp-gr.k"
       slct yno=(*) xno=1
       +    lg.type=1 line_hidden symb.size=0.5 symb.color="yellow"
       axis type=x,0 label=t lb.f="%1.0h" t.size=10 t.align=32
       +    type=x,1 axis=u
       +    type=y,0 label=t lb.f="%1.0h" t.size=10 t.align=12 t.angle=90
       +    type=y,1 axis=u
       text type=1 txt="X" t.size=10 t.align=22
       +    type=2 txt="Y" t.size=10 t.align=22
%gEnd_
