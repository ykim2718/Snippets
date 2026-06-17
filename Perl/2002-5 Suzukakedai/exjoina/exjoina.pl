#!/usr/bin/perl
# Tokyo Institue of Technology,Suzukakedai Campus,Iwai Lab.
# Created by Yongshik Kim. 43360526-0527,0908
# Revised :...

exit if $#ARGV!=0; # only one file needed

$format1st="%1.3e";
# $format1st="%s";
$path="";
@in=@in_b=@in_x=@in_y=();
$out="";

while (<>) {
   s/(^ |\s$| $)//g; #43360527 Ya-hooooooooo
   next if /^!/; # comment
   if (s/^path=//) {
      s/(^"|"$)//g;
      s/(^ | $)//g;
      s/\\$//g;
      $path=$_;
      system("mkdir $path") if ! -d $path;
   }
   if (s/^in=//) {
      /=/; # See Programming Perl, p.112
      push(@in,$');
      ($in_b[$#in],$in_x[$#in],$in_y[$#in])=split(',',$`);
      $in[$#in]=~s/(^ | $)//g;
      $in_b[$#in]=~s/(^ | $)//g;
      $in_x[$#in]=~s/(^ | $)//g;
      $in_y[$#in]=~s/(^ | $)//g;
   }
   if (s/^out=//) {
      s/(^"|"$)//g;
      s/(^ | $)//g;
      $out=$_;
      next if $#in==-1;
      if (!$#in) { # 20090908
         print "excob -b$in_b[0] -x$in_x[0] -y$in_y[0] $in[0] > $path\\.0.o\n";
         system("excob -b$in_b[0] -x$in_x[0] -y$in_y[0] \"$in[0]\" > \"$path\\.0.o\"");
         print "rename $path\\.0.o $path\\$out\n";
         system("move $path\\.0.o $path\\$out");
         @in=@in_b=@in_x=@in_y=();
         next;
      }
      @files=();
      for ($i=0;$i<=$#in;$i++) {
         push(@files,"$path\\.$i.o");
         if (-T $files[$#files]) {
            print "A temporary file (.[0-9][0-9].o) creation is corrupted \n";
            print "due to the existence of $files[$#files]\n";
            exit;
         }
         print "excob -b$in_b[$i] -x$in_x[$i] -y$in_y[$i] $in[$i] > $files[$#files]\n";
         system("excob -b$in_b[$i] -x$in_x[$i] -y$in_y[$i] \"$in[$i]\" > \"$files[$#files]\"");
      }
      $_=join(' ',@files);
      print "joina -f$format1st -n# $_ > $path\\$out\n";
      $cmd="joina -f$format1st -n#";
      foreach $file (@files) { $cmd.=" \"$file\""; }
      $cmd.=" > \"$path\\$out\"";
      system($cmd);
      foreach $file (@files) { system("del \"$file\""); }
      @in=@in_b=@in_x=@in_y=();      
   }
}

print "(c)Y.Kim,20030908";