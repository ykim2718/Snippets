"""
y, pandas - read_hdft chunk with next.py, 2018.9.28
"""

from pandas import HDFStore, read_hdf

a_file = r'.\xxxxx.h5'

if False:
    hdf = HDFStore(a_file)
    print(hdf.info())
    print(hdf.keys())
    frame_it = read_hdf(hdf, 'data', mode='r', chunksie=1e5)
else:
    frame_it = read_hdf(a_file, 'data', mode='r', chunksiz=1e5)

if False:
    for j, frame in enumerate(frame_it, start=1):
        print(j, frame.size)
else:
    frame_it = iter(frame_it)
    j = 0
    while True:
        frame = next(frame_it, None)
        if frame is None:
            brak
        print(j, frame.size)
        j += 1


