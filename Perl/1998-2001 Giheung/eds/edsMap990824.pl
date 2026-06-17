################################################################################
# (c)shik,990624-0628+0708+0824
################################################################################

#34dies
@kb25edge=("30,30","31,30","32,30","33,30","34,30","35,30","36,30",
           "29,31","37,31","28,32","38,32","27,33","39,33",
           "26,34","40,34","26,35","40,35","26,36","40,36",
           "26,37","40,37","26,38","40,38","27,39","39,39",
           "28,40","38,40","29,41","37,41",
           "31,42","32,42","33,42","34,42","35,42"
);
#119dies
@kb25inside=(           "30,31","31,31","32,31","33,31","34,31","35,31","36,31",
                "29,32","30,32","31,32","32,32","33,32","34,32","35,32","36,32","37,32",
        "28,33","29,33","30,33","31,33","32,33","33,33","34,33","35,33","36,33","37,33","38,33",
"27,34","28,34","29,34","30,34","31,34","32,34","33,34","34,34","35,34","36,34","37,34","38,34","39,34",
"27,35","28,35","29,35","30,35","31,35","32,35","33,35","34,35","35,35","36,35","37,35","38,35","39,35",
"27,36","28,36","29,36","30,36","31,36","32,36","33,36","34,36","35,36","36,36","37,36","38,36","39,36",
"27,37","28,37","29,37","30,37","31,37","32,37","33,37","34,37","35,37","36,37","37,37","38,37","39,37",
"27,38","28,38","29,38","30,38","31,38","32,38","33,38","34,38","35,38","36,38","37,38","38,38","39,38",
        "28,39","29,39","30,39","31,39","32,39","33,39","34,39","35,39","36,39","37,39","38,39",
                "29,40","30,40","31,40","32,40","33,40","34,40","35,40","36,40","37,40",
                        "30,41","31,41","32,41","33,41","34,41","35,41","36,41"
);
#5dies
@kb25edgeFZ=("31,42","32,42","33,42","34,42","35,42"
);

$file="PMsrData.txt";
$CorrelationBase="lot"; # "lot" or "wafer"

# @waferBinMap=@kb25inside;
# @waferBinMap=@kb25edge;
  @waferBinMap=@kb25edgeFZ;

################################################################################

### Bin Report ...
@ConsiderableBins=(1,3,4);
sub BRopen {
   local($i);
   for (@bins) {
      $bins[$i]=0;
      $i++;
   }
   $bins=();  
}
sub BRclose {
   &BRopen();
   $ConsiderableBins=();
}
sub BRaddBin {
   local($i)=@_;
   $bins[$i]++;
}
sub BRsummary {
   local($i,$binNo,$binSum,@binTable);
   $binNo=-1;
   $binSum=0; for (@bins) { $binSum+=$_ if $_; }
   @binTable=();
   for (@ConsiderableBins) { push(@binTable,0); }
   for (@bins) {
      $binNo++;
      next if ! $_;
      $i=noInArray($binNo,@ConsiderableBins);
      next if $i < 0;
      $binTable[$i]=sprintf("%2.1f",$_/$binSum*100);
   }
   return join(' ',@binTable);
}
### end of BR.

sub strInArray {
   local($no,@array,$elem);
   my($str,$array)=@_;
   foreach $elem (@$array) {
      return 1 if $str eq $elem;
   }
   return 0;
 #  return grep($elem,@$array);
}

sub noInArray {
   local($no,@array,$elem,$i);
   my($no,@array)=@_;
   foreach $elem (@array) {
      return $i if $no == $elem;
      $i++;
   }
   return -1;
}

sub doubleEx {
   local($str)=@_;
   if (! $str) { return "#"; }
   $str=~ y/A-Z/a-z/;
   $_=$str;
   s/ma/e-3/g if /ma/;
   s/ua/e-6/g if /ua/;
   return $_;
}

sub sqzToYYMMDD {
   local($_)=@_;
   $_ =~ y/0-9//cd;
   $_=substr($_,2,6) if length($_) == 8;
   return $_;
}

sub sqzSpaceOfFile {
   local($file)=@_;
   local($fileNew)=join('',$file,".sqz");
   open(IN,"< $file");
   open(OUT,"> $fileNew");
   select(OUT);
   while (<IN>) {
      $_ =~ y/ / /s;
      print;
   }
   close(IN);
   close(OUT);
   select(STDOUT);
   return $fileNew;
}

################################################################################

open (IN,"$file");
$lotName="";
$lotWafer="";
$lotDate="";
while (<IN>) {
   @line=split(' ',$_);
   next if ! &strInArray($line[10],\@waferBinMap);
   if (! $lotName) {
      &BRopen();
      $lotName=$line[2];
      $lotWafer=$line[4];
      $lotDate=&sqzToYYMMDD($line[8]);
      next;
   }
   # $value=doubleEx $line[22];
   if ($CorrelationBase eq "wafer") {
      if ($lotName ne $line[2] || $lotWafer ne $line[4]) {            
         printf("%s %s %s %s\n",$lotName,$lotWafer,$lotDate,&BRsummary());
         &BRclose();
         $lotName=$line[2];
         $lotWafer=$line[4];
         $lotDate=&sqzToYYMMDD($line[8]);
         &BRopen();
      };
   } else { # "lot"
      if ($lotName ne $line[2]) {
         printf("%s %s %s\n",$lotName,$lotDate,&BRsummary());
         &BRclose();
         $lotName=$line[2];
         $lotDate=&sqzToYYMMDD($line[8]);
         &BRopen();
      };
   }
   &BRaddBin($line[12]);
}
C:close(IN);
$_=$CorrelationBase;
END: {
   printf("%s %s %s %s\n",$lotName,$lotWafer,$lotDate,&BRsummary()),last END if /wafer/;
   printf("%s %s %s\n",$lotName,$lotDate,&BRsummary()),last END if /lot/;
}
&BRclose();

################################################################################
exit 0;