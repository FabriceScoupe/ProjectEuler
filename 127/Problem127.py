#!/usr/bin/env python
from collections import defaultdict

# a < b < a+b == c
# a, b, c pairwise prime
# so rad(abc) = rad(a)*rad(b)*rad(a+b)

# 1,2,3 *not* an abc-hit rad(6)=6, not < 6
# so start at a = 2, b = 3

primes  = [2, 3]

factors = defaultdict(list)
rad = defaultdict(int)
abc_hits = 0

factors[2]=[2]
rad[2]=2
factors[3]=[3]
rad[3]=3

# Calculating primes, factors and rad up to 120000 (not subtle...)
for n in xrange(primes[-1]+2, 120001, 2):
    m = n
    rad[n]=1
    for p in primes:
        if m % p == 0:
            rad[n] *= p
            factors[n] += [p]
            while m % p == 0:
                m /= p
        if m == 1:
            #print "done", n
            break;
    if m == n:
        primes += [n]
        factors[n] = [n]
        rad[n] *= n
