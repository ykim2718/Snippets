#!/usr/bin/perl
#shik96,2001.0801

exit if $#ARGV != 2;

open(GARBAGE,$ARGV[0]);
$GarbageStep=$ARGV[1];
open(EASDATA,$ARGV[2]);
@Garbage=();
while (<GARBAGE>) {
   s/\n//g;  #or#  $_ =~ s/\n//g;
   @Fields=split(' ');
   next if $Fields[1] ne $GarbageStep;
   $_=shift(@Fields);
   push(@Garbage,$_);
}
@EasData=();
while (<EASDATA>) {
   push(@EasData,$_);
   $nLastIndex++;
}
close(GARBAGE);
close(EASDATA);

for (@Garbage) {
   $Target=$_;
   for ($nIndex=$[;$nIndex<=$#EasData;$nIndex++) {
      $_=$EasData[$nIndex];
      if (/$Target/) {
         $EasData[$nIndex]="";
      }
   }
}

for (@EasData) {
   print;
}

exit 0

