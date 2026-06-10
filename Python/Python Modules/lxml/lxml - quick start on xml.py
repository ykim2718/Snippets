"""
y, lxml - quick start on xml.py, 2019.1.11
"""

from lxml import etree

root = etree.XML('''<root>
    <TEXT1 class="myitem">one</TEXT1>
    <TEXT2 class="myitem">two</TEXT2>
    <TEXT3 class="myitem">three</TEXT3>
    <v-TEXT4 class="v-list">four</v-TEXT4>
</root>''')

items = root.xpath("//*[re:test(local-name(), '^TEXT.*')]", namespaces={'re': 'http://exslt.org/regular-expressions'})
for item in items:
    print(item.text, item.attrib)

items = root.xpath("//*[@class='myitem']")
for item in items:
    print(item.text, item.attrib)
