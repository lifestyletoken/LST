//------------------------------------------------------------------------------
/*
    This file is part of skywelld: https://github.com/skywell/skywelld
    Copyright (c) 2012, 2013 Skywell Labs Inc.

    Permission to use, copy, modify, and/or distribute this software for any
    purpose  with  or without fee is hereby granted, provided that the above
    copyright notice and this permission notice appear in all copies.

    THE  SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
    WITH  REGARD  TO  THIS  SOFTWARE  INCLUDING  ALL  IMPLIED  WARRANTIES  OF
    MERCHANTABILITY  AND  FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
    ANY  SPECIAL ,  DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
    WHATSOEVER  RESULTING  FROM  LOSS  OF USE, DATA OR PROFITS, WHETHER IN AN
    ACTION  OF  CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/
//==============================================================================

#include <BeastConfig.h>

#include <skywell/basics/impl/BasicConfig.cpp>
#include <skywell/basics/impl/CheckLibraryVersions.cpp>
#include <skywell/basics/impl/CountedObject.cpp>
#include <skywell/basics/impl/Log.cpp>
#include <skywell/basics/impl/make_SSLContext.cpp>
#include <skywell/basics/impl/RangeSet.cpp>
#include <skywell/basics/impl/ResolverAsio.cpp>
#include <skywell/basics/impl/strHex.cpp>
#include <skywell/basics/impl/StringUtilities.cpp>
#include <skywell/basics/impl/Sustain.cpp>
#include <skywell/basics/impl/TestSuite.test.cpp>
#include <skywell/basics/impl/ThreadName.cpp>
#include <skywell/basics/impl/Time.cpp>
#include <skywell/basics/impl/UptimeTimer.cpp>

#include <skywell/basics/tests/CheckLibraryVersions.test.cpp>
#include <skywell/basics/tests/hardened_hash_test.cpp>
#include <skywell/basics/tests/KeyCache.test.cpp>
#include <skywell/basics/tests/RangeSet.test.cpp>
#include <skywell/basics/tests/StringUtilities.test.cpp>
#include <skywell/basics/tests/TaggedCache.test.cpp>

#if DOXYGEN
#include <skywell/basics/README.md>
#endif
