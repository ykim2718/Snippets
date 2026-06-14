#!/bin/ksh 
#951126-28,(c)Yong-Shik Kim

#########1#########2#########3#########4#########5#########6#########7#########8
# Do not modify anything below this line ! ######5#########6#########7#########8
#########1#########2#########3#########4#########5#########6#########7#########8

while getopts :n:i:d: arguments
do
   case $arguments in
      n) headName=$OPTARG;;
      i) infoFile=$OPTARG;;
      d) ETinFile=$OPTARG;;
      :) print "Error, you forgot to enter an argument to \"-$OPTARG\""
         exit;;
   esac
done
divider="~"
if [[ -z $headName || -z $infoFile || -z $ETinFile || ! -r $ETinFile ]] then
   echo ""
   echo "- ET Extractor -"
   echo "  * 43281126-28,(c)shik,Logic PA,6595"
   echo "  * Usage; c5hs-ex.ksh -n <headName> -i <infoFile> -d <ETinfile>"
   echo "  * About <infoFile> ..."
   echo "       @vtfn-po                       <- @\"tailName\""
   echo "       N-PGFTR 25/0.8  Vth~0.8VTFN-PO <-  \"finding\"~\"header\""
   echo "       N-PGFTR 25/0.9  Vth~0.9VTFN-PO <-  \"finding\"~\"header\""
   echo "       @vtfn-m1                       <- @\"tailName\""
   echo "       N-M1FTR 25/0.8  Vth~0.8VTFN-M1 <-  \"finding\"~\"header\""
   echo "       N-M1FTR 25/0.9  Vth~0.8VTFN-M1 <-  \"finding\"~\"header\""
   echo "       <eof>"
   echo "    Note: outfile will be \"headName\"-\"tailName\""
   echo ""
   exit 1
fi
\rm -f .tmp-*
file=""
while read line
do
   if [[ -z $line ]] then
      continue
   fi
   if [[ $line = "@"* ]] then
      if [[ -n $file ]] then
         print "! $file" > $headName-$file
         paste -d" " .tmp-* >> $headName-$file
         \rm -f .tmp-*
      fi
      file=${line#*"@"} # right string
      typeset -i index=0
   elif [[ -z $file ]] then
      continue
   elif [[ $line = *$divider* ]] then
      string=${line%$divider*} # left string
      header=${line#*$divider} # right string
      typeset -RZ3 index
      print $header >> .tmp-$index
      grep -i ^"$string" $ETinFile | awk '{print $NF}' >> .tmp-$index
      typeset -i index
      index=index+1
   fi
done < $infoFile
      if [[ -n $file ]] then
         print "! $file" > $headName-$file
         paste -d" " .tmp-* >> $headName-$file
         \rm -f .tmp-*
      fi
echo "\"$0 $headName $infoFile $ETinFile\" now completed ..... !"
exit 0

#########1#########2#########3#########4#########5#########6#########7#########8
