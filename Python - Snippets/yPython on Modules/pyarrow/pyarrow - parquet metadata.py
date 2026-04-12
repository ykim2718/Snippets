"""
y, 2026.4.12
pyarrow - parquet metadata.py
"""

import pandas as pd
import pyarrow as pa
import pyarrow.parquet as pq

# 1. 데이터프레임 생성
df = pd.DataFrame({'sensor_01': [1.2, 1.3], 'sensor_02': [10, 11]})

# 2. PyArrow Table로 변환
table = pa.Table.from_pandas(df)

# 3. 사용자 정의 메타데이터 추가
custom_meta = {
    "project": "Semiconductor_VM",
    "author": "yRocket",
    "filter_applied": "BorutaShap_v1",
    "timestamp": "2026-04-12 11:23:45 CDT"
}
# 기존 메타데이터와 병합
merged_meta = {**table.schema.metadata, **{k: v.encode() for k, v in custom_meta.items()}}
table = table.replace_schema_metadata(merged_meta)

# 4. 저장
pq.write_table(table, 'sensors.parquet')

# 5. 읽을 때 메타데이터 확인
loaded_table = pq.read_table('sensors.parquet')
# print(loaded_table.schema.metadata)
print('Parquet File Metadata:', '-' * 17)
metadata = loaded_table.schema.metadata
if metadata:
    for key, value in metadata.items():
        print(f"{key.decode()}: {value.decode()}")
print('Parquet File Data:', '-' * 17)
df = loaded_table.to_pandas()
print(df)
