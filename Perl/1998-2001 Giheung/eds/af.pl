#!/usr/local/bin/perl
#file:af.pl
#(c)shik,980714-0716
#

#############################################################################
$filter="kgc033*.w??";
$path=".\/data\/";
$command="mv -f paste.out kgc033.out";
#############################################################################
sub myPaste {
   local (@fileArray)=@_;
   local (@wcl,$i,$l,$line);
   $pasted=".pasteOut";
   `rm -f $pasted; touch $pasted`;
   $line=-1;
   for ($i=0;$i<=$#fileArray;$i++) {
      @wcl=split(' ',`wc -l $fileArray[$i]`);
      $l=shift(@wcl);
      if ($line<0) { $line=$l }
      else {
         if ($line!=$l) {
            print "Error, line numbers are not equal ...";
            print "at <$fileArray[$i]> ..in myPaste()\n\n";
            exit 1;
         }
         $line=$l;
      }
      `paste -d" " $pasted $fileArray[$i] > $pasted.tmp`; 
      `mv -f $pasted.tmp $pasted`;
   }
   `mv -f $pasted paste.out`;
}

@files=`ls $path$filter`;
$line=-1;
foreach $file (@files) {
   $_=$file;
   s/\n/ /g;
   s/ //g;
   @ff=split(/\//);
   $file=$_;
   $f=splice(@ff,$#ff,1);
   print "<$file> ---> <$f>\n";
   system("\rm -f $f.log");
   system("af $file > $f.log");
   push(@fileOut,"$f.log");
}
myPaste @fileOut;
foreach $file (@fileOut) { `rm -f $file`; }
exec($command);
exit 0;

