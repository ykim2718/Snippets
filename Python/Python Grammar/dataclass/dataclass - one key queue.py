"""
y, 2025.9.11
dataclass - one key queue.py
copilot
"""

import queue
from dataclasses import dataclass


@dataclass
class OneKeyNode:
    id: int
    key: str
    value: str


class OneKeyQueue:
    def __init__(self):
        self.q = queue.Queue()
        self.last_key = None

    def add(self, obj: OneKeyNode):
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
        OneKeyNode(1, "2023-09-10", "A"),
        OneKeyNode(2, "2023-09-10", "B"),
        OneKeyNode(3, "2023-09-11", "C"),
        OneKeyNode(4, "2023-09-11", "D"),
        OneKeyNode(5, "2023-09-12", "E"),
    ]

    processor = OneKeyQueue()
    for node in stream:
        processor.add(node)
    processor.finalize()
