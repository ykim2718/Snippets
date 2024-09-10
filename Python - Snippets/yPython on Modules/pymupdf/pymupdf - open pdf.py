"""
y, 2024.9.9 - 10
pymupdf - open pdf.py
https://pypi.org/project/PyMuPDF/
"""

import pymupdf   # pip install PyMuPDF


def read_pdf(file_path, key_pattern, use_re=False):

    assert isinstance(file_path, (str, pathlib.Path))
    assert isinstance(key_pattern, str)

    doc = pymupdf.open(file_path)
    for page in doc:
        text = page.get_text()
        if use_re:
            if re.search(key_pattern, text):
                return text
        else:
            if key_pattern in text:
                return text
    return ''


def extract_korea_top_15_exports_table(text: str, exports: list = []):
    """
    y,  2024.9.9 - 10
    """

    assert isinstance(text, str) and text, f"invalid {text=}"
    assert isinstance(exports, list)

    if not exports:
        exports = [
            '반도체', '디스플레이', '무선통신', '컴퓨터', '자동차', '자동차부품', '일반기계', '선박',
            '석유제품', '석유화학', '바이오헬스', '가전', '섬유', '철강', '이차전지']
    table_indices = ['구분', '수출액', '증감률', '역대순위']
    table_columns = exports + ['전체']

    pattern = f"【 {month}월 15대 주요 품목별 수출액(억달러) 및 증감률(%) 】"
    pattern = pattern.replace(' ', '\s*').replace('(', '\(').replace(')', '\)')
    m = re.search(pattern, text)
    if m:
        # print(f"{m=}")
        # print(f"{m.regs[0]=}")
        text = text[m.regs[0][0]:]
        a = [t.replace(' ', '') for t in text.split('\n')][1:73]  # table = 8x9 = 72 cells
        text = ','.join(a)
        text = re.sub(r"(\구분.*?\수출액)", lambda m: re.sub(r',', '', m.group(1)), text)
        text = re.sub('구분', '구분,', text)
        text = re.sub('수출액', ',수출액', text)
        text = text.replace('△', '-')
        a = text.split(',')
        # print(f"{a=}")
        f = pd.DataFrame(index=pd.Index(table_indices[1:], name=table_indices[0]), columns=table_columns, dtype=object)
        sorted_table_columns = sorted(f.columns, key=len, reverse=True)
        index = None
        for x in a:
            if x in table_indices:
                index = x
                column_seq = 0
                continue
            if index == '구분':
                columns = []
                while x:
                    for c in sorted_table_columns:
                        if x.startswith(c):
                            columns.append(c)
                            x = x[len(c):]
                            break
                    else:
                        raise AssertionError(f"invalid column: {x[:10]}...")
            else:
                try:
                    column = columns[column_seq]
                except IndexError as e:
                    raise e
                f.loc[index, column] = x
                column_seq += 1
                if not pd.isnull(f).any(axis=None):
                    break
        if not set(f.columns).issuperset(set(korea_top_15_exports)):
            raise AssertionError(f"missing columns: {set(korea_top_15_exports)-set(f.columns)=}")
    return f


if __name__ == '__main__':

    import pathlib
    import re
    import pandas as pd

    korea_top_15_exports =[
        '반도체', '디스플레이', '무선통신', '컴퓨터', '자동차', '자동차부품', '일반기계', '선박',
        '석유제품', '석유화학', '바이오헬스', '가전', '섬유', '철강', '이차전지']
    month = 8
    print(f"{korea_top_15_exports=}")

    if False:
        text = """
        하락(임금·단체 협상, 생산시설 현대화 작업 등) 등 영향으로 감소
【 8월 15대 주요 품목별 수출액(억달러) 및 증감률(%) 】
구 분
반도체디스플레이무선통신컴퓨터
자동차자동차부품일반기계
선박
수출액
118.8
18.2
18.1
14.8
50.7
18.4
38.6
28.4
증감률
+38.8
△4.9
+50.4
+183.2
△4.3
△3.5
△5.9
+80.0
역대순위
1위
-
-
2위
2위
-
-
-
구 분
석유제품석유화학바이오헬스
가전
섬유
철강
이차전지
전 체
수출액
45.3
41.8
12.8
6.2
7.9
28.1
7.1
579
증감률
+1.4
+6.9
+39.0
△4.9
△4.8
△1.7
△4.5
+11.4
역대순위
-
-
1위
-
-
-
3위
1위
□ (지역) 9대 주요 수출시장 중 8개에서 수출 플러스
        """
        f = extract_korea_top_15_exports_table(text)
        print(f"{f=}")
    else:
        file_path = pathlib.Path(__file__).with_name('0901(1일(일)11시엠바고)수출입과, 2024년 8월 수출입동향.pdf')
        if False:
            key_text = f"【 {month}월 15대 주요 품목별 수출액(억달러) 및 증감률(%) 】"
            use_re = False
        else:
            key_text = rf'【 {month}월 15대 주요 품목별 수출액(억달러) 및 증감률(%) 】'
            key_text = key_text.replace(' ', '')
            key_text = '\s*'.join(key_text)
            key_text = key_text.replace('(', '\(').replace(')', '\)')
            use_re = True
        print(f"{key_text=}")
        text = read_pdf(file_path, key_text, use_re=use_re)
        # print(text)
        if text:
            f = extract_korea_top_15_exports_table(text)
            print(f"{f=}")
