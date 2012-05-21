#!/usr/bin/env python

#
# Project Euler: Problem 080 (http://projecteuler.net/problem=80)
#

# It is well known that if the square root of a natural number is not
# an integer, then it is irrational.
# The decimal expansion of such square roots is infinite without any
# repeating pattern at all.
#
# The square root of two is 1.41421356237309504880..., and the digital sum
# of the first one hundred decimal digits is 475.
#
# For the first one hundred natural numbers, find the total of the digital
# sums of the first one hundred decimal digits for all the irrational
# square roots.

# This problem is straightforward in Python, with the support for
# arbitrarily long integers:
# Irrational square roots if integer not perfect square.
# r(n+1) = 1/2 ( r(n) + x / r(n) ) ? lim r(n)[n -> +inf] = sqrt( x ) = r
# Use long integers: multiply x by 10^202 (add 202 zeros)
# Take floor( sqrt( x ))*10^101 as first guess and apply algorithm.

def rootDigitSum( n, num_digits ):
    """Returns the sum of the (num_digits) first digits of the root of n"""
    r = 1
    # Calculating floor( root( n ) )
    while ( r*r < n ):
        r += 1
    if ( r*r == n ):
        # Perfect square => ignore
        return 0;
    --r
    x = n * 10 ** ((num_digits+1)*2)
    t = r * 10 ** (num_digits+1)
    r = 0
    while ( t != r ):
        r = t
        t = ( r + x / r ) / 2
    sum = 0
    for digit in str(t)[:100]:
        sum += int(digit)
    return sum

if __name__ == "__main__" :
    sum = 0
    for i in range(1,101):
        s = rootDigitSum( i, 100 )
        #print "sum ",i," = ",s
        sum += s
    print "Answer:",sum
