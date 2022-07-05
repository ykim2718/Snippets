"""
y, fbprohet - training and test (y).py, 2018.4.13 - 23

https://facebook.github.io/prophet/docs/trend_changepoints.html
https://github.com/facebook/prophet/issues/223
https://stackoverflow.com/questions/11130156/suppress-stdout-stderr-print-from-python-functions
"""

import pandas as pd
import numpy as np
import fbprophet as fbp  # fb = face book
import os
import datetime as dt
import matplotlib.pyplot as plt


# copied to yPyStandard.py, 2018.4.22
# https://github.com/facebook/prophet/issues/223
# https://stackoverflow.com/questions/11130156/suppress-stdout-stderr-print-from-python-functions
class YSuppressStdoutAndStderr(object):
    '''
    A context manager for doing a "deep suppression" of stdout and stderr in
    Python, i.e. will suppress all print, even if the print originates in a
    compiled C/Fortran sub-function.
       This will not suppress raised exceptions, since exceptions are printed
    to stderr just before a script exits, and after the context manager has
    exited (at least, I think that is why it lets exceptions through).

    '''
    def __init__(self):
        # Open a pair of null files
        self.null_fds = [os.open(os.devnull, os.O_RDWR) for x in range(2)]
        # Save the actual stdout (1) and stderr (2) file descriptors.
        self.save_fds = (os.dup(1), os.dup(2))

    def __enter__(self):
        # Assign the null pointers to stdout and stderr.
        os.dup2(self.null_fds[0], 1)
        os.dup2(self.null_fds[1], 2)

    def __exit__(self, *_):
        # Re-assign the real stdout/stderr back to (1) and (2)
        os.dup2(self.save_fds[0], 1)
        os.dup2(self.save_fds[1], 2)
        # Close the null files
        os.close(self.null_fds[0])
        os.close(self.null_fds[1])


# copied to yTime.py, 2018.4.22
def set_axis_legend(ax1, axt=None, loc='upper left', fontsize='small'):
    """
    y,  2016,
        2017.1.6
        2018.4.22
    """

    if axt:  # ax twin
        lines1, labels1 = ax1.get_legend_handles_labels()
        lines2, labels2 = axt.get_legend_handles_labels()
        axt.legend(lines1 + lines2, labels1 + labels2, loc=loc, fontsize=fontsize)
    else:
        ax1.legend(numpoints=1, ncol=1, bbox_to_anchor=(0, 1), loc=loc, fontsize=fontsize)


# copied to yTime.py, 2018.4.22
def timedelta_str(timedelta, decimal_point_format="%05.2f"):
    """ y, 2018.4.22 - 23 """

    if decimal_point_format:
        *hm, sec = str(timedelta).split(':')
        hm = ':'.join(hm)
        sec = decimal_point_format % float(sec)
        return hm + ':' + sec
    else:
        return str(timedelta).split('.', 2)[0]


_ds = 'ds'
_y, _yhat, _yhat_lower, _yhat_upper = 'y', 'yhat', 'yhat_lower', 'yhat_upper'


def expect_ts_trend(frame, training_date='2018-1-1', test_date='2018-1-31',
                    col_y='close', max_training_size=1000):
    """ y, 2018.4.13 - 20

    Note
    ----
    . training_date is the last date of training data.
    . test_date is the last date of test (expectation).

    """

    assert isinstance(frame, pd.DataFrame)
    assert isinstance(frame.index[0], pd.Timestamp)
    assert isinstance(training_date, (str, dt.datetime, dt.date))
    assert isinstance(test_date, (str, dt.datetime, dt.date))
    training_date = pd.Timestamp(training_date)
    test_date = pd.Timestamp(test_date)
    assert training_date < test_date

    training = frame[frame.index <= training_date].copy()
    training = training[-max_training_size:]
    training.index.name = _ds
    training.reset_index(drop=False, inplace=True)
    training[_y] = np.log(training[col_y])

    m = fbp.Prophet(growth='linear')  # changepoint_prior_scale=0.5, changepoints=['2017-01-01'])
    with YSuppressStdoutAndStderr():
        m.fit(training)

    training_ = m.predict(training[_ds].to_frame())
    assert training[_ds].equals(training_[_ds])
    training_.drop(_ds, axis=1, inplace=True)
    assert set(training.columns).isdisjoint(training_.columns)  # confirm nothing is common
    training = pd.concat([training, training_], axis=1)
    del training_

    dates = pd.date_range(start=training_date + dt.timedelta(days=1), end=test_date, freq='B')
    test = m.predict(pd.DataFrame({_ds: dates}))  # expect
    """
    print(forecast.columns)
    ['ds', 'trend', 'trend_lower', 'trend_upper', 'yhat_lower', 'yhat_upper',
           'seasonal', 'seasonal_lower', 'seasonal_upper', 'seasonalities',
           'seasonalities_lower', 'seasonalities_upper', 'weekly', 'weekly_lower',
           'weekly_upper', 'yearly', 'yearly_lower', 'yearly_upper', 'yhat']
    forecast = forecast[[_ds, _yhat, _yhat_lower, _yhat_upper]]
    """
    training.set_index(_ds, inplace=True)
    test.set_index(_ds, inplace=True)

    y_columns = [_yhat, _yhat_lower, _yhat_upper]
    training[[_y] + y_columns] = np.exp(training[[_y] + y_columns])
    test[y_columns] = np.exp(test[y_columns])

    return training, test


def correlate_expectation_to_observation(exp, obs):
    """ y, 2018.4.16 - 4.20 """

    assert isinstance(exp, pd.Series)
    assert isinstance(obs, pd.Series)
    obs = obs.reindex(exp.index)
    assert obs.dropna().size

    return dict(
        pe=exp.corr(obs, method='pearson'),
        ke=exp.corr(obs, method='kendall'),
        sp=exp.corr(obs, method='spearman'),
    )


def compare_expectation_with_observation(exp, obs, exp_ref, obs_ref, obs_sample_size_at_the_end=5):
    """ y, 2018.4.17 - 20 """

    assert isinstance(exp, pd.Series)
    assert isinstance(obs, pd.Series)
    obs = obs.reindex(exp.index)
    assert exp_ref
    assert obs_ref

    obs_end = obs[-obs_sample_size_at_the_end:].mean()
    exp_end = exp[-1]

    dyhat = (exp_end - exp_ref) / exp_ref
    dyhat_y = (exp_end - obs_ref) / obs_ref
    dy = (obs_end - obs_ref) / obs_ref
    eor = dyhat / dy  # expected delta to observed delta ratio

    return eor, dyhat, dyhat_y, dy,


def add_swing_paths_to_scenario(scenario, summary, keep='first', col_eval='dyhat', col_swing_path_prefix='swp'):
    """ y, 2018.4.23 """

    _test_date, _training_date = 'test_date', 'training_date'
    _enter, _exit = 'enter', 'exit'

    assert isinstance(scenario, pd.DataFrame)
    assert scenario.index.is_unique and scenario.index.is_monotonic_increasing
    assert isinstance(summary, pd.DataFrame)
    assert summary.index.name == _test_date
    assert summary.index.is_unique and summary.index.is_monotonic_increasing
    assert _training_date in summary
    assert keep in ['first', 'all'] or isinstance(keep, int)
    assert col_eval in summary  # target
    assert all([not column.startswith(col_swing_path_prefix) for column in summary.columns])

    summary = summary.reset_index(drop=False).copy()
    mask = ((scenario.index[0] <= summary[[_training_date, _test_date]]) &
            (scenario.index[-1] >= summary[[_training_date, _test_date]])).all(axis=1)
    summary = summary[mask]
    summary[_training_date] = pd.to_datetime(summary[_training_date])
    summary[_test_date] = pd.to_datetime(summary[_test_date])

    mask = summary[col_eval] > 0
    enters = summary[_training_date][mask]
    if len(enters) == 0:
        return

    def _next_enter(exit):
        """ y, 2018.4.23 """

        try:
            j = pd.Index(enters).get_loc(exit + dt.timedelta(days=1), method='bfill')
        except KeyError:
            j = len(enters) - 1
        return enters.iloc[j]

    def _next_exit(enter):
        """ y, 2018.4.23 """

        j = pd.Index(summary[_training_date]).get_loc(enter)
        exit = summary[_test_date].iloc[j]
        j = scenario.index.get_loc(exit, method='bfill')
        return scenario.index[j]

    if keep == 'first':
        max_path_count = 1
    elif keep == 'all':
        max_path_count = 99
    else:
        max_path_count = keep

    for j, enter in enumerate(enters, start=1):
        col_path = col_swing_path_prefix + "%02d" % j
        exit = _next_exit(enter)
        last_exit = pd.Timestamp.min
        while last_exit < enter:
            scenario.loc[enter, col_path] = _enter
            scenario.loc[exit, col_path] = _exit
            last_exit = exit
            enter = _next_enter(last_exit)
            exit = _next_exit(enter)
        if j >= max_path_count:
            break

    scenario.sort_index(inplace=True)


def calculate_rr_of_swing_paths(scenario, col_price='close', col_swing_path_prefix='swp'):
    """ y, 2018.4.23 """

    _enter, _exit = 'enter', 'exit'

    assert isinstance(scenario, pd.DataFrame)
    assert col_price in scenario.columns

    swing_path_columns = [column for column in scenario.columns if column.startswith(col_swing_path_prefix)]
    if len(swing_path_columns):
        crrs = pd.DataFrame()
        for column in swing_path_columns:
            path = scenario[column].dropna()
            dates = path.index
            assert (path[0::2] == _enter).all(), "{}".format(path[0::2])
            assert (path[1::2] == _exit).all()
            assert path[-1] == _exit
            crr = 1.0
            count = 0
            for enter, exit in zip(dates[0::2], dates[1::2]):
                crr *= scenario.loc[exit, col_price] / scenario.loc[enter, col_price]
                count += 1
            crrs.loc[column, 'crr'] = crr
            crrs.loc[column, 'count'] = count
            crrs.loc[column, '1st enter'] = dates[0].strftime("%Y-%m-%d")
            crrs.loc[column, 'last exit'] = dates[-1].strftime("%Y-%m-%d")
        return crrs
    else:
        return pd.DataFrame()


def calculate_rr_of_pebble_trend(scenario, col_price='close', sample_size=10):
    """ y, 2018.4.23 """

    trend = scenario[col_price]
    return {
        'rr_p2p': trend.max() / trend.min(),
        'rr_s2s': trend[-sample_size:].mean() / trend[:sample_size].mean(),
    }


start_time = dt.datetime.now()

file_path = './sample/A000020-day.csv'
frame = pd.read_csv(file_path, index_col=0, parse_dates=True)
if False:
    col_y = 'aclose'
    max_training_size = 52 * 5 * 2  # 52 weeks/year x 5 days/week x 2 year
    start_date = pd.Timestamp('2017-1-1')
    stop_date = pd.Timestamp('2017-12-31')
    # stop_date = pd.Timestamp('2017-1-5')
    mask = (start_date <= frame.index) & (frame.index <= stop_date)
    total = mask.sum()
    results = pd.DataFrame()
    results.index.name = 'test_date'  # last date of test
    for j, training_date in enumerate(frame.index[mask], start=1):
        test_date = training_date + dt.timedelta(days=30)
        print(dt.datetime.now(), "[%d/%d]" % (j, total), training_date.date(), test_date.date(), end=' ')
        training, test = expect_ts_trend(frame, training_date=training_date, test_date=test_date,
                                         col_y=col_y, max_training_size=max_training_size)
        exp, exp_ref = test[_yhat], training[_yhat][-1]
        obs, obs_ref = frame[col_y].reindex(test.index), training[_y][-1]
        rs = correlate_expectation_to_observation(exp, obs)
        eor, dyhat, dyhat_y, dy = compare_expectation_with_observation(exp, obs, exp_ref, obs_ref)
        results.loc[test_date, 'training_date'] = training_date.date()  # last date of test
        results.loc[test_date, 'r_pe'] = rs['pe']
        results.loc[test_date, 'r_ke'] = rs['ke']
        results.loc[test_date, 'r_sp'] = rs['rdr']
        results.loc[test_date, 'eor'] = eor
        results.loc[test_date, 'dyhat'] = dyhat
        results.loc[test_date, 'dyhat_y'] = dyhat_y
        results.loc[test_date, 'dy'] = dy
        results.loc[test_date, 'rr'] = obs[-1] / obs_ref if dyhat > 0 else np.nan
        results.loc[test_date, _y] = obs[-1]
        results.loc[test_date, _yhat] = exp[-1]
        # results.loc[training_date, 'slope'] = np.polyfit(list(range(len(test))), test['yhat'], 1)[0]
        print("eor=%.3f, rr=%.3f (mrr=%.3f)" % (eor, results.loc[test_date, 'rr'], results['rr'].mean()))
    print('mean of rr =', results['rr'].mean())
    training.to_csv('./sample/training.csv')
    obs.name = _y
    test = pd.concat([test, obs], axis=1)
    test.to_csv('./sample/test.csv')
    results.to_csv('./sample/results.csv')
else:
    training = pd.read_csv('./sample/training.csv', index_col=0, parse_dates=True)
    test = pd.read_csv('./sample/test.csv', index_col=0, parse_dates=True)
    results = pd.read_csv('./sample/results.csv', index_col=0, parse_dates=True)
    obs, obs_ref = test[_y], training[_y][-1]
    # start_date, stop_date = results['training_date'][0], results.index[-1]
    start_date = pd.Timestamp('2017-1-1')
    stop_date = pd.Timestamp('2017-12-31')


scenario = frame.loc[start_date:stop_date].copy()
add_swing_paths_to_scenario(scenario, results, keep=10)
scenario.to_csv('./sample/scenario.csv')
rr_of_swing_paths = calculate_rr_of_swing_paths(scenario)
print(rr_of_swing_paths)
print(rr_of_swing_paths.mean())
rr_of_pebble_trend = calculate_rr_of_pebble_trend(scenario)
print(rr_of_pebble_trend)


fig_title = os.path.basename(__file__)
fig, (ax1, ax2, ax3, ax4) = plt.subplots(
    facecolor='w', nrows=4, gridspec_kw={'height_ratios': [2, 1, 1, 1]}, sharex=True)
fig.canvas.manager.set_window_title(fig_title)
fig.suptitle(fig_title, fontsize='large')

# m.plot(forecast)
# m.plot_components(forecast)
ax1.plot(training[_y], 'k-', alpha=0.5, label='y_training')
ax1.fill_between(training.index, training[_yhat_lower], training[_yhat_upper], color='r', alpha=0.2)
ax1.plot(training[_yhat], ls='-', c='r', label='yhat_training')
ax1.plot(obs, ls='-', c='b', label='y_test')
ax1.fill_between(test.index, test[_yhat_lower], test[_yhat_upper], color='r', alpha=0.2)
ax1.plot(test[_yhat], ls='-', c='r', label='yhat_test')
ax1.set_ylabel('eoc')
ax1.set_title(results.index[-1].date(), loc='right', size='small')
ax1.set_xlim(start_date, stop_date)
ax1.ticklabel_format(axis='y', style='sci', scilimits=(-2, 2))
set_axis_legend(ax1)

ax2.plot(results['rr'], ls='-', c='g')
ax2.set_ylabel('rr')
ax2.axhline(y=1.0, color='k', ls='-', alpha=0.2)
set_axis_legend(ax2)

ax3.plot(results['dyhat'], 'r-', alpha=0.5)
ax3.plot(results['dyhat_y'], 'g-', alpha=0.5)
ax3.axhline(y=0.0, color='k', ls='-', alpha=0.2)
ax3.set_ylabel('delta')

ax3t = ax3.twinx()
ax3t.plot(results['eor'], 'b-', alpha=0.5)
ax3t.set_ylabel('eor')

set_axis_legend(ax3, ax3t)

ax4.plot(results['r_pe'], 'r-', alpha=0.5)
ax4.plot(results['r_ke'], 'g-', alpha=0.5)
ax4.plot(results['r_sp'], 'b-', alpha=0.5)
ax4.axhline(y=0.0, color='k', ls='-', alpha=0.2)
ax4.set_ylabel('correlation, r')
set_axis_legend(ax4)

fig.tight_layout()
fig.subplots_adjust(wspace=0, hspace=0)

print("end at {}, running for {}".format(dt.datetime.now(), timedelta_str(dt.datetime.now() - start_time)))
plt.show()


