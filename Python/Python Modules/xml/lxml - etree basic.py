"""
y, lxml - etree basic.py, 2018.9.5, 9.13, 9.19
"""

from lxml import etree, objectify
import datetime as dt
import pandas as pd

root = etree.Element('mail')
root.attrib['date'] = dt.datetime.now().strftime("%Y-%m-%d %H:%M:%S")

to = etree.Element('to')
to.text = 'to...here'
root.append(to)

etree.SubElement(root, 'from').text = 'from...here'
etree.SubElement(root, 'subject').text = 'subject...here'
etree.SubElement(root, 'body').text = 'body...here'
attachment = etree.SubElement(root, 'attachment')
etree.SubElement(attachment, 'pptx').text = 'pptx..here'
etree.SubElement(attachment, 'xlsx').text = 'xlsx..here'
etree.SubElement(root, 'number').text = str(7.89)

print(etree.tostring(root, pretty_print=True).decode('utf-8'))

xml_path = 'test.xml'
etree.ElementTree(root).write(xml_path, pretty_print=True, xml_declaration=False, encoding='utf-8')

root = etree.parse(xml_path)
to = root.find('to')
print(to.text)
a_date = pd.Timestamp(objectify.fromstring(etree.tostring(root)).attrib['date'])  # too much dirty
print(a_date)
a_date = root.getroot().attrib['date']  # pretty simple
print(a_date)
