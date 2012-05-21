#!/usr/bin/python

#
# Project Euler: Problem 098 (http://projecteuler.net/problem=98)
#

import sys

filename = "words.txt"
if (sys.argv[0] and len(sys.argv) > 1):
    filename = sys.argv[1]

print "Parsing file %s" % filename

f = open(filename)
words = f.readline().split(",")
f.close()
words = [w.strip('"') for w in words]

def pair_cmp(x,y):
    if (x[1] > y[1]): return 1
    if (x[1] < y[1]): return -1
    return 0

# Identify anagrams
def get_anagrams(wordlist):
    anags = {}
    for w in wordlist:
        l = list(w)
        l.sort()
        wa = "".join(l)
        if anags.has_key(wa):
            anags[wa].append(w)
        else:
            anags[wa] = [w]

    # Eliminate singletons
    for k in anags.keys():
        if (len(anags[k]) == 1):
            anags.pop(k)
    return anags

anagwords = get_anagrams(words)

squares = [str(x*x) for x in xrange(4,10000)]
anagsquares = get_anagrams(squares)

found_list = []
for i1 in anagwords.items():
    for i2 in anagsquares.items():
        if (len(i1[0]) != len(i2[0])): continue
        lw = i1[1]
        ls = i2[1]
        for w in lw:
            for s1 in ls:
                m1 = dict([(w[i],s1[i]) for i in xrange(len(w))])
                m2 = dict([(s1[i],w[i]) for i in xrange(len(s1))])
                if (len(m1) == len(m2)):
                    tmp_l = []
                    for w2 in lw:
                        s2 = "".join([m1[c] for c in w2])
                        if (s2 in ls):
                            tmp_l.append((w2,s2))
                    if (len(tmp_l) > 1):
                        found_list.extend(tmp_l)

max_square = ('',0)
for fl in found_list:
    if (int(fl[1]) > int(max_square[1])): max_square = fl

print "Answer:", max_square[1]
