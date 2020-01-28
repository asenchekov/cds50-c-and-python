from nltk.tokenize import sent_tokenize


def lines(a, b):
    """Return lines in both a and b"""
    # using splitlines() to split the strings into list of lines
    aLines = a.splitlines()
    bLines = b.splitlines()
    # creating empty list for matches
    matches = []
    # checking if two lists of lines excist
    if aLines and bLines:
        # iterating over each line from aLines
        for line in aLines:
            # matching curent line to lines from bLines
            for two in bLines:
                if line == two:
                    if matches:
                        match = False
                        # checking if we have already found this match
                        for each in matches:
                            if each == line:
                                match = True
                                break
                        if not match:
                            matches.append(line)
                            print(line)
                    else:
                        matches.append(line)
    return matches


def sentences(a, b):
    """Return sentences in both a and b"""
    # spliting the two strings into sentences
    aSent = sent_tokenize(a)
    bSent = sent_tokenize(b)
    matches = []
    # cheking if both sentance list exsists
    if aSent and bSent:
        # iterating over each sentace from aSent and matching it to each of bSent
        for one in aSent:
            for two in bSent:
                if one == two:
                    if matches:
                        match = False
                        # checks if we have already found this match
                        for each in matches:
                            if each == one:
                                match = True
                                break
                        if not match:
                            matches.append(one)
                    else:
                        matches.append(one)
    return matches


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    # creating empty lists for substrings and matches
    aSubs = []
    bSubs = []
    matches = []
    # creating range for iterating over the strings
    rangeA = range(len(a))
    rangeB = range(len(b))
    # populating the lists with possible substrings
    for one in rangeA:
        if not len(a[one:n+one]) < n:
            aSubs.append(a[one:n+one])
    for one in rangeB:
        if not len(b[one:n+one]) < n:
            bSubs.append(b[one:n+one])
    # Checking if the lists are not empty
    if aSubs and bSubs:
        # Iterating over every substring from aSubs and matching it to substrings from bSubs
        for one in aSubs:
            for two in bSubs:
                if one == two:
                    if matches:
                        match = False
                        # Checking if we haven't found that match already
                        for each in matches:
                            if each == one:
                                match = True
                                break
                        if not match:
                            matches.append(one)
                    else:
                        matches.append(one)
    return matches
