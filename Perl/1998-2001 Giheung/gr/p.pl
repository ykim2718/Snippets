#!/usr/local/bin/perl
#csp7,(copyLeft)shik,971007-1010

#########1#########2#########3#########4#########5#########6#########7#########8
$name="GQJE02,PMOSFET\@M1";
$path=".\/O";
$file[0]="p01";
$range=90;
$BVrange=100;
#########1#########2#########3#########4#########5#########6#########7#########8
# Do not modify anything below this line ! ######5#########6#########7#########8
#########1#########2#########3#########4#########5#########6#########7#########8

print join(' ',@file),"\n";print "\n";

$perlName="_perL";
system ("/bin/rm -f $perlName*");
sub xtractBlock {
   local($name)=@_;
   open(IN,"$0");
   local($i,$j,$no,@fileList);
   $i=-1;
   $j=1;
   while (<IN>) {
      $i++ if /copyLeft_shik/;
      if ($i == $j) {
         close(OUT);
         $no=sprintf("%02d",$i);
         open(OUT,"> $name-$no");
         push(@fileList,"$name-$no");
         select(OUT);
         $j++;
      }
      if (/\S/ && $i>=1) {
          substr($_,0,1)=" ";
          print;
      }
   }
   close(IN);
   close(OUT);
   select(STDOUT);
   return @fileList
}
sub changeString {
   local(@fileList)=@_;
   local($i,$j,$no);
   for ($i=0;$i<=$#fileList;$i++) {
      $grFile=$fileList[$i];
      if ($grFile eq $fileList[0]) {
         system("sed -e \"s/_NAME_/$name/g\" $grFile > $grFile-00");
         next;
      } elsif ($grFile eq $fileList[$#fileList]) {
         rename($grFile,"$grFile-00");
         next;
      }
      $j=1;
      foreach $splitFile (@file) {
         $no=sprintf("%02d",$j);
         open(OUT,"> $grFile-$no");
         select(OUT);
         open(IN,"< $grFile");
         while (<IN>) {
            s/_FILE_/$splitFile/g;
            s/_PATH_/$path/g;
            s/_RANGE_/$range/g;
            s/_BVRANGE_/$BVrange/g;
            s/_SYMBOL_/$j/g;
            print;
         }
         close(IN);
         close(OUT);
         $j++;
         if ($j == 2) {
            $i++;
            $grFile=$fileList[$i];
         }
      }
   }
   select(STDOUT);
}
sub createGRscript {
   local($script)="GRscript";
   system ("cat $perlName-[0-9][0-9]-[0-9][0-9] > $script");
   system ("/bin/rm -f $perlName-*");
   return $script;
}
sub xGR {
   local ($script)=@_;
   print "gr ....\n";
   system("grxSUN $script -geometry 600x800+0+0 -s");
   rename("$script.ps","$0.ps");print "\"$0.ps\" written ...\n";
   system("csplit -s -f $script- $script.log /\"--C---N---V---T--\"/");
   system("csplit -s -f $script- $script-01  /\"--G---O---U---T--\"/");
   rename("$script-00","$0.dat");print "\"$0.dat\" written ...\n";
   system ("/bin/rm -f $script-*")
}

@fileList=xtractBlock "$perlName";
changeString @fileList;
xGR createGRscript;
exit 0;

#! copyLeft_shik 01
#%gBeg_
# _defn "XA_0" "type=x,0 label=t lb.f="%1.1f" tc.majsp=0.5 tc.minsp=0.1 TEXT4"
# _defn "XA_1" "type=x,1 loc=upper tc.majsp=0.5 tc.minsp=0.1"
# _defn "view_1/6" "view x1=0.20 x2=0.45 y1=0.65 y2=0.90"
# _defn "view_2/6" "view x1=0.55 x2=0.80 y1=0.65 y2=0.90"
# _defn "view_3/6" "view x1=0.20 x2=0.45 y1=0.35 y2=0.60"
# _defn "view_4/6" "view x1=0.55 x2=0.80 y1=0.35 y2=0.60"
# _defn "view_5/6" "view x1=0.20 x2=0.45 y1=0.05 y2=0.30"
# _defn "view_6/6" "view x1=0.55 x2=0.80 y1=0.05 y2=0.30"
# _defn "view_1/4" "view x1=0.15 x2=0.45 y1=0.55 y2=0.90"
# _defn "view_2/4" "view x1=0.55 x2=0.85 y1=0.55 y2=0.90"
# _defn "view_3/4" "view x1=0.15 x2=0.45 y1=0.05 y2=0.40"
# _defn "view_4/4" "view x1=0.55 x2=0.85 y1=0.05 y2=0.40"
# _defn "view_1/2" "view x1=0.10 x2=0.45 y1=0.25 y2=0.65"
# _defn "view_2/2" "view x1=0.55 x2=0.90 y1=0.25 y2=0.65"
# _defn "LOGA"     "lb.f="%1.0f" lb.p="z=log10(z)""
# _defn "TEXT4"    "t.size=4 t.align="22""
# _defn "LGTEXT"   "t.size=4"
# _defn "FILL"     "symb.size=1 symb.stipple=10 symb.polyarc=0 symb.color=red"
# _defn "XB"       "xlb=0.0 xub=1.0"
# _defn "YA2"      "type=y,2 loc=any x=0.35 tick=n"
# .glob
#       gtxt txt="_NAME_" t.width=10 t.height=20
#       gout ps portrait
# _defn "NRLH_VT"  "nrl=01 nrh=05"
# _defn "NRLH_SW"  "nrl=06 nrh=10"
# _defn "NRLH_ID"  "nrl=11 nrh=15"
# _defn "NRLH_IO"  "nrl=16 nrh=20"
# _defn "NRLH_BV10nA" "nrl=21 nrh=25"
# _defn "NRLH_BV1uA"  "nrl=26 nrh=30"
#
#! copyLeft_shik 02
# .plot
#       attr moment ylin
#       data name="_PATH_/csp7l-ptr._FILE_.plt" switch
#       slct yno=(*) xno=1 XB ylb=0.2 yub=1.0 range=_RANGE_ NRLH_VT
#       +    type=_SYMBOL_ legn.size=1 legn.txt="_FILE_" LGTEXT FILL
#       +    x=2.5
#       ufun seqn=0 fn=6 pgm="z=abs(z)"
#       axis type=y,0 label=t lb.f="%1.1f" TEXT4 tc.majsp=0.2
#       +    type=y,1 loc=upper                 tc.majsp=0.2
#       +    XA_0 XA_1 YA2
#       text type=2 txt="Vth [V]"
#       text type=5 txt="_RANGE_%" t.size=1
#       view_1/6
#
#! copyLeft_shik 03
# .plot
#       attr back moment
#       data name="_PATH_/csp7l-ptr._FILE_.plt" switch
#       slct yno=(*) xno=1 range=_RANGE_ NRLH_VT
#       +    type=_SYMBOL_ legn.size=1 legn.txt="_FILE_" LGTEXT FILL
#       ufun seqn=0 fn=6 pgm="z=abs(z)"
#
#! copyLeft_shik 04
# .plot
#       attr omtx moment ylin
#       data name="_PATH_/csp7l-ptr._FILE_.plt"
#       slct yno=(*) xno=1 XB ylb=70 yub=120 range=_RANGE_ NRLH_SW
#       +    type=_SYMBOL_ legn.size=1 FILL
#       axis type=y,0 label=t lb.f="%g" TEXT4 tc.majsp=10
#       +    type=y,1 loc=upper               tc.majsp=10
#       +    XA_0 XA_1 YA2
#       text type=2 txt="Swing [mV/dec]"
#       view_2/6
#
#! copyLeft_shik 05
# .plot
#       attr back omtx moment
#       data name="_PATH_/csp7l-ptr._FILE_.plt"
#       slct yno=(*) xno=1 range=_RANGE_ NRLH_SW
#       +    type=_SYMBOL_ legn.size=1 FILL
#
#! copyLeft_shik 06
# .plot
#       attr omtx moment ylin
#       data name="_PATH_/csp7l-ptr._FILE_.plt"
#       slct yno=(*) xno=1 XB ylb=000 yub=400 range=_RANGE_ NRLH_ID
#       +    type=_SYMBOL_ legn.size=1 FILL
#       ufun seqn=0 fn=6 pgm="z=abs(z)" ncl=2 nch=100
#       axis type=y,0 label=t lb.f="%g" TEXT4
#       +    type=y,1 loc=upper
#       +    XA_0 XA_1 YA2
#       text type=2 txt="Ids3.3 [uA/um]"
#       view_3/6
#
#! copyLeft_shik 07
# .plot
#       attr back omtx moment
#       data name="_PATH_/csp7l-ptr._FILE_.plt"
#       slct yno=(*) xno=1 range=_RANGE_ NRLH_ID
#       +    type=_SYMBOL_ legn.size=1 FILL
#       ufun seqn=0 fn=6 pgm="z=abs(z)" ncl=2 nch=100
#
#! copyLeft_shik 08
# .plot
#       attr omtx moment ylog
#       data name="_PATH_/csp7l-ptr._FILE_.plt"
#       slct yno=(*) xno=1 XB ylb=1e-13 yub=1e-6 range=_RANGE_ NRLH_IO
#       +    type=_SYMBOL_ legn.size=1 FILL
#       ufun seqn=0 fn=6 pgm="z=abs(z)" ncl=2 nch=100
#       axis type=y,0 label=t lb.f="%g" TEXT4 LOGA
#       +    type=y,1 loc=upper
#       +    XA_0 XA_1 YA2
#       text type=2 txt="Ids0 [A/um]"
#       view_4/6
#
#! copyLeft_shik 09
# .plot
#       attr back omtx moment
#       data name="_PATH_/csp7l-ptr._FILE_.plt"
#       slct yno=(*) xno=1 range=_RANGE_ NRLH_IO
#       +    type=_SYMBOL_ legn.size=1 FILL
#       ufun seqn=0 fn=6 pgm="z=abs(z)" ncl=2 nch=100
#
#! copyLeft_shik 10
# .plot
#       attr omtx moment ylin
#       data name="_PATH_/csp7l-ptr._FILE_.plt"
#       slct yno=(*) xno=1 XB ylb=0 yub=12 range=_BVRANGE_ NRLH_BV10nA
#       +    type=_SYMBOL_ legn.size=1 FILL
#       ufun seqn=0 fn=6 pgm="z=abs(z)"
#       axis type=y,0 label=t lb.f="%g" TEXT4 tc.majsp=2 tc.minsp=1
#       +    type=y,1 loc=upper               tc.majsp=2 tc.minsp=1
#       +    XA_0 XA_1 YA2
#       text type=1 txt="Ldrawn [um]"
#       +    type=2 txt="BVdss [V,@10nA]"
#       view_5/6
#
#! copyLeft_shik 11
# .plot
#       attr back omtx moment
#       data name="_PATH_/csp7l-ptr._FILE_.plt"
#       slct yno=(*) xno=1 range=_BVRANGE_ NRLH_BV10nA
#       +    type=_SYMBOL_ legn.size=1 FILL
#       ufun seqn=0 fn=6 pgm="z=abs(z)"
#
#! copyLeft_shik 12
# .plot
#       attr omtx moment ylin
#       data name="_PATH_/csp7l-ptr._FILE_.plt"
#       slct yno=(*) xno=1 XB ylb=0 yub=12 range=_BVRANGE_ NRLH_BV1uA
#       +    type=XXX_LGTYPE legn.size=1 FILL
#       ufun seqn=0 fn=6 pgm="z=abs(z)"
#       axis type=y,0 label=t lb.f="%g" TEXT4 tc.majsp=2 tc.minsp=1
#       +    type=y,1 loc=upper               tc.majsp=2 tc.minsp=1
#       +    XA_0 XA_1 YA2
#       text type=1 txt="Ldrawn [um]"
#       +    type=2 txt="BVdss [V,@1uA]"
#       view_6/6
#! copyLeft_shik 13
# .plot
#       attr back omtx moment
#       data name="_PATH_/csp7l-ptr._FILE_.plt"
#       slct yno=(*) xno=1 range=_BVRANGE_ NRLH_BV1uA
#       +    type=XXX_LGTYPE legn.size=1 FILL
#       ufun seqn=0 fn=6 pgm="z=abs(z)"
#
#! copyLeft_shik 14
#%gEnd_
