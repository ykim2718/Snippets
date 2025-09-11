"""
y, 2025.9.11
dataclass - key-aware queue.py
copilot
"""

import queue
from dataclasses import dataclass


@dataclass
class KeyAwareNode:
    id: int
    key: str
    value: str


class KeyAwareQueue:
    def __init__(self):
        self.q = queue.Queue()
        self.last_key = None

    def add(self, obj: KeyAwareNode):
        if self.last_key is not None and obj.key != self.last_key:
            self.flush()
        self.q.put(obj)
        self.last_key = obj.key

    def flush(self):
        items = list(self.q.queue)
        if items:
            first = items[0]
            last = items[-1]
            print(f"Flushing queue for key change:")
            print(f"  First: id={first.id}, key={first.key}, value={first.value}")
            print(f"  Last:  id={last.id}, key={last.key}, value={last.value}")
            print(f"  Total items flushed: {len(items)}")
            with self.q.mutex:
                self.q.queue.clear()
                self.q.all_tasks_done.notify_all()
                self.q.unfinished_tasks = 0

    def finalize(self):
        if not self.q.empty():
            self.flush()


if __name__ == "__main__":
    stream = [
        KeyAwareNode(1, "2023-09-10", "A"),
        KeyAwareNode(2, "2023-09-10", "B"),
        KeyAwareNode(3, "2023-09-11", "C"),
        KeyAwareNode(4, "2023-09-11", "D"),
        KeyAwareNode(5, "2023-09-12", "E"),
    ]

    processor = KeyAwareQueue()
    for node in stream:
        processor.add(node)
    processor.finalize()
