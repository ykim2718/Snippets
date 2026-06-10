import sys
import time

j = 0
while j < 60:
    print(__name__, f"[child] child ... {j=}")
    time.sleep(1)
    j += 1
sys.exit('exit message from child to the parent')