#!/usr/bin/perl

print "Content-type: text/html\n\n";
print "<html><h1>Hello!</h1></html>\n";


open (MAIL,"|/usr/lib/sendmail");
print MAIL "To: zoo\@foo.com\n";
print MAIL "From: from\@e.mail\n";
print MAIL "Subject: Subject\n\n";
print MAIL "Body\n";
close MAIL;