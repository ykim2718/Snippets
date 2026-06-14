#!/usr/bin/perl
# Tokyo Institue of Technology,Suzukakedai Campus,Iwai Lab.
# Created by Yongshik Kim,4335.12.22-25
#
# Data Manupulation Program to extract X & Y column(s) by a Block you wanted.
#

$sExeName="excob";

require "getopt.pl";
&Getopt('xybo');
$nXColWanted=$opt_x-1; # $opt_x will be 0 if no argument.
$nYColWanted=$opt_y-1;
$nBlockWanted=$opt_b;
$sOutFile=$opt_o?$opt_o:$sExeName.".out"; #43351225
$sOutFile=~s#^\s#./$&#; # See Programming Perl p.165.
open(OUT,">$sOutFile");

goto E if $opt_y==-1 || $opt_b==-1;
goto E if $#ARGV!=0; # want only one file as an argument.

sub bIsDigitChr {
   local($_)=@_;
   return /[0-9]/ ? 1:0;
}
sub bIsSignChr {
   return /[+-]/ ? 1:0;
}
sub bIsDotChr {
   local($_)=@_;
   return /./ ? 1:0;
}
sub bIsNanChr {
   local($_)=@_;
   return /#/ ? 1:0;
}
sub bIsNumStr {
   local($_)=@_;
   $c0=substr($_,0,1);
   $c1=substr($_,1,1);
   $c2=substr($_,2,1);
   return 1 if bIsDigitChr($c0);
   return 1 if bIsNanChr($c0);
   return 1 if bIsDotChr($c0) && bIsDigitChr($c1);
   return 1 if bIsSignChr($c0) && bIsDigitChr($c1);
   return 1 if bIsSignChr($c0) && bIsDotChr($c1) && bIsDigitChr($c1);
   return 0;
}

$nBlockCount=0;
$bInDataBlock=0;
while (<>) {
   @sLine=split(' ');
   $bInBlock=bIsNumStr($sLine[0])?1:0;
   if (bIsNumStr($sLine[0])) {
      $nBlockCount++ if !$bInDataBlock;
      $bInDataBlock=1;
   } else {
      $bInDataBlock=0;
   }
   print OUT $sLine[$nXColWanted]," ",$sLine[$nYColWanted],"\n"
   if $nBlockWanted==$nBlockCount && $bInDataBlock && $nXColWanted!=-1;
   print OUT $sLine[$nYColWanted],"\n"
   if $nBlockWanted==$nBlockCount && $bInDataBlock && $nXColWanted==-1;
}
close(OUT);
exit(0);
E:
print OUT 
"Yongshik Kim(copyLeft),Iwai-Lab. at TIT\n",
" Mail:yskim\@ae.titech.ac.jp\n",
" Name: EXtract COlumn(s) by a Block\n",
" Version: 43351225\n",
" Usage(1): ".$sExeName." -x[1-..] -y[1..] -b[1..] -o<file> <file>\n",
" Usage(2): ".$sExeName." -y[1..] -b[1..] -o<file> <file>\n",
" Example: ".$sExeName." -x1 -y2 -b3 -oOut.dat In.dat\n";
close(OUT);
exit(1);

