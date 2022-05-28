"""
y, 2022.5.27 - 28
pandas - to_string (2).py
"""

import pandas as pd
import io

data = """
,0,0,1,1,2,2
,code_id,value,code_id,value,code_id,value
0,121800,-8.056872037914697,035760,-0.2350176263219761,058470,1.3452914798206317
1,048260,-5.255681818181824,018670,0.0,006730,2.1953896816685026
2,017390,-3.9106145251396662,033290,0.11862396204034287,267270,3.7168141592920367
3,137400,-3.010752688172047,278650,0.5347593582887722,011200,4.218362282878418
4,348210,-1.8786127167630062,298050,0.5625879043600568,302440,16.55328798185942
5,084370,-0.6396588486140775,140860,0.8320726172466042,,
6,000120,-0.2808988764044895,064760,1.1840157868771684,,
"""
frame = pd.read_csv(io.StringIO(data), header=[0, 1], index_col=0, dtype=str)
frame[('0', 'value')] = frame[('0', 'value')].astype(float)
frame[('1', 'value')] = frame[('1', 'value')].astype(float)
frame[('2', 'value')] = frame[('2', 'value')].astype(float)
print(f"frame.dtypes=\n{frame.dtypes}")
# print(f"frame.columns=\n{frame.columns}")

formatters = {
    ('0', 'value'): lambda x: f"<0>{x:.0f}",
    ('1', 'value'): lambda x: f"<1>{x:.1f}",
    ('2', 'value'): lambda x: f"<2>{x:.2f}",
}
outs = frame.to_string(formatters=formatters)
print("frame_to_string=\n", outs)

"""
frame.dtypes=
0  code_id     object
   value      float64
1  code_id     object
   value      float64
2  code_id     object
   value      float64
dtype: object
frame_to_string=
        0             1               2         
  code_id value code_id   value code_id    value
0  121800 <0>-8  035760 <1>-0.2  058470  <2>1.35
1  048260 <0>-5  018670  <1>0.0  006730  <2>2.20
2  017390 <0>-4  033290  <1>0.1  267270  <2>3.72
3  137400 <0>-3  278650  <1>0.5  011200  <2>4.22
4  348210 <0>-2  298050  <1>0.6  302440 <2>16.55
5  084370 <0>-1  140860  <1>0.8     NaN      NaN
6  000120 <0>-0  064760  <1>1.2     NaN      NaN
"""


print('- ' * 16)
# integer in columns cause abnormal operation, 2022.5.28
column0 = list(map(int, frame.columns.get_level_values(0)))
column1 = frame.columns.get_level_values(1)
frame.columns = pd.MultiIndex.from_arrays([column0, column1], names=('1st', '2nd'))
formatters = {
    (0, 'value'): lambda x: f"<0>{x:.0f}",
    (1, 'value'): lambda x: f"<1>{x:.1f}",
    (2, 'value'): lambda x: f"<2>{x:.2f}",
}
outs = frame.to_string(formatters=formatters)
print("frame_to_string=\n", outs)
"""
frame_to_string=
 1st       0                 1               2         
2nd code_id     value code_id   value code_id    value
0    121800 -8.056872  035760 <1>-0.2  058470  <2>1.35
1    048260 -5.255682  018670  <1>0.0  006730  <2>2.20
2    017390 -3.910615  033290  <1>0.1  267270  <2>3.72
3    137400 -3.010753  278650  <1>0.5  011200  <2>4.22
4    348210 -1.878613  298050  <1>0.6  302440 <2>16.55
5    084370 -0.639659  140860  <1>0.8     NaN      NaN
6    000120 -0.280899  064760  <1>1.2     NaN      NaN
"""
