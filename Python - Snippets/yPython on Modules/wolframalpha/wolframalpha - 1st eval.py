"""
y, wolframalpha - 1st eval.py, 2018.2.6
https://pypi.python.org/pypi/wolframalpha
"""

import wolframalpha

client = wolframalpha.Client('PQ92VG-PPL8KV98VE')  # ykimwolfram
# res = client.query('temperature in Washington, DC on October 3, 2012')
# res = client.query('temperature in Seoul on Feb 8, 2018')
# res = client.query('temperature in Seoul from Feb 1 to Feb 7, 2018')
res = client.query('price earnings ratio of NASDAQ:AMD')
print(next(res.results).text)

"""
for pod in res.pods:
    for sub in pod.subpods:
        print(sub.text)
"""
