#!/usr/bin/perls/sol2/perl
#(copyLeft)shik,980406-0408

#########1#########2#########3#########4#########5#########6#########7#########8
# Do not modify anything below this line ! ######5#########6#########7#########8
#########1#########2#########3#########4#########5#########6#########7#########8

@file=@ARGV;
print "\n(copyLeft)shik\n";
$grossDie=0;
$fileTotal=$#file+1;
@MapX=(); # baseNo=0
@MapY=(); # baseNo=0
@MapZ=(); # baseNo=0
@MapV=(); # baseNo=0,value=probability

sub chkFiles {
}

sub printXYZ {
   local($i,$j,$k);
   for ($i=-1;$i<$grossDie;$i++) {
      if ($i<0) {
         printf("  xx   yy ");
         for ($j=0;$j<$fileTotal;$j++) {
            $_=$file[$j];
            /.001/;
            printf("%10s ",$`);
         }
         printf("\n");
         next;
      }
      printf("%+04d %+04d ",$MapX[$i],$MapY[$i]);
      for ($j=0;$j<$fileTotal;$j++) {
         $k=$i+$grossDie*$j;
         printf("%10d ",$MapZ[$k]);
      }
      printf("\n");
   }
}

sub printXYV {
   local($i,$j,$k,$sum);
   for ($i=0;$i<$grossDie;$i++) {
      $k=$fileTotal;
      $sum=0;
      while ($k--) {$sum+=$MapZ[$i+$k*$grossDie];}
      $MapV[$i]=$sum/$fileTotal;
   }
   printf("%4s %4s %-s\n","xx","yy","average");
   for ($i=0;$i<$grossDie;$i++) {
      printf("%+04d %+04d ",$MapX[$i],$MapY[$i]);
      printf("%1.2f\n",$MapV[$i]);
   }
}

sub minInVector {
   local(*vec)=@_;
   local($minValue,$elem);
   $minValue=$vec[0];
   foreach $elem (@vec) {
      $minValue=$elem if $minValue > $elem;
   }
   return $minValue;
}

sub maxInVector {
   local(*vec)=@_;
   local($maxValue,$elem);
   $maxValue=$vec[0];
   foreach $elem (@vec) {
      $maxValue=$elem if $maxValue < $elem;
   }
   return $maxValue;
}

sub byXY {
   local ($xa,$ya)=split(/:/,$a,2);
   local ($xb,$yb)=split(/:/,$b,2);
   return $xa > $xb if $ya==$yb; # be careful in comparsion operator.
   return $ya < $yb;
}

sub printXYV2D {
   local($xmin,$xmax,$xLength,$list,$listNew,$i,$line,$y,$x,$dummy);
   $xmin=&minInVector(*MapX);
   $xmax=&maxInVector(*MapX);
   $xLength=$xmax-$xmin+1;
   @list=();
   for ($i=0;$i<$grossDie;$i++) {
      $list[$i]=sprintf("%+04d:%+04d:%4d",$MapX[$i],$MapY[$i],$MapV[$i]*100);
   }
   @listNew=sort byXY @list;
   $i=0;
   foreach $elem (@listNew) {
      ($MapX[$i],$MapY[$i],$MapV[$i])=split(/:/,$elem,3);
 #    printf("%+04d %+04d %4d\n",$MapX[$i],$MapY[$i],$MapV[$i]);
      $i++;
   }
   $dummy="0";
 # printf "#%s\n",$#listNew+1;
   for ($y=0;$y<$xLength;$y++) { $line[$y]=$dummy; }
   $y=$MapY[0];
   for ($i=0;$i<=$#listNew;$i++) {
      if ($MapY[$i]!=$y) {
         for ($y=0;$y<$xLength;$y++) { printf("%-4s ",$line[$y]); }
         print "\n";
         for ($y=0;$y<$xLength;$y++) { $line[$y]=$dummy; }
         $y=$MapY[$i];
      }
      $x=$MapX[$i]-$xmin;
      $line[$x]=sprintf("%-3d",$MapV[$i]);
   }
   for ($y=0;$y<$xLength;$y++) { printf("%-4s ",$line[$y]); }
   print "\n";
}

sub errExit {
   print "Error,  \"@_\" .. !\n\n";
   exit 1;
}

sub indexMatchingXY {
   local($xNo,$yNo)=@_;
   local($i);
   $i=0;
   while ($i<$grossDie) {
      last if $MapX[$i]==$xNo && $MapY[$i]==$yNo;
   } continue {
      $i++;
   }
   $i=-1 if $i >= $grossDie;
   return $i;
}

sub setGrossDieMap {
   local($fileName)=@_[0];
   local($line,$i);
   open(IN,"$fileName");
   while (<IN>) { last if /SampleTestPlan/; }
   if (! $_) { do errExit("$fileName is abnormal"); }
   @line=split;
   $grossDie=$line[1];
   for ($i=0;$i<$grossDie;$i++) {
      $_=<IN>;
      s/;//g if /;/;
      @line=split;
      $MapX[$i]=$line[1];
      $MapY[$i]=$line[2];
   }
   close(IN);
}

sub setMapZV0 {
   local($colHeight,$colTotal)=$_;
   local($i,$total);
   $total=$colHeight*$colTotal;
   for ($i=0;$i<$total;$i++) {
      $MapZ[$i]=0;
      $MapP[$i]=0;
   }
}

sub setXYDefectData {
   local($fileNo,$x,$y,$data)=@_;
   local($i);
   $i=&indexMatchingXY($x,$y);
   $i+=$grossDie*$fileNo;
   $MapZ[$i]=$data; 
}

&chkFiles();
&setGrossDieMap($file[0]);
&setMapZV0($grossDie,$fileTotal);

open(OUT,"> kla.001");
select(OUT);
for ($i=0;$i<=$#file;$i++) {
   $f=$file[$i];
   open(IN,"< $f");
   while (<IN>) {
      chop;
      @line=split;
      &setXYDefectData($i,$line[4],$line[5],1) if ($#line==12);
   }
   close(IN);
}
&printXYZ;
close(OUT);
select(STDOUT);
print "kla.001 written\n";

open(OUT,"> kla.002");
select(OUT); &printXYV;
close(OUT);
select(STDOUT);
print "kla.002 written\n";
open(OUT,"> kla.003");
select(OUT); &printXYV2D;
close(OUT);
select(STDOUT);
print "kla.003 written\n";

select(STDOUT);
print ".done..\n\n";
exit 0;


