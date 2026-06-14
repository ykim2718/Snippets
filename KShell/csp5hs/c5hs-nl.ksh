#!/bin/ksh
#24/11/95,(c)shik,CSP5HS,0.4um CMOS Logic Process

#########1#########2#########3#########4#########5#########6#########7#########8
name="D4SU03"
file[0]="n1"
file[1]="n2"
file[2]="n2"
range=100
lgType=1
#########1#########2#########3#########4#########5#########6#########7#########8
# Do not modify anything below this line ! ######5#########6#########7#########8
#########1#########2#########3#########4#########5#########6#########7#########8

function extr_gr_file { # in  -> $1 : k-shell & gr-format-file name
                        # out -> core-Gr
   integer FOUND=0
   \rm -f core-Gr
   while read line
   do
      if [[ $line = "%gBeg_" ]] then
         FOUND=1
      fi
      if (( $FOUND == 1 ))
      then
         echo $line >> core-Gr
      fi
   done < $1
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
function noOfArray { # $1 : array
   integer count=0
   for array in $*
   do
      count=count+1
   done
   echo $count
}

\rm -f core-*
extr_gr_file $0
csplit -s -f core- core-Gr /"! (c)shik"/ {12}
\rm -f core-Gr
typeset -i count="`noOfArray ${file[*]}`"
for indexOfFile in 01 03 05 07 09 11
do
   sed -e "s/XXX_LGTYPE/$lgType/g" core-$indexOfFile > core-99
   \mv core-99 core-$indexOfFile
done
if (( $count != 1 ))
   then
   typeset -i lgType
   typeset -i index=1
   while [[ $index < $count ]]
   do
      for indexOfFile in 02 04 06 08 10 12
      do
         
         sed -e "s/XXX_FILE/${file[$index]}/g" -e "s/XXX_RANGE/$range/g"\
             core-$indexOfFile > core-$indexOfFile$index
         if (( $lgType != 0 ))
            then
            lgType=index+1
            sed -e "s/XXX_LGTYPE/$lgType/g" core-$indexOfFile$index > core-99
            \mv core-99 core-$indexOfFile$index
         else
            sed -e "s/XXX_LGTYPE/0/g" core-$indexOfFile$index > core-99
            \mv core-99 core-$indexOfFile$index
         fi
      done
      index=index+1
   done
fi
\rm -f core-0[2468] core-1[02]
cat core-[0-9][0-9]* > core-Gr
sed -e "s/XXX_NAME/$name/g" -e "s/XXX_FILE/${file[0]}/g" \
    -e "s/XXX_RANGE/$range/g"   core-Gr > core-Gr.p
\rm -f core-Gr core-[0-9][0-9]*
gr core-Gr.p -geometry 600x800+0+0
\mv -f core-Gr.p.log $name.log
echo "\"$name.log\" written ..."
# \rm -f core-*
exit

#########1#########2#########3#########4#########5#########6#########7#########8

! (c)shik : core-00
%gBeg_
 _defn "XA_0" "type=x,0 label=t lbfmt="%1.1f" tcmajsp=0.5 tcminsp=0.1 TEXT3"
 _defn "XA_1" "type=x,1 axis=upper tcmajsp=0.5 tcminsp=0.1"
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
 _defn "LOGA"     "lbfmt="%1.0f" lbpgm="z=log10(z)""
 _defn "TEXT3"    "t.width=3 t.height=6 t.align="22""
 _defn "LGTEXT"   "t.width=3 t.height=6"
 _defn "FILL"     "symb.size=1 symb.stipple=10 symb.polyarc=2 symb.color=yellow"
 _defn "XB"       "xlb=0.0 xub=2"
 _defn "YA2"      "type=y,2 axis=any x=0.4 tick=n"
 _defn "WIDTH"    "25"
 .glob 
       gtxt txt="XXX_NAME,NMOSFET,W=WIDTHum" t.width=10 t.height=20
       gout psf portrait name="XXX_NAME"
! (c)shik : core-01
 .plot 
       attr moment ylin
       data name="XXX_FILE.lch-vth" switch
       slct yno=(*) xno=1 XB ylb=0.2 yub=1.2 range=XXX_RANGE
       +    lg.type=XXX_LGTYPE lg.size=1 lg.txt="XXX_FILE" LGTEXT FILL
       axis type=y,0 label=t lbfmt="%1.1f" TEXT3 tcmajsp=0.2
       +    type=y,1 axis=upper                  tcmajsp=0.2
       +    XA_0 XA_1 YA2
       text type=2 txt="Vth [V]"
       view_1/6
! (c)shik : core-02
 .plot 
       attr back moment
       data name="XXX_FILE.lch-vth" switch
       slct yno=(*) xno=1 range=XXX_RANGE
       +    lg.type=XXX_LGTYPE lg.size=1 lg.txt="XXX_FILE" LGTEXT FILL
! (c)shik : core-03
 .plot
       attr moment ylin
       data name="XXX_FILE.lch-swing" switch
       slct yno=(*) xno=1 XB ylb=60 yub=100 range=XXX_RANGE
       +    lg.type=XXX_LGTYPE lg.size=1 FILL
       axis type=y,0 label=t lbfmt="%g" TEXT3 tcmajsp=10
       +    type=y,1 axis=upper               tcmajsp=10
       +    XA_0 XA_1 YA2
       text type=2 txt="Swing [mV/dec]"
       view_2/6
! (c)shik : core-04
 .plot 
       attr back moment
       data name="XXX_FILE.lch-swing" switch
       slct yno=(*) xno=1 range=XXX_RANGE lg.type=XXX_LGTYPE lg.size=1 FILL
! (c)shik : core-05
 .plot 
       attr moment ylin
       data name="XXX_FILE.lch-ids5" switch
       slct yno=(*) xno=1 XB ylb=300 yub=500 range=XXX_RANGE
       +    lg.type=XXX_LGTYPE lg.size=1 FILL
       ufun seqn=0 fnid=6 pgm="z=z*1e6" ncl=2 nch=100
       axis type=y,0 label=t lbfmt="%g" TEXT3
       +    type=y,1 axis=upper
       +    XA_0 XA_1 YA2
       text type=2 txt="Ids5.0 [uA/um]"
       view_3/6
! (c)shik : core-06
 .plot 
       attr back moment
       data name="XXX_FILE.lch-ids5" switch
       slct yno=(*) xno=1 range=XXX_RANGE lg.type=XXX_LGTYPE lg.size=1 FILL
       ufun seqn=0 fnid=6 pgm="z=z*1e6" ncl=2 nch=100
! (c)shik : core-07
 .plot 
       attr moment ylog
       data name="XXX_FILE.lch-ids0" switch
       slct yno=(*) xno=1 XB ylb=1e-15 yub=1e-12 range=XXX_RANGE
       +    lg.type=XXX_LGTYPE lg.size=1 FILL
       ufun seqn=0 fnid=6 pgm="z=z/WIDTH" ncl=2 nch=100
       axis type=y,0 label=t lbfmt="%g" TEXT3 LOGA
       +    type=y,1 axis=upper
       +    XA_0 XA_1 YA2
       text type=2 txt="Ids0 [A/um]"
       view_4/6
! (c)shik : core-08
 .plot 
       attr back moment
       data name="XXX_FILE.lch-ids0" switch
       slct yno=(*) xno=1 range=XXX_RANGE lg.type=XXX_LGTYPE lg.size=1 FILL
       ufun seqn=0 fnid=6 pgm="z=z/WIDTH" ncl=2 nch=100
! (c)shik : core-09
 .plot 
       attr moment ylin
       data name="XXX_FILE.lch-bvdss" switch
       slct yno=(*) xno=1 XB ylb=0 yub=15 range=XXX_RANGE
       +    lg.type=XXX_LGTYPE lg.size=1 FILL
       axis type=y,0 label=t lbfmt="%g" TEXT3 tcmajsp=5 tcminsp=1
       +    type=y,1 axis=upper               tcmajsp=5 tcminsp=1
       +    XA_0 XA_1 YA2
       text type=1 txt="Ldrawn [um]"
       +    type=2 txt="BVdss [V]"
       view_5/6
! (c)shik : core-10
 .plot 
       attr back moment
       data name="XXX_FILE.lch-bvdss" switch
       slct yno=(*) xno=1 range=XXX_RANGE lg.type=XXX_LGTYPE lg.size=1 FILL
! (c)shik : core-11
 .plot 
       attr moment ylog
       data name="XXX_FILE.lch-isub" switch
       slct yno=(*) xno=1 XB ylb=1e-7 yub=1e-3 range=XXX_RANGE
       +    lg.type=XXX_LGTYPE lg.size=1 FILL
       ufun seqn=0 fnid=6 pgm="z=z/WIDTH" ncl=2 nch=100
       axis type=y,0 label=t lbfmt="%g" TEXT3 LOGA
       +    type=y,1 axis=upper
       +    XA_0 XA_1 YA2
       text type=1 txt="Ldrawn [um]"
       +    type=2 txt="Isub [A/um]"
       view_6/6
! (c)shik : core-12
 .plot 
       attr back moment
       data name="XXX_FILE.lch-isub" switch
       slct yno=(*) xno=1 range=XXX_RANGE lg.type=XXX_LGTYPE lg.size=1 FILL
       ufun seqn=0 fnid=6 pgm="z=z/WIDTH" ncl=2 nch=100
! (c)shik : core-13
%gEnd_
