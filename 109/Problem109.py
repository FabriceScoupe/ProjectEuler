#!/usr/bin/env python

throw  = dict()

for i in xrange(1, 21):
    throw['S'+str(i)] = i
    throw['D'+str(i)] = 2*i
    throw['T'+str(i)] = 3*i

throw['-'] = 0
throw['S25'] = 25
throw['D25'] = 50
 
print throw.keys()

throws_2 = { tuple(sorted([k1, k2])) for k1 in throw.keys() for k2 in throw.keys() }
throws_3 = { (t[0], t[1], k3) for t in throws_2 for k3 in throw.keys() if k3[0]=='D' }

combis = { t : throw[t[0]]+throw[t[1]]+throw[t[2]] for t in throws_3 }

is_checkout = lambda t : any([t[i][0]=='D' for i in xrange(3)])

sol6 = {(d) for d in combis if combis[d]==6 and is_checkout(d)}
print "Checkout at 6 points:", len(sol6)

print "Total checkouts:", len(combis)

sol = {(d) for d in combis if is_checkout(d) and combis[d]<100}
print "Answer:", len(sol)
