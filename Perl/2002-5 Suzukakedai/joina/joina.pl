#!/usr/bin/perl
# Tokyo Institue of Technology,Suzukakedai Campus,Iwai Lab.
# Created by Yongshik Kim,4335.12.23-4336.2.11-2.15-2.27
#
# This looks like jsbs.pl except the attching method. Jsbs2.pl sorts columns
# by its first column in a numeric order of the first column of the first
# file. Then, it puts the sorted columns into the side of the first file matrix
# If the first column of the first file matrix does not match the number of
# the first attached column, its number is inserted into the first coumn of
# the first file matrix and the corresponding row is attached. Since the other
# columns of the first file matrix  also does not have an inserted row, 
# a new dummy string (e.g.,#) is inserted as many as it requires.
# So, every joinging process carry out in accordance with the numeric order
# of the each first column.
#

$sExeName="joina";

sub numerically {$a<=>$b;} # See Programming Perl p.183.
sub reverse {$b cmp $a;} # See Programming Perl p.184.
sub MAX { local($a,$b)=@_;return $a>$b?$a:$b; }

require "getopt.pl";
&Getopt('fn');
$sFormat=$opt_f?$opt_f:"%.3e";
$sFormat="%".$sFormat unless $sFormat =~ /^%/;
$sNan=$opt_n?$opt_n:"#";

goto E if $#ARGV==-1; # @aFiles=@ARGV; $nFiles=$#ARGV+1;

$sIn=shift(@ARGV);
%aOut=(); # associative array 

#open(IN,"$sIn") || die "Can't open stuff: $!\n"; 43351224
open(IN,"$sIn") || ((print "-_- Can't open stuff: ",$sin,"\n"),goto E);
while (<IN>) {
   ($sFirst,$sTheOthers)=split(' ',$_,2);
   $sFirst=sprintf($sFormat,$sFirst);
   $sTheOthers=~s/\n//;
   $aOut{$sFirst}.=$sTheOthers;
}
close(IN);

foreach $sIn (@ARGV) {

   #open(IN,"$sIn") || die "Can't open stuff: $!\n"; 43351224
   open(IN,"$sIn") || ((print "-_- Can't open stuff: ",$sIn,"\n"),goto E);
   @aBuffer=<IN>;
   close(IN);

   #{43360106 for remainder not added by this file.
   @aBuf=split(' ',$aBuffer[$[]);
   $nCount=$#aBuf+0; # 1->0 [Y.Kim,20030211]
   goto E if $nCount<=0; # for empty file. <-- Y.Kim,20030215
   $sNans4Remainder="";
   while ($nCount--) {$sNans4Remainder.=$sNan." ";};
   #}

   #{40030227 for adding first by this file.
   $nCount=0;
   foreach $sKey (keys %aOut) {
      @aBuf=split(' ',$aOut{$sKey});
      $nCount=$#aBuf if $#aBuf>$nCount;
   }
  $nCount++;
   $sNans4FirstAdding="";
   while ($nCount--) {$sNans4FirstAdding.=$sNan." ";};
   #}

   %aCheck=%aOut;

   $nCount=$#aBuffer;
   while ($nCount>=0) {
      ($sFirst,$sTheOthers)=split(' ',$aBuffer[$nCount],2);
      $sFirst=sprintf($sFormat,$sFirst);
      $sTheOthers=~s/\n//;
      $bFound=exists($aOut{$sFirst}); # Y.Kim,20030211
      if ($bFound) {
         $aOut{$sFirst}.=" ".$sTheOthers;
      } else {
         $aOut{$sFirst}.=" ".$sNans4FirstAdding.$sTheOthers; #43360106
      }
      $nCount--;
   }
      
   foreach $sKey (keys %aCheck) {
      #20030227) sNan -> sNans4Remainder
      $aOut{$sKey}.=" ".$sNans4Remainder if $aOut{$sKey} eq $aCheck{$sKey};
   }
}

foreach $sKey (sort numerically keys(%aOut)) {
   print $sKey," ",$aOut{$sKey},"\n";
}

exit(0);
E:
print
"(copyLeft)Yongshik Kim, Iwai-Lab. at TIT\n",
" mail: yskim\@ae.titech.ac.jp\n",
" name: JOIN side by side Adaptively by the first column value and order\n",
" version: 43351226-43350227\n",
" usage: ".$sExeName." [-f%.3e] [-n#] -o<file> <file> <file> <file> ...\n",
" example: ".$sExeName." In1.dat In2.dat In3.dat\n",
" caution: A row count is not always determined by that of the first file.\n",
"          since it is adative to a value of the first column.\n";
exit(1);

