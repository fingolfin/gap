#!/bin/sh -ex
#
# Regenerate configure from configure.ac
#
# Requires GNU autoconf.
#
autoreconf -vif `dirname "$0"`
