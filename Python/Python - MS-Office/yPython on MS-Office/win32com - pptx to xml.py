"""
y, Python win32com - pptx to xml.py, 2017.5.11, 5.15

"""

import win32com.client
import os


def convert_pptx_to_xml():

    folder = 'd:\Wolf\Homo academicus\yStudy on code - Python\Python - Y\yEvalOfficeControl'
    file_name = 'sample1.pptx'
    pptx_file = os.path.join(folder, file_name)
    xml_file = os.path.join(folder, file_name.replace('.pptx', '.xml'))

    ppt = win32com.client.Dispatch('PowerPoint.Application')
    ppt.Activate()
    presentation = ppt.Presentations.Open(pptx_file, False, False, False)
    presentation.SaveAs(xml_file)
    presentation.Close()


if __name__ == '__main__':

    convert_pptx_to_xml()


