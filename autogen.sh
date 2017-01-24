#!/bin/sh -ex
#
# Regenerate configure from configure.ac
#
# Requires GNU autoconf.
#
autoreconf -vif --no-recursive -I cnf/m4 `dirname "$0"`
