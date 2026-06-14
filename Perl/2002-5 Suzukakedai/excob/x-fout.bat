del m40.o m20.o 000.o 020.o 040.o 080.o 120.o iv.out
perl excob.pl -x1 -y2 -b2 -o m40.o IVM40.DAT
perl excob.pl -x1 -y2 -b2 -o m20.o IVM20.DAT
perl excob.pl -x1 -y2 -b2 -o 000.o IVP00.DAT
perl excob.pl -x1 -y2 -b2 -o 020.o IVP20.DAT
perl excob.pl -x1 -y2 -b2 -o 040.o IVP40.DAT
perl excob.pl -x1 -y2 -b2 -o 080.o IVP80.DAT
perl excob.pl -x1 -y2 -b2 -o 120.o IV120.DAT
perl joina-fout.pl -f%1.2e -n#  -o iv.out m40.o m20.o 000.o 020.o 040.o 080.o 120.o

