#!/usr/bin/csh
#ZOO@FOO.com,2001.0127

# mkdir ./Script

foreach file (*.spi+)
  setenv new  `echo $file | cut -c1-11`
  echo "$file -> $new"
  mv -f $file $new
end

