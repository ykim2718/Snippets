#!/bin/ksh
#941107,(c)shik
#951124,(c)shik

#########1#########2#########3#########4#########5#########6#########7#########8
file[0]="./d4su0302"
selectionTilde="vth,swing,ids0,bv1e-09,isub,ids5"
selectionSplit[0]="n-tr,25/0.55,~"     # device-name,device-size,parameter
selectionSplit[1]="n-tr,25/0.6, ~"     # device-name,device-size,parameter
selectionSplit[2]="n-tr,25/0.65,~"     # device-name,device-size,parameter
selectionSplit[3]="n-tr,25/0.7, ~"     # device-name,device-size,parameter
selectionSplit[4]="n-tr,25/0.8, ~"     # device-name,device-size,parameter
selectionSplit[5]="n-tr,25/1.0, ~"     # device-name,device-size,parameter
selectionSplit[6]="n-tr,25/2.0, ~"     # device-name,device-size,parameter
selectionSplit[7]="n-tr,25/25,  ~"     # device-name,device-size,parameter
selectionHead[0]="0.55"
selectionHead[1]="0.6"
selectionHead[2]="0.65"
selectionHead[3]="0.7"
selectionHead[4]="0.8"
selectionHead[5]="1.0"
selectionHead[6]="2.0"
selectionHead[7]="25"
command[0]="mv -f kshell-out-vth     n1.lch-vth    "
command[1]="mv -f kshell-out-swing   n1.lch-swing  "
command[2]="mv -f kshell-out-ids5    n1.lch-ids5   "
command[3]="mv -f kshell-out-ids0    n1.lch-ids0   "
command[4]="mv -f kshell-out-bv1e-09 n1.lch-bvdss  "
command[5]="mv -f kshell-out-isub    n1.lch-isub   "
command[6]="mv -f kshell-out-gmmax   n1.lch-gmmax  "
#########1#########2#########3#########4#########5#########6#########7#########8
# Do not modify anything below this line ! ######5#########6#########7#########8
#########1#########2#########3#########4#########5#########6#########7#########8

function extract_data_column { # $1 : pattern
                               # $2 : file *
   IFS=','
   p1=`print $1 | awk '{print $1}'`
   p2=`print $1 | awk '{print $2}'`
   p3=`print $1 | awk '{print $3}'`
   IFS=' '
   for object in $*
   do
      if [[ ! -a $object ]] then
         continue
      fi
      print ">>> $object : <$p1><$p2><$p3>"
      line=`grep -i ^$p1 $object | grep -i "$p2 " | grep -i $p3`
      print $line
      print -u3 -- `print $line | awk '{print $NF}'`
   done
}
function str_replace { # $1 : string
                       # $2 : src string
                       # $3 : dst string
   left=${1%$2*}
   right=${1#*$2}
#  echo "l=<$left>,r=<$right>,s=<$2>,d=<$3>"
   new="$left$3$right"
   echo $new
}
function extract_data_table { # global varaibles :
                              # ${file[*]},${selectionSplit[*]}
   \rm .out
   tilde_str="~"
   IFS=','
   for tilde in $selectionTilde
   do
      \rm .tmp-*
      integer i=1
      while ((1))
      do
         tmp=${selectionSplit[i]}
         if [[ -z $tmp ]] then
            break
         fi
         IFS=''
         object="`str_replace $tmp $tilde_str $tilde`"
         typeset -RZ3 i
         print ">>> `echo .tmp-$i` <<< $object"
         exec 3>|  .tmp-$i
         print -u3 $object
         print -u3 ${selectionHead[i]}
         extract_data_column $object ${file[*]}
         exec 3<&-
         typeset -i i
         i=i+1
      done
      print ${file[*]} > .out
      paste -d" " .tmp-* >> .out
      chmod 644 .out
      \mv .out "kshell-out-$tilde"
   done
}
extract_data_table 
i=0
while ((1))
do
  if [[ -z ${command[i]} ]] then
     break
  fi
  ${command[i]}
  if [[ $? != 0 ]] then
     echo "Error, ..... \"${command[i]}\""
     exit
  fi
  ((i=i+1))
done
\rm .out .tmp-*
echo "now completed ..... !"
