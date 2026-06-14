#!/bin/ksh
#csp7,(copyLeft)shik,970823

#########1#########2#########3#########4#########5#########6#########7#########8
name="??????,N-ISOLATION@M1"
path=".\/O"
file[0]="n01"
file[1]="n02"
file[2]="n03"
file[3]="n04"
range=99
lgType=1
#########1#########2#########3#########4#########5#########6#########7#########8
# Do not modify anything below this line ! ######5#########6#########7#########8
#########1#########2#########3#########4#########5#########6#########7#########8

tmpFile="/usr/tmp/$0"
function extrGrFile { # in  -> $1 : k-shell & gr-format-file name
                      # out -> $tmpFile-Gr
   integer FOUND=0
   \rm -f $tmpFile-Gr
   while read line
   do
      if [[ $line = "%gBeg_" ]] then
         FOUND=1
      fi
      if (( $FOUND == 1 ))
      then
         echo $line >> $tmpFile-Gr
      fi
   done < $1
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
function noOfArray { # $1 : array
   integer count=0
   for array in $*
   do
      count=count+1
   done
   echo $count
}

\rm -f $tmpFile-*
extrGrFile $0
csplit -s -f $tmpFile- $tmpFile-Gr /"! (c)shik"/ {12}
\rm -f $tmpFile-Gr
typeset -i count="`noOfArray ${file[*]}`"
for indexOfFile in 01 03 05 07 09 11
do
   sed -e "s/XXX_LGTYPE/$lgType/g" $tmpFile-$indexOfFile > $tmpFile-99
   \mv $tmpFile-99 $tmpFile-$indexOfFile
done
if (( $count != 1 ))
   then
   typeset -i lgType
   typeset -i index=1
   while (( $index < $count ))
   do
      for indexOfFile in 02 04 06 08 10 12
      do
         
         sed -e "s/XXX_FILE/${file[$index]}/g" -e "s/XXX_RANGE/$range/g"\
             $tmpFile-$indexOfFile > $tmpFile-$indexOfFile$index
         if (( $lgType != 0 ))
            then
            lgType=index+1
            sed -e "s/XXX_LGTYPE/$lgType/g" $tmpFile-$indexOfFile$index > $tmpFile-99
            \mv $tmpFile-99 $tmpFile-$indexOfFile$index
         else
            sed -e "s/XXX_LGTYPE/0/g" $tmpFile-$indexOfFile$index > $tmpFile-99
            \mv $tmpFile-99 $tmpFile-$indexOfFile$index
         fi
      done
      index=index+1
   done
fi

\rm -f $tmpFile-0[2468] $tmpFile-1[02]
cat $tmpFile-[0-9][0-9]* > $tmpFile-Gr
sed -e "s/XXX_NAME/$name/g" \
    -e "s/XXX_FILE/${file[0]}/g" \
    -e "s/XXX_RANGE/$range/g" \
    -e "s/XXX_PATH/$path/g"  $tmpFile-Gr > $tmpFile-Gr.p
\rm -f $tmpFile-Gr $tmpFile-[0-9][0-9]*
grxSUN $tmpFile-Gr.p -geometry 600x800+0+0 -s
########## 961104(c)shik
\mv -f $tmpFile-Gr.p.ps $0.ps;echo "\"$0.log\" written ..."
csplit -s -f $tmpFile-core- $tmpFile-Gr.p.log /"--C---N---V---T--"/
csplit -s -f $tmpFile-core- $tmpFile-core-01 /"--G---O---U---T--"/
cat $tmpFile-core-00 > $0.dat;echo "\"$0.dat\" written ..."
##
\rm -f $tmpFile-*
exit

#########1#########2#########3#########4#########5#########6#########7#########8

! (c)shik : core-00
%gBeg_
 _defn "XA_0" "type=x,0 label=t lb.f="%1.1f" tc.majsp=0.1 tc.minsp=0.1 TEXT4"
 _defn "XA_1" "type=x,1 loc=upper            tc.majsp=0.1 tc.minsp=0.1"
 _defn "YA2"  "type=y,2 loc=any x=0.6 y=(0,5) tick=n a.color=blue"
 _defn "view_1/6" "view x1=0.20 x2=0.45 y1=0.65 y2=0.90"
 _defn "view_2/6" "view x1=0.55 x2=0.80 y1=0.65 y2=0.90"
 _defn "view_3/6" "view x1=0.20 x2=0.45 y1=0.35 y2=0.60"
 _defn "view_4/6" "view x1=0.55 x2=0.80 y1=0.35 y2=0.60"
 _defn "view_5/6" "view x1=0.20 x2=0.45 y1=0.05 y2=0.30"
 _defn "view_6/6" "view x1=0.55 x2=0.80 y1=0.05 y2=0.30"
 _defn "view_1/4" "view x1=0.15 x2=0.45 y1=0.55 y2=0.90"
 _defn "view_2/4" "view x1=0.55 x2=0.85 y1=0.55 y2=0.90"
 _defn "view_3/4" "view x1=0.15 x2=0.45 y1=0.05 y2=0.40"
 _defn "view_4/4" "view x1=0.55 x2=0.85 y1=0.05 y2=0.40"
 _defn "view_1/2" "view x1=0.10 x2=0.45 y1=0.25 y2=0.65"
 _defn "view_2/2" "view x1=0.55 x2=0.90 y1=0.25 y2=0.65"
 _defn "view|1/2" "view x1=0.30 x2=0.80 y1=0.55 y2=0.90"
 _defn "view|2/2" "view x1=0.30 x2=0.80 y1=0.05 y2=0.40"
 _defn "LOGA"     "lb.f="%1.0f" lb.p="z=log10(z)""
 _defn "TEXT4"    "t.size=4 t.align="22""
 _defn "LGTEXT"   "t.size=4"
 _defn "SYMBOL"   "symb.size=1 symb.stipple=10 symb.polyarc=0 symb.color=red"
 _defn "XB"       "xlb=0.3 xub=0.7"
 _defn "YB"       "ylb=0 yub=12"
 .glob 
       gtxt txt="XXX_NAME" t.width=10 t.height=20
       gout ps portrait
! (c)shik : core-01
 .plot 
       attr moment ylin
       data name="XXX_PATH/csp7l-inch.XXX_FILE.plt" switch
       slct yno=(*) xno=1 XB YB range=XXX_RANGE nrl=1 nrh=5
       +    type=XXX_LGTYPE SYMBOL
       axis type=y,0 label=t lb.f="%g" TEXT4 tc.majsp=2
       +    type=y,1 loc=upper               tc.majsp=2
       +    XA_0 XA_1 YA2
       text type=2 txt="BV [V] (ACT SPACE W.Ti)"
       text type=5 txt="XXX_RANGE%" t.size=1
       view|1/2
! (c)shik : core-02
 .plot 
       attr back moment
       data name="XXX_PATH/csp7l-inch.XXX_FILE.plt" switch
       slct yno=(*) xno=1 range=XXX_RANGE nrl=1 nrh=5
       +    type=XXX_LGTYPE legn.size=1 SYMBOL
! (c)shik : core-03
 .plot
       attr moment
       data name="XXX_PATH/csp7l-inch.XXX_FILE.plt" switch
       slct yno=(*) xno=1 XB YB range=XXX_RANGE nrl=6 nrh=9
       +    type=XXX_LGTYPE SYMBOL legn.size=1 LGTEXT legn.txt="XXX_FILE" x=0.75
       axis type=y,0 label=t lb.f="%g" TEXT4 tc.majsp=2
       +    type=y,1 loc=upper               tc.majsp=2
       +    XA_0 XA_1 YA2
       text type=2 txt="BV [V] (ACT SPACE WO.Ti)"
       view|2/2
! (c)shik : core-04
 .plot 
       attr back moment
       data name="XXX_PATH/csp7l-inch.XXX_FILE.plt" switch
       slct yno=(*) xno=1 range=XXX_RANGE nrl=6 nrh=9
       +    type=XXX_LGTYPE SYMBOL legn.size=1 LGTEXT legn.txt="XXX_FILE"
! (c)shik : core-05
!.plot 
!      attr moment ylin
!      data name="XXX_PATH/csp7l-inch.XXX_FILE.plt" switch
!      slct yno=(*) xno=1 XB YB range=XXX_RANGE nrl=10 nrh=13
!      +    type=XXX_LGTYPE SYMBOL
!      axis type=y,0 label=t lb.f="%g" TEXT4 tc.majsp=2
!      +    type=y,1 loc=upper               tc.majsp=2
!      +    XA_0 XA_1 YA2
!      text type=2 txt="NFTRGP VTH [V]"
!      view_3/6
! (c)shik : core-06
!.plot 
!      attr back moment
!      data name="XXX_PATH/csp7l-inch.XXX_FILE.plt" switch
!      slct yno=(*) xno=1 XB YB range=XXX_RANGE nrl=10 nrh=13
!      +    type=XXX_LGTYPE SYMBOL
! (c)shik : core-07
!.plot 
!      attr moment
!      data name="XXX_PATH/csp7l-inch.XXX_FILE.plt" switch
!      slct yno=(*) xno=1 XB YB range=XXX_RANGE nrl=14 nrh=17
!      +    type=XXX_LGTYPE SYMBOL
!      axis type=y,0 label=t lb.f="%g" TEXT4 tc.majsp=2
!      +    type=y,1 loc=upper               tc.majsp=2
!      +    XA_0 XA_1 YA2
!      text type=2 txt="NFTRGP BV [V]"
!      view_4/6
! (c)shik : core-08
!.plot 
!      attr back moment
!      data name="XXX_PATH/csp7l-inch.XXX_FILE.plt" switch
!      slct yno=(*) xno=1 range=XXX_RANGE nrl=14 nrh=17
!      +    type=XXX_LGTYPE SYMBOL
! (c)shik : core-09
!.plot 
!      attr moment 
!      data name="XXX_PATH/csp7l-inch.XXX_FILE.plt" switch
!      slct yno=(*) xno=1 XB YB range=XXX_RANGE nrl=18 nrh=21
!      +    type=XXX_LGTYPE SYMBOL
!      axis type=y,0 label=t lb.f="%g" TEXT4 tc.majsp=2
!      +    type=y,1 loc=upper               tc.majsp=2
!      +    XA_0 XA_1 YA2
!      text type=2 txt="NFTRM1 BV [V]"
!      text type=1 txt="Ldrawn [um]"
!      view_5/6
! (c)shik : core-10
!.plot 
!      attr back moment
!      data name="XXX_PATH/csp7l-inch.XXX_FILE.plt" switch
!      slct yno=(*) xno=1 range=XXX_RANGE  nrl=18 nrh=21
!      +    type=XXX_LGTYPE SYMBOL
! (c)shik : core-11
! (c)shik : core-12
! (c)shik : core-13
%gEnd_
