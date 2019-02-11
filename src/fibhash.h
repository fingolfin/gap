/****************************************************************************
**
**  This file is part of GAP, a system for computational discrete algebra.
**
**  Copyright of GAP belongs to its developers, whose names are too numerous
**  to list here. Please refer to the COPYRIGHT file for details.
**
**  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef GAP_FIBHASH_H
#define GAP_FIBHASH_H

#include "system.h"

#ifdef SYS_IS_64_BIT
#define FIB_HASH_MULT 0x9e3779b9UL
#define FIB_HASH_BITS 64
#else
#define FIB_HASH_MULT 0x9e3779b97f4a7c13UL
#define FIB_HASH_BITS 32
#endif

EXPORT_INLINE UInt FibHash(UInt word, unsigned bits)
{
    return (word * FIB_HASH_MULT) >> (FIB_HASH_BITS - bits);
}

#endif // GAP_FIBHASH_H
