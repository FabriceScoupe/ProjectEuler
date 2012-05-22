#!/usr/bin/python
from math import factorial

fact = factorial

count = 0;

for n in xrange(3, 17):
    for m in xrange(2, n):
        sum_m = 0
        for a in xrange(0, m-1):
            for b in xrange(1, m-a):
                c = m-a-b
                c_abc = fact(n-1) / (fact(a)*fact(b)*fact(c))
                sum_m = sum_m + c_abc
        sum_m = sum_m / fact(n-m-1)
        sum_m = sum_m * (13**(n-m-1))
        count = count + sum_m

count = count * 2
print "Decimal answer: %d" % count
print "Answer: %X" % count
