/*
    This file is part of KCachegrind.

    SPDX-FileCopyrightText: 2002-2016 Josef Weidendorfer <Josef.Weidendorfer@gmx.de>

    SPDX-License-Identifier: GPL-2.0-only
*/

#include "addr.h"

//---------------------------------------------------
// Addr

bool Addr::set(FixString& s)
{
    return s.stripUInt64(_v);
}

int Addr::set(const char *s)
{
    int n = 0;
    _v = 0;

    while((n<16) && *s) {
        if ((*s>='0') && (*s<='9'))
            _v = 16*_v + (*s-'0');
        else if ((*s>='a') && (*s<='f'))
            _v = 16*_v + 10 + (*s-'a');
        else if ((*s>='A') && (*s<='F'))
            _v = 16*_v + 10 + (*s-'A');
        else break;
        s++;
        n++;
    }

    return n;
}


QString Addr::toString() const
{
    if (_v == 0) return QStringLiteral("0");

    uint64 n = _v;
    QString hex;
    hex.reserve(16);

    while(n>0) {
        int d = (n & 15);
        hex = QChar((d<10) ? ('0'+d) : ('A'-10+d)) + hex;
        n /= 16;
    }

    return hex;
}

QString Addr::pretty() const
{
    if (_v == 0) return QStringLiteral("0");

    uint64 n = _v;
    int p = 0;
    QString hex;
    hex.reserve(20);

    while(n>0) {
        int d = (n & 15);
        if ((p>0) && ((p%4)==0)) hex = ' ' + hex;
        hex = QChar((d<10) ? ('0'+d) : ('A'-10+d)) + hex;
        n /= 16;
        p++;
    }

    return hex;
}

bool Addr::isInRange(Addr a, int distance)
{
    uint64 diff = (a._v > _v) ? (a._v - _v) : (_v - a._v);
    uint64 dist = (distance<0) ? distance : -distance;
    return (diff < dist);
}
