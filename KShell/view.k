#!/bin/ksh
#960828,0912(c)shik

#########1#########2#########3#########4#########5#########6#########7#########8
#Do not modify anything below this line !

tmpFile="/tmp/tmp-view.k"

function extractGrInputFrKshell { # in  -> $0 = this file
   integer FOUND=0
   \rm -f $tmpFile-GR
   echo $0 > $tmpFile-GR
   while read line
   do
      if [[ $line = "%gBeg_" ]] then
         FOUND=1
      fi
      if (( $FOUND == 1 ))
      then
         echo $line >> $tmpFile-GR
      fi
   done < $1
   if [[ $FOUND != 1 ]] then
      echo "Error, %gBeg_ not found ... in K-shell"
      exit
   fi
}
function runGr { # in -> $tmpFile-GR
   if [[ ! -a $tmpFile-GR ]] then
      echo "Error, $tmpFile-GR not found ... in K-shell"
      exit
   fi
   integer nrl nrh
   \rm -f $tmpFile-GR-TMP
   for f in $*
   do
      print ">>> \"" $f "\" drawing ....."
      sed -e "s/K_FILE/$f/g"  $tmpFile-GR > $tmpFile-GR-TMP
      grx -s $tmpFile-GR-TMP -geometry 600x800+0+0
   done
}
function getridofTemporaryFile {
   \rm -f $tmpFile-*
}
function strReplace { # $1 : string
                      # $2 : src string
                      # $3 : dst string
   left=${1%$2*}
   right=${1#*$2}
#  echo "l=<$left>,r=<$right>,s=<$2>,d=<$3>"
   new="$left$3$right"
   echo $new
}
getridofTemporaryFile
extractGrInputFrKshell $0
runGr $*
getridofTemporaryFile
exit

K_FILE  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

%gBeg_
 .glob 
       gtxt txt="K_FILE" t.size=15 t.color=red
 .plot 
       attr xlin ylin
       data name="K_FILE"
       slct yno=(*) xno=1
       +    lg.type=1 line_hidden symb.size=0.2 symb.color="yellow"
       axis type=x,0 label=t lb.f="%1.0h" t.size=10 t.align=32
       +    type=x,1 axis=u
       +    type=y,0 label=t lb.f="%1.0h" t.size=10 t.align=12 t.angle=90
       +    type=y,1 axis=u
       text type=1 txt="X" t.size=10 t.align=22
       +    type=2 txt="Y" t.size=10 t.align=22
%gEnd_
