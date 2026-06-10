"""
y, 2016.4.25 - 5.1
"""


def GetAccumulatedNumList(aList, bInplace=True):
    """
    y (copyRight) 2016.4.25
    :param aList:  list of numeric elements
    :param bInplace: in-place operation if true, out-of-place if false
    :return: list with accumulation of elements
    """

    if bInplace is True:
        rList = aList
    else:
        rList = aList.copy()
    sum = 0
    for i in range(0, len(rList)):
        sum += rList[i]
        rList[i] = sum

    return rList


def GetNormalizedNumList(aList, fMax=None, bInplace=True):
    """
    y (copyRight) 2016.4.25
    :param aList:  list of numeric elements
    :param bInplace: in-place operation if true, out-of-place if false
    :return: list after normalization of elements
    """

    if fMax:
        rList = [value / fMax for value in aList]
    else:
        rList = [value / max(aList) for value in aList]
    if bInplace is True:
        j = len(aList)
        aList.extend(rList)
        del aList[:j]
        rList = aList

    return rList


def GetFirstElementInList():
    """
    y (copyRight) 2016.5.1
    :return:
    """
    my_list = range(10)
    r = next((e for e in my_list if e == 3), None)
    # r =(e for e in my_list if e==3).next()    <<< not working, don't know
    print(r)


def GetBooleanIndicesOfFirstInRepeationInInList():
    """
    y (copyRight) 2016.5.1
    :return: boolean list for Pandas DataFrame operation
    """

    def isNaN(num):
        return num != num

    nan = float("nan")
    my = [0, 1, 1, 2, 3, 3, 4, 5, 6, 6, 'a', 'a', nan, nan, 7]
    # print(my[-2])
    tracker = None
    r = []
    for i in range(len(my)):
        if my[i] == tracker or (isNaN(my[i]) and isNaN(tracker)):
            r.append(0)  # False
        else:
            tracker = my[i]
            r.append(1)  # True

    print(my)
    print(r)


if __name__ == '__main__':
    aList = list(range(11))
    rList = GetAccumulatedNumList(aList)
    print(aList, rList)

    rList = GetNormalizedNumList(aList, bInplace=True)
    print(aList, rList)

    GetFirstElementInList()

    GetBooleanIndicesOfFirstInRepeationInInList()
