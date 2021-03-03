#!/usr/bin/env python3
#
from utils import *

import json
import os
import shutil

if len(sys.argv) != 3:
     error(f"usage: {sys.argv[0]} <gaproot> <json>")

gaproot = sys.argv[1]
jsonfile = sys.argv[2]

if not os.path.isdir(gaproot):
    error(f"{gaproot} is not a directory")
if not os.path.isfile(jsonfile):
    error(f"{jsonfile} is not a file")

# TODO: where to place the results??
dstdir = "Manuals"

with open(jsonfile, "r") as f:
    pkgs = json.load(f)

# iterate over all packages and their descriptions
for k, v in pkgs.items():
    # extract the name of package directory
    print("processing ", v["PackageName"])
    pkgdir = os.path.join(gaproot, v["InstallationPath"])
    if not os.path.isdir(pkgdir):
        error(f"{pkgdir} is not a directory")
    docpaths = set()
    for b in v["PackageDoc"]:
        docpaths = docpaths.union(b["ArchiveURLSubset"])
    for p in docpaths:
        p = os.path.join(pkgdir, p)
        if os.path.isdir(p):
            notice(f"  copying dir {p}")
           #shutil.copytree(p, DST) 
        elif os.path.isfile(p):
            notice(f"  copying file {p}")
           #shutil.copy(p, DST) 
        else:
            error(f"{p} is not a directory or file")


# shutil.copytree(src, dst, symlinks=False, ignore=None, copy_function=copy2, ignore_dangling_symlinks=False, dirs_exist_ok=False)


# Some examples of what can happen
# 
# anupq  --  ['doc']
# autpgrp  --  ['doc', 'htm']
# 
# ctbllib  --  ['doc', 'htm']
# ctbllib  --  ['doc2']
# 
# gapdoc  --  ['doc', 'example']
# gapdoc  --  ['example', 'doc']
# 
# sonata  --  ['doc/ref', 'htm/ref']
# sonata  --  ['doc/tut', 'htm/tut']
# 
# transgrp  --  ['doc/manual.pdf', 'htm']
