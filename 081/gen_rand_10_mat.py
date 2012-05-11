#!/bin/python
import random
l=[]
for i in range(1,26):
    l+=[str(random.randrange(1,10))]
print ",".join(l)
