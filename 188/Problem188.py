#!/usr/bin/python

# The hyperexponentiation or tetration of a number a by a positive number b,
# denoted by a^^b, is recursively defined by:
# a^^1 = a
# a^^(k+1) = a^(a^^k)
#
# Thus we have e.g. 3^^2 = 3^3 = 27, hence 3^^3 = 3^27 = 7625597484987,
# and 3^^4 is roughly 10^(3.6383346400240996*10^12).
#
# Find the last 8 digits of 1777^^1855.

# Use Python power-modulo! pow(x,y,z) = (x^y) % z

def tetration(a, b, mod):
    u = a;
    for i in xrange(b-1):
        u = pow(a, u, mod)
    return u

#print "3^^3 % 100000000 = ", tetration(3, 3, 100000000)
print "1777^^1855 % 100000000 = ", tetration(1777, 1855, 100000000)
