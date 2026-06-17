#!/usr/bin/perl
# Tokyo Institue of Technology,Suzukakedai Campus,Iwai Lab.
# Created by Yongshik Kim,4335.12.22-26,43360210
#
# Data Manupulation Program to extract X & Y column(s) by a Block you wanted.
#

$sExeName="excob";
goto E if $#ARGV==-1; # want only one file as an argument

require "getopt.pl";
&Getopt('xyb');
$nXColWanted=$opt_x-1; # $opt_x will be 0 if no argument.
$nYColWanted=$opt_y-1;
$nBlockWanted=$opt_b;

goto E if $opt_y==-1 || $opt_b==-1;

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

sub Doit {
   local($_)=@_;
   @sLine=split(' ');
   $bInBlock=bIsNumStr($sLine[0])?1:0;
   if (bIsNumStr($sLine[0])) {
      $nBlockCount++ if !$bInDataBlock;
      $bInDataBlock=1;
   } else {
      $bInDataBlock=0;
   }
   print $sLine[$nXColWanted]," ",$sLine[$nYColWanted],"\n"
   if $nBlockWanted==$nBlockCount && $bInDataBlock && $nXColWanted!=-1;
   print $sLine[$nYColWanted],"\n"
   if $nBlockWanted==$nBlockCount && $bInDataBlock && $nXColWanted==-1;
}

$nBlockCount=0;
$bInDataBlock=0;

if ($#ARGV==0) { # want only one file as an argument.
   while (<>) { Doit($_); }
} elsif ($#ARGV==-1) { # standard input
   while (<STDIN>) { Doit($_); }
} else {
   goto E;
}



exit(0);
E:
print
"Yongshik Kim(copyLeft),Iwai-Lab. at TIT\n",
"  mail:yskim\@ae.titech.ac.jp\n",
"  name: EXtract COlumn(s) of a Block\n",
"  version: 43360210\n",
"  usage(1): ".$sExeName." -x[1..] -y[1..] -b[1..] [file]\n",
"  usage(2): ".$sExeName." -x[1..] -y[1..] -b[1..] [file]\n",
"  usage(3): ".$sExeName." -x[1..] -y[1..] -b[1..] < [file]\n",
"  usage(4): type [file] | ".$sExeName." -x[1..] -y[1..] -b[1..] \n",
"  example: ".$sExeName." -x1 -y2 -b3 In.dat\n";
exit(1);

