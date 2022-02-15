"""
y, psutil - network.py, 2018.8.7
http://psutil.readthedocs.io/en/latest/#
https://www.programcreek.com/python/example/53875/psutil.net_io_counters

DOS
---
netstat -bnpo TCP

"""

import psutil
import time

result = psutil.net_connections(kind='tcp')
print(type(result), type(result[0]))
print(result[0])

pid = None  # 9396
if pid:
    p = psutil.Process(pid=pid)
    print(p.name())
    print(p.connections())
    for c in p.connections():
        print(c.status, c.laddr, c.raddr)


def get_network_io_speeds():
    """
    y,  2018.8.7

    Return
    ------
    upload and download speeds in Mbps

    Reference
    ---------
    http://psutil.readthedocs.io/en/latest/#
    https://www.programcreek.com/python/example/53875/psutil.net_io_counters

    """

    count0 = psutil.net_io_counters(pernic=True)
    time.sleep(1)
    count1 = psutil.net_io_counters(pernic=True)
    uploads = {}
    downloads = {}
    for key in count0.keys():
        uploads[key] = count1[key].bytes_recv - count0[key].bytes_recv
        downloads[key] = count1[key].bytes_sent - count0[key].bytes_sent
    upload_mpbs, download_mbps = sum(uploads.values())/1e6, sum(downloads.values())/1e6

    return upload_mpbs, download_mbps

upload_mps, download_mps = get_network_io_speeds()

print('upload: {} Mbps'.format(upload_mps))
print('download: {} Mbps'.format(download_mps))
