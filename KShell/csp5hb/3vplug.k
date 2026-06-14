#!/bin/ksh
#951124,(c)shik,csp5hb3v,NMOST
#960309,961104

#########1#########2#########3#########4#########5#########6#########7#########8
name="dbha-02,PLUG-NMOSFET,M1,3V"
path=".\/O"
file[0]="n1"
file[1]="n3"
file[2]="n4"
range=100
BVrange=100
lgType=1
#########1#########2#########3#########4#########5#########6#########7#########8
# Do not modify anything below this line ! ######5#########6#########7#########8
#########1#########2#########3#########4#########5#########6#########7#########8

tmpFile="/tmp/$0"
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
    -e "s/XXX_RANGE/$range/g" -e "s/XXX_BVRANGE/$BVrange/g" \
    -e "s/XXX_PATH/$path/g"  $tmpFile-Gr > $tmpFile-Gr.p
\rm -f $tmpFile-Gr $tmpFile-[0-9][0-9]*
grx $tmpFile-Gr.p -geometry 600x800+0+0 -s
########## 961104(c)shik
\mv -f $tmpFile-Gr.p.psf $0.psf;echo "\"$0.log\" written ..."
csplit -s -f $tmpFile-core- $tmpFile-Gr.p.log /"--C---N---V---T--"/
csplit -s -f $tmpFile-core- $tmpFile-core-01 /"--G---O---U---T--"/
cat $tmpFile-core-00 > $0.dat;echo "\"$0.dat\" written ..."
##
\rm -f $tmpFile-*
exit

#########1#########2#########3#########4#########5#########6#########7#########8

! (c)shik : core-00
%gBeg_
 _defn "XA_0" "type=x,0 label=t lb.f="%1.1f" tc.majsp=0.5 tc.minsp=0.1 TEXT3"
 _defn "XA_1" "type=x,1 axis=upper tc.majsp=0.5 tc.minsp=0.1"
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
 _defn "LOGA"     "lb.f="%1.0f" lb.p="z=log10(z)""
 _defn "TEXT3"    "t.size=3 t.align="22""
 _defn "LGTEXT"   "t.size=3"
 _defn "FILL"     "symb.size=1 symb.stipple=10 symb.polyarc=0 symb.color=yellow"
 _defn "XB"       "xlb=0.0 xub=2.0"
 _defn "YA2"      "type=y,2 axis=any x=0.8 tick=n"
 _defn "DEVICE"   "plug-tr"
 _defn "WIDTH"    "100"
 .glob 
       gtxt txt="XXX_NAME,W=WIDTHum" t.width=10 t.height=20
       gout psf portrait
! (c)shik : core-01
 .plot 
       attr moment ylin
       data name="XXX_PATH/DEVICE-wWIDTH-vth.XXX_FILE.plt" switch
       slct yno=(*) xno=1 XB ylb=0.2 yub=1.0 range=XXX_RANGE
       +    lg.type=XXX_LGTYPE lg.size=1 lg.txt="XXX_FILE" LGTEXT FILL
       +    lg.x=5
       ufun seqn=0 fn=6 pgm="z=abs(z)"
       axis type=y,0 label=t lb.f="%1.1f" TEXT3 tc.majsp=0.2
       +    type=y,1 axis=upper                 tc.majsp=0.2
       +    XA_0 XA_1 YA2
       text type=2 txt="Vth [V]"
!       text type=5 txt="XXX_RANGE%"
       view_1/6
! (c)shik : core-02
 .plot 
       attr back moment
       data name="XXX_PATH/DEVICE-wWIDTH-vth.XXX_FILE.plt" switch
       slct yno=(*) xno=1 range=XXX_RANGE
       +    lg.type=XXX_LGTYPE lg.size=1 lg.txt="XXX_FILE" LGTEXT FILL
       ufun seqn=0 fn=6 pgm="z=abs(z)"
! (c)shik : core-03
 .plot
       attr moment ylin
       data name="XXX_PATH/DEVICE-wWIDTH-swing.XXX_FILE.plt" switch
       slct yno=(*) xno=1 XB ylb=60 yub=100 range=XXX_RANGE
       +    lg.type=XXX_LGTYPE lg.size=1 FILL
       axis type=y,0 label=t lb.f="%g" TEXT3 tc.majsp=10
       +    type=y,1 axis=upper               tc.majsp=10
       +    XA_0 XA_1 YA2
       text type=2 txt="Swing [mV/dec]"
       view_2/6
! (c)shik : core-04
 .plot 
       attr back moment
       data name="XXX_PATH/DEVICE-wWIDTH-swing.XXX_FILE.plt" switch
       slct yno=(*) xno=1 range=XXX_RANGE lg.type=XXX_LGTYPE lg.size=1 FILL
! (c)shik : core-05
 .plot 
       attr moment ylin
       data name="XXX_PATH/DEVICE-wWIDTH-ids33.XXX_FILE.plt" switch
       slct yno=(*) xno=1 XB ylb=200 yub=600 range=XXX_RANGE
       +    lg.type=XXX_LGTYPE lg.size=1 FILL
       ufun seqn=0 fn=6 pgm="z=abs(z)*1e6/WIDTH" ncl=2 nch=100
       axis type=y,0 label=t lb.f="%g" TEXT3
       +    type=y,1 axis=upper
       +    XA_0 XA_1 YA2
       text type=2 txt="Ids3.3 [uA/um]"
       view_3/6
! (c)shik : core-06
 .plot 
       attr back moment
       data name="XXX_PATH/DEVICE-wWIDTH-ids33.XXX_FILE.plt" switch
       slct yno=(*) xno=1 range=XXX_RANGE lg.type=XXX_LGTYPE lg.size=1 FILL
       ufun seqn=0 fn=6 pgm="z=abs(z)*1e6/WIDTH" ncl=2 nch=100
! (c)shik : core-07
 .plot 
       attr moment ylog
       data name="XXX_PATH/DEVICE-wWIDTH-ids0.XXX_FILE.plt" switch
       slct yno=(*) xno=1 XB ylb=1e-15 yub=1e-6 range=XXX_RANGE
       +    lg.type=XXX_LGTYPE lg.size=1 FILL
       ufun seqn=0 fn=6 pgm="z=abs(z)/WIDTH" ncl=2 nch=100
       axis type=y,0 label=t lb.f="%g" TEXT3 LOGA
       +    type=y,1 axis=upper
       +    XA_0 XA_1 YA2
       text type=2 txt="Ids0 [A/um]"
       view_4/6
! (c)shik : core-08
 .plot 
       attr back moment
       data name="XXX_PATH/DEVICE-wWIDTH-ids0.XXX_FILE.plt" switch
       slct yno=(*) xno=1 range=XXX_RANGE lg.type=XXX_LGTYPE lg.size=1 FILL
       ufun seqn=0 fn=6 pgm="z=abs(z)/WIDTH" ncl=2 nch=100
! (c)shik : core-09
 .plot 
       attr moment ylin
       data name="XXX_PATH/DEVICE-wWIDTH-bv10nA.XXX_FILE.plt" switch
       slct yno=(*) xno=1 XB ylb=0 yub=13 range=XXX_BVRANGE
       +    lg.type=XXX_LGTYPE lg.size=1 FILL
       ufun seqn=0 fn=6 pgm="z=abs(z)"
       axis type=y,0 label=t lb.f="%g" TEXT3 tc.majsp=5 tc.minsp=1
       +    type=y,1 axis=upper               tc.majsp=5 tc.minsp=1
       +    XA_0 XA_1 YA2
       text type=1 txt="Ldrawn [um]"
       +    type=2 txt="BVdss [V,@10nA]"
       view_5/6
! (c)shik : core-10
 .plot 
       attr back moment
       data name="XXX_PATH/DEVICE-wWIDTH-bv10nA.XXX_FILE.plt" switch
       slct yno=(*) xno=1 range=XXX_BVRANGE lg.type=XXX_LGTYPE lg.size=1 FILL
       ufun seqn=0 fn=6 pgm="z=abs(z)"
! (c)shik : core-11
 .plot
       attr moment ylog
       data name="XXX_PATH/DEVICE-wWIDTH-isub33.XXX_FILE.plt" switch
       slct yno=(*) xno=1 XB ylb=1e-9 yub=1e-5 range=XXX_RANGE
       +    lg.type=XXX_LGTYPE lg.size=1 FILL
       ufun seqn=0 fn=6 pgm="z=abs(z)/WIDTH" ncl=2 nch=100
       axis type=y,0 label=t lb.f="%g" TEXT3 LOGA
       +    type=y,1 axis=upper
       +    XA_0 XA_1 YA2
       text type=1 txt="Ldrawn [um]"
       +    type=2 txt="Isub3.3 [A/um]"
       view_6/6
! (c)shik : core-12
 .plot
       attr back moment
       data name="XXX_PATH/DEVICE-wWIDTH-isub33.XXX_FILE.plt" switch
       slct yno=(*) xno=1 range=XXX_RANGE lg.type=XXX_LGTYPE lg.size=1 FILL
       ufun seqn=0 fn=6 pgm="z=abs(z)/WIDTH" ncl=2 nch=100
! (c)shik : core-13
%gEnd_
