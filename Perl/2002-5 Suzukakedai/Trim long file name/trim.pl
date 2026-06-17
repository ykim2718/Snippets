#!/usr/bin/perl
#Iwai-Laboratory,YKim,43351116-17


$nMaxFileNameLength=64; # should be greater than 4.
$nExtensionLength=3;
$cExtension='.';


&dodir('.');

sub dofile{
   local($file)=@_;
   return if -d $file;
   $length=length($file);
   if ($length>$nMaxFileNameLength) {
      $pos=$length-1-$nExtensionLength;
      $bFound=substr($file,$pos,1) eq $cExtension ? 1:0;
      if ($bFound) {
         $head=substr($file,0,$nMaxFileNameLength-$nExtensionLength-3);
         $tail=substr($file,length($file)-$nExtensionLength);
         $new=join("",$head,"++",$cExtension,$tail);
      } else {
         $head=substr($file,0,$nMaxFileNameLength-2);
         $new=join("",$head,"++");
      }
      print "Rename: $new <<< $file\n";
      rename($file,$new);    
   }
}

sub dodir{
   local($dir,$nlink)=@_;
   local($dev,$ino,$mode,$subcount);
   ($dev,$ino,$mode,$nlink)=stat('.') unless $nlink;
   opendir(DIR,'.') || die "Can't open $dir";
   local(@filenames)=readdir(DIR);
   closedir(DIR);

   if ($nlink==2) {
      for (@filenames) {
          next if $_ eq '.';
          next if $_ eq '..';
#         print "$dir/$_\n";
          dofile($_);
      }
   } else {
      $subcount=$nlink-2;
      for (@filenames) {
          next if $_ eq '.';
          next if $_ eq '..';
          $name="$dir/$_";
#         print $name,"\n";
          dofile($_);
          next if $subcount==0;
          ($dev,$ino,$mode,$nlink)=lstat('.');
          next unless -d;
          chdir $_ || die "Can't cd to $name";
          &dodir($name,$nlink);
          chdir '..';
          --$subcount;
      }
   }
}
