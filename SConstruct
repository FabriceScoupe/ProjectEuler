# ----- scons: main software construction file -----
# By default, all problems built (if need be) and executed
# scons <3-digit problem number> : builds and executes problem
# scons -c : cleans.

import os
import re

# Get a list of all the problem directories (3-digit numbers):
problems = [e for e in os.listdir('.') if re.match('[0-9]{3}', e)]
problems.sort()

env = Environment(CCFLAGS= '-O2 -Wall -Weffc++ -Werror')
env.Default(problems)

# Rules to build (if need be) and execute the problems
# Results stored in result<number>.log, in <number> directory.
# ------------------------------------------------------------
for p in problems:
    f = "Problem%s" % p
    # C/C++ source?
    if (os.access("%s/%s.cc" % (p, f), os.F_OK)):
        env.Program("%s/%s" % (p, f), "%s/%s.cc" % (p, f))
        e = f
    # Python source?
    elif (os.access("%s/%s.py" % (p, f), os.F_OK)):
        e = f+".py"
    log = "result%s.log" % p
    env.Depends(p, "%s/%s" % (p, log))
    env.Command("%s/%s" % (p, log), "%s/%s" % (p, e), [
        "@echo > "+log,
        "@echo \"##### Executing "+p+"\" >> "+log,
        "@echo \"--- START:\" `date +%H:%M:%S.%N` >> "+log,
        "@echo >> "+log,
        "@./"+e+" >> "+log,
        "@echo >> "+log,
        "@echo \"--- STOP:\" `date +%H:%M:%S.%N` >> "+log,
        "@echo >> "+log,
        "@cat "+log], chdir=1)
