"""
y, 2020.6.30, 7.7
ftplib - list files.py
"""

import ftplib
import os

ftp = ftplib.FTP()
ftp.connect(host='10.0.0.51', port=21, timeout=86400)  # 3600*24=86400 (1 day)
ftp.login(os.getenv('FTP_USER', 'user'), os.getenv('FTP_PASSWORD', 'password'))
ftp.dir()
ftp.cwd('test')
print(ftp.nlst())
