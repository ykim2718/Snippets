#!/usr/bin/perl
# Tokyo Institue of Technology,Suzukakedai Campus,Iwai Lab.
# Data Manupulation for XRD-SPECTROSCOPY Data
#
# Created by Yongshik Kim,2002.7.8-
#

@aArgument=@ARGV;
$nArgument=$#aArgument+1;
exit(1) if $nArgument<=0;
print "![",$nArgument,"]";
foreach $sFile (@aArgument) { print " ",$sFile; }
print "\n";

$fStart=$fStop=$fStep=0;
open(IN,"$aArgument[0]");
while (<IN>) {
   ($dummy1,$dummy2,$dummy3)=split(" ",$_,3);
   $fStart=$dummy3 if /START/;
   $fStop=$dummy3 if /STOP/;
   $fStep=$dummy3 if /STEP/;
   last if $fStart && $fStop && $fStep;
}
close(IN);
goto E if !($fStart && $fStop && $fStep);
$nTotal=($fStop-$fStart)/$fStep+1;

@Data=0;
foreach $sFile (@aArgument) {
   @DataTemp=0;
   pop(DataTemp); # don't know exactly but necessary. 2002.7.8,shik
   open(IN,"$sFile");
   while (<IN>) { last if /\*COUNT /;}
   @dummy=split(" ");
   if ($nTotal!=pop(dummy)) {
      print "\n",$sFile," does not match to the first file,",$aArgument[0];
      goto E;
   }
   while (<IN>) {
      s/,//g;
      @dummy=split(" ");
      push(DataTemp,@dummy);
      last if /END/;
   }
   close(IN);
   pop(DataTemp);
   push(Data,@DataTemp);
}

goto E if $#Data%$nTotal;

for ($nIndex=1;$nIndex<=$nTotal;$nIndex++) {
   printf("%.2f",$fStart+$fStep*($nIndex-1));
   for ($nCount=0;$nCount<$nArgument;$nCount++) {
      print " ",$Data[$nCount*$nTotal+$nIndex];
   }
   print "\n";
}

exit(0);
E:
print "\nSorry, something wrong took place somewhere..",
      "\nPlease Contact with Yongshik Kim (yskim\@ae.titech.ac.jp) ",
      "at Iwai Lab.\n\n";
exit(1);


