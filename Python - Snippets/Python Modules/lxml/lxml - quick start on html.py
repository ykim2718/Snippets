"""
y, lxml - quick start on html.py, 2019.1.11
Need
----
pip install lxml
pip install cssselect
"""

import lxml.html

tree = lxml.html.fromstring('''<!DOCTYPE html>
<html>
<head>
    <title>lxml tutorials</title>
</head>
<body>
    <table id='table#1' width: "fit-content", height: "fit-content">
    </table>
</body>
<div>
    <div class="cc cv" a=b><i>Hello</i> World!!!</div>
</div>
</html>''')

print(tree.find('head').find('title').text)
print(tree.find('head/title').text)
print(tree.find('body/table').attrib)
print([x for x in tree.iter('div')][1].attrib)
print(tree.xpath("//div[@class='cc cv']")[0].attrib)
print(tree.xpath("//div[contains(@class, 'cv')]")[0].attrib)
print(tree.xpath("//div[contains(@class, 'cv')]")[0].get('a'))

selectors = tree.cssselect('.cc')
print(len(selectors))  # 1 (iterators)
elements = selectors[0].cssselect('i')[0]  # <i>Hello</i>
print(elements.text_content())  # Hello
print(selectors[0].text_content())  # Hello World!!!
print(selectors[0].attrib)  # {'class': 'cc cv'}
print(selectors[0].get('class'))  # 'cc cv'

