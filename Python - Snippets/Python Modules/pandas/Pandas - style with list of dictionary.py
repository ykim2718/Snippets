"""
y, Pandas - style with list of dictionary.py, 2017.7.20 - 21

"""

import pandas as pd
import numpy as np


def SetVectorCellStylesPerValues(cell_values, values, attributes):
    """ y, 2017.7.20 """

    assert isinstance(values, (list, pd.Series)) and len(values) >= 1
    assert values == sorted(values)
    assert all([isinstance(c, (int, float)) for c in values])
    assert isinstance(attributes, list)
    assert all([isinstance(a, dict) for a in attributes])
    assert len(values) + 1 == len(attributes)

    # convert dict to css style format
    css_attributes = []
    for j in range(len(attributes)):
        css_attributes.append(';'.join([str(k) + ':' + str(v) for k, v in attributes[j].items()]))

    def find_attribute_of_value_in_values(value):

        if pd.isnull(value):
            return 'background-color: none'
        else:
            for j in range(len(values)):
                if value <= values[j]:
                    return css_attributes[j]
            else:
                return css_attributes[-1]

    cell_attributes = []
    for cell_value in cell_values:
        cell_attribute = find_attribute_of_value_in_values(cell_value)
        cell_attributes.append(cell_attribute)

    return cell_attributes

if __name__ == '__main__':

    import os

    df = pd.DataFrame({'A': [0, 2, np.nan, 4],
                       'B': [2, 3.5, None, 6],
                       'C': [1, 3, 5, 6]})

    values = [3, 5]
    attributes = [
        {'background-color': 'red',
         'font-size': '150%'
         },
        {'background-color': 'yellow'
         },
        {'background-color': 'blue',
         'color': 'white',
         'font-weight': 'bolder'
         },
    ]

    df = df.style.apply(SetVectorCellStylesPerValues, args=(values, attributes), subset=['A', 'B'], axis=0). \
        apply(SetVectorCellStylesPerValues, args=(values, attributes), subset=['C'], axis=0)

    df.to_excel(os.path.splitext(__file__)[0] + '.xlsx', sheet_name='y1', engine='openpyxl', startrow=1, index=False)