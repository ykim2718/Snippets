"""
y, 2024.9.12
re - find text between parentheses.py
copilot
    "\[.*?(key).*?\]"
        .*?: Matches any character (except for line terminators) between zero and unlimited times,
            as few times as possible.
        (key): Captures the target text key.
        .*?: Matches any character (except for line terminators) between zero and unlimited times,
            as few times as possible.
"""

import re

key_word = 'home'
boundary_words = ('\[', '\]')
text = 'head [ one home qxx1223].. ..[another home]tail'
print(f"{text=}")
# pattern = rf"\[.*?({key_word}).*?\]"
pattern = rf"{boundary_words[0]}.*?({key_word}).*?{boundary_words[1]}"
print(f"{pattern=}")


print('search'.ljust(32, '-'))
match = re.search(pattern, text)
print(f"{match=}")
if match:
    print(f"Found: {match.group(1)=}, {match.regs[0]=}, {text[4:25]=}")
else:
    print("Not found")

print('findall'.ljust(32, '-'))
match = re.findall(pattern, text)
print(f"{match=}")

print('finditer'.ljust(32, '-'))
matches = re.finditer(pattern, text)
print(f"{matches=}")
positions = [(match.start(1), match.end(1)) for match in matches]
print(f"{positions}")
