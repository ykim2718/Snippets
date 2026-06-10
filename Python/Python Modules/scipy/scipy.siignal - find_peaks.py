"""
y, 2026.4.17
scipy.siignal - find_peaks.py
"""

import numpy as np
import matplotlib.pyplot as plt
from scipy.signal import find_peaks
import pathlib

# 1. 데이터 생성 (큰 사인파 + 작은 고주파 신호)
x = np.linspace(0, 10, 500)
large_sine = np.sin(x)
small_signal = 0.1 * np.sin(50 * x)
combined = large_sine + small_signal

# 2. 피크 찾기
# 아무 조건 없이 찾으면 모든 작은 떨림을 다 잡습니다.
peaks_all, _ = find_peaks(combined)

# 돌출도(prominence)를 설정하면 큰 흐름의 피크만 잡을 수 있습니다.
peaks_major, _ = find_peaks(combined, prominence=0.5)

# 3. 시각화
plt.figure(figsize=(10, 4))
plt.plot(x, combined, label='Combined Signal')
plt.plot(x[peaks_all], combined[peaks_all], "x", label='All Peaks (Small & Large)')
plt.plot(x[peaks_major], combined[peaks_major], "ro", label='Major Peaks only')
plt.legend()
plt.savefig(f"{pathlib.Path(__file__).stem}.png", dpi=300, bbox_inches='tight')
plt.show()
