"""
y, tkinter - simple file selection dialog.py

https://stackoverflow.com/questions/9319317/quick-and-easy-file-dialog-in-python
https://stackoverflow.com/questions/7994461/choosing-a-file-in-python3

"""

import tkinter as tk
from tkinter import filedialog

root = tk.Tk()
root.withdraw()

file_path = filedialog.askopenfilename(initialdir="d:\\",
                                       title="choose your data file",
                                       filetypes=(("csv files", "*.csv"), ("all files", "*.*")))

print(file_path)