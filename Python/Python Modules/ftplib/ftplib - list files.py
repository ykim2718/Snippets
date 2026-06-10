"""
y, 2020.6.30, 7.7
ftplib - list files.py
"""

import ftplib

ftp = ftplib.FTP()
ftp.connect(host='10.227.253.51', port=21, timeout=86400)  # 3600*24=86400 (1 day)
ftp.login('pasystem', 'pa#system00')
ftp.dir()
ftp.cwd('test')
print(ftp.nlst())
