#!/user/bin/perl
#Iwai Laboratory,YKim,43351116

&dodir('.');

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
          print "$dir/$_\n";
      }
   } else {
      $subcount=$nlink-2;
      for (@filenames) {
          next if $_ eq '.';
          next if $_ eq '..';
          $name="$dir/$_\n";
          print $name,"\n";
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
