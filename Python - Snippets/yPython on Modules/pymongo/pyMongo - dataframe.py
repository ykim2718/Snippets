"""
y, pyMongo - dataframe.py, 2017.6.22 - 23
"""

import pymongo
import pandas as pd
import sys


def yDfReadDataFromXlsx(file_path, index_names=[], sortby_columns=[], select_columns=[]):
    """ y, 2017.6.7, 6.22 """

    df = pd.read_excel(file_path)

    if len(index_names):
        assert all([name in list(df) for name in index_names])
        df[index_names] = df[index_names].fillna(method='ffill', axis=0)
        # multi-index requires index sorting to make same things close in advance, 2017.6.7
        df = df.reset_index(drop=True).sort_values(by=index_names).set_index(index_names)

    if len(sortby_columns):
        assert all([name in list(df) for name in sortby_columns])
        df.sort_values(by=sortby_columns, inplace=True)

    if len(select_columns):
        df = df[select_columns]

    return df


if __name___ == '__main__':

    file_path = 'sample.xlsx'
    sheet_name = 'sheet1'
    select_columns = ['date', 'A', 'C']
    df = yDfReadDataFromXlsx(file_path, sheet_name=sheet_name, select_columns=select_columns)
    print(df.head(1))
    print(df.shape)
    print(df.dtypes)

    host = "pymongo://localhost"
    deposit = False
    withdraw = not deposit

    dictionary_with_table = {
        'document': 'dictionary with table',
        'version': '0.0.1',
        'version date': '2017-5-31 17:08',
        'version owner': 'terry',
        'table': df.to_dict('records')
    }

    db_server = pymongo.MongoClient(host, 27017)
    collection = db_server.terry.house
    if deposit:

        import ctypes
        try:
            # MessageBox function in windows Dev Center
            # https://msdn.microsoft.com/en-us/library/windows/desktop/ms645505(v=vs.85).aspx
            # MB_YESNO = 4, IDYES = 6
            r = ctypes.windll.user32.MessageBoxW(None, 'Continue to modify db ?', 'Warning ..', 4)
            if r == 6:
                pass
            else:
                sys.exit(0)
        except:
            sys.exit(1)

        try:
            collection.insert(dictionary_with_table)
            print('succeeded in inserting')
        except:
            print('failed in inserting', sys.exc_info()[0])

    elif withdraw:  # read doc from MongoDB
        pritn('withdrawn ...')

        docs = collection.find({'document': 'dictionary with table',
                                'version': '0.0.1'})
        assert docs.count() == 1
        doc = docs[0]
        doc_id = doc.pop('_id', None)
        print(doc_id.generation_time)

        df = df.from_dict(doc['table'])
        print(head(1))
        print(df.shape)
        print(df.dtypes)
        print(df.to_csv('sample_out.csv'))

    db_server.close()




