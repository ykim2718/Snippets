#!/usr/bin/perl
# Tokyo Institue of Technology,Suzukakedai Campus,Iwai Lab.
# Created by Yongshik Kim,4336.01.05-02.16
#

$sExeName="getdbi";

#require "getopt.pl";
#&Getopt('b');
#$nBlockWanted=$opt_b?$opt_b:0;

goto E if $#ARGV==-1; # at least one file needed.

sub MAX { local($a,$b)=@_;return $a>$b?$a:$b; }
sub bIsDigitChr { local($_)=@_;return /[0-9]/ ? 1:0; }
sub bIsSignChr { return /[+-]/ ? 1:0; }
sub bIsDotChr { local($_)=@_;return /./?1:0; }
sub bIsNanChr { local($_)=@_;return /#/ ? 1:0; }
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

$nIndex=$[;
for (@ARGV) {
   if (/\*/ || /\?/) {
      local($sFilter,@aFiles,@aFilesTmp);
      tr/()/<>/; # [20030106] trick to avoid the ( and ) effect in the pattern matching.
      s/\*/(\\S)*/g; # [20030106] * -> (\S)*
      s/\?/(\\S){1,1}/g; # [20030106] ? -> (\S){1,1}
      $sFilter=$_; # [20030106] Can't understand it doesn't work with $_.
      opendir(DIR,'.') || die "Can't open current directory";
      #@aFiles=grep(-T && /^$sFilter$/,readdir(DIR));
      @aFiles=grep(-T,readdir(DIR));
      closedir(DIR);
      @aFilesTmp=();             # [20030106] trick                  
      for (@aFiles) {            # [20030106] trick
      	 tr/()/<>/;              # [20030106] trick
      	 $aFilesTmp[$#aFilesTmp+1]=$_ if /^$sFilter$/; # [20030106] trick
      }                          # [20030106] trick
      @aFiles=();                # [20030106] trick
      for (@aFilesTmp) {         # [20030106] trick
      	 tr/<>/()/;              # [20030106] trick
      	 $aFiles[$#aFiles+1]=$_; # [20030106] trick
      }                          # [20030106] trick
      splice(@ARGV,$nIndex,1,@aFiles);
   }
   $nIndex++;
}

foreach $sFile (@ARGV) {
   $sFile=~s#^\s#./$&#; # See Programming Perl p.165.
   open(IN,"$sFile") || ((print "-_- Can't open stuff: ",$sIn,"\n"),goto E);
   $nBlockCount=$bInDataBlock=0;
   $nRowMax=$nColMax=0;
   $sResult=();
   while (<IN>) {
      @sLine=split(' ');
      $bInBlock=bIsNumStr($sLine[0])?1:0;
      if (bIsNumStr($sLine[0])) {
      	 $nBlockCount++ if !$bInDataBlock;
         $nRowMax++;
         for ($nCount=1;
              bIsNumStr($sLine[$nCount]) && $nCount<=$#sLine;
              $nCount++) {};
         $nColMax=MAX($nColMax,$nCount);
         $bInDataBlock=1;
      } else {
      	 $sResult.=sprintf(" %dx%d",$nRowMax,$nColMax) if $bInDataBlock;
      	 $nRowMax=$nColMax=0;
         $bInDataBlock=0;
      }
   }
   close(IN);
   $sResult.=sprintf(" %dx%d",$nRowMax,$nColMax) if $bInDataBlock && $nRowMax && $nColMax;
   $sResult=~s/^ //; # trim the leading space, which functions like trimleft().
   printf("%s : %d block(s) %s\n", $sFile,$nBlockCount,$sResult);
}

exit(0);
E:
print
"(copyLeft) Yongshik Kim, Iwai-Lab. TIT\n",
" mail: yskim\@ae.titech.ac.jp\n",
" function: GET Data Block Information inside each file.\n",
" version: 43360216\n",
" usage: ".$sExeName." <file> ... <file>\n",
" example: ".$sExeName." in[12].dat\n";
exit(1);

