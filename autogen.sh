#!/bin/sh -ex
#
# Regenerate configure from configure.ac
#
# Requires GNU autoconf.
#
autoreconf -vif --no-recursive `dirname "$0"`
