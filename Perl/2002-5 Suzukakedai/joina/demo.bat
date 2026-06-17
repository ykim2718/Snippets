rem 20030227
set out=demo.out
perl joina.pl -f1.2e -n#  a.dat b.dat c.dat > %out%
getdbi %out%
pause

