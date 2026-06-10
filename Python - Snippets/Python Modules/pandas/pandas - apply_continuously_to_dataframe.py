"""
y, pandas - apply_continuously_to_dataframe.py, 2019.1.9, 1.12 - 13
"""

import pandas as pd


def apply_continuously_to_dataframe(*dec_args, _previous=[None], method='static', **dec_kwargs):
    """
    y, 2019.1.9, 1.12 - 13

    Note
    ----
    . decorator over function to be applied to dataframe
    . The first argument in the function should be pd.DataFrame.
    . The function must return pd.DataFrame.
    . The function can not make in-place operation because the 1st argument is passed dataframe.copy(deep=True)
    . _continue=True let dataframe at the first argument appended to _previous dataframe.

    Usage
    -----
    >> @apply_continuously_to_dataframe(method='static')
    >> def rolling_mean(df, column):
          df['rm'] = df[column].rolling(window=3, center=False).mean()
          return df
    >> a = pd.DataFrame({'A': [0, 1, 2, 3]})
    >> b = pd.DataFrame({'A': [4, 5, 6]})
    >> c = pd.DataFrame({'A': [7, 8]})
    >> for df in [a, b, c]:
          df = rolling_mean(df, 'A', _continuous=True)
          print(df, '-' * 8)
    """

    def _split_args(*args):
        """ y, 2019.1.12 - 13 """

        if method == 'static':
            frame = args[0]
            args = args[1:]
        elif method == 'class':
            self, frame = args[0:2]
            args = args[2:]
        self = None
        assert isinstance(frame, pd.DataFrame)
        return self, frame, args

    def _join_args(self, frame, args):
        """ y, 2019.1.12 - 13 """

        if method == 'static':
            args = (frame, *args)
        elif method == 'class':
            args = (self, frame, *args)
        return args

    def wrap(f):

        assert method in ['static', 'class']

        def wrapped_f(*args, **kwargs):

            self, frame, args = _split_args(*args)
            _continuous = kwargs.pop('_continuous', False)
            if _continuous:
                if _previous[0] is not None:
                    current = frame
                    previous = _previous[0]
                    assert set(previous.columns).issuperset(set(current.columns)),\
                        "Previous columns {} must be superset over the current {}".format(
                            previous.columns, current.columns)
                    frame = pd.concat([previous, current], axis=0, sort=False)
                else:
                    frame = frame.copy(deep=True)

            args = _join_args(self, frame, args)
            result = f(*args, **kwargs)
            assert isinstance(result, pd.DataFrame)
            if 'current' in locals():
                result = result.tail(len(current))
            if _continuous:
                _previous[0] = result
            else:
                _previous[0] = None

            return result

        return wrapped_f

    return wrap


@apply_continuously_to_dataframe()
def rolling_mean(df, column):

    df['rm'] = df[column].rolling(window=3, center=False).mean()
    return df


a = pd.DataFrame({'A': [0, 1, 2, 3]}); a.index.name = 'a'
b = pd.DataFrame({'A': [4, 5, 6]}); b.index.name = 'b'
c = pd.DataFrame({'A': [7, 8]}); c.index.name = 'c'
for df in [a, b, c]:
    df = rolling_mean(df, 'A', _continuous=True)
    print(df, '-' * 8)

print(a)
# print(b)
print(c)



