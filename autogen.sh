#!/bin/sh -ex
#
# Requires GNU autoconf, GNU make and GNU libtool.
#
autoreconf -vif `dirname "$0"`
