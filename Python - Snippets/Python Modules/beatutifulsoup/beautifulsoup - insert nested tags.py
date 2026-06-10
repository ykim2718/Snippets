"""
y, 2021.8.6
beautifulsoup - insert nested tags.py
https://stackoverflow.com/questions/53310709/python-html-inserting-sibling-element-containing-nested-tags
"""

from bs4 import BeautifulSoup

html = """
<html>
  <body>
    <div class= first_class>
    <h1 id=Heder1>Header1</h1>
    </div>
  </body>
</html>
"""

insert = """
<button class="accordion"><div class="preface"><i>Text</i></div></button>
"""
insert_content = BeautifulSoup(insert, "lxml")
soup = BeautifulSoup(html, "lxml")

title = soup.find("div")

title.insert_before(insert_content.find("button"))
# title.insert_before(insert_content.strip())  # TypeError: 'NoneType' object is not callable
print(soup.prettify())
