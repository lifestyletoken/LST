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

#ifndef NDEBUG
# define consistency_check(cond) bassert(cond)
#else
# define consistency_check(cond)
#endif

#include <skywell/peerfinder/impl/Bootcache.cpp>
#include <skywell/peerfinder/impl/PeerfinderConfig.cpp>
#include <skywell/peerfinder/impl/Endpoint.cpp>
#include <skywell/peerfinder/impl/Manager.cpp>
#include <skywell/peerfinder/impl/SlotImp.cpp>
#include <skywell/peerfinder/impl/SourceStrings.cpp>

#include <skywell/peerfinder/sim/GraphAlgorithms.h>
#include <skywell/peerfinder/sim/WrappedSink.h>
#include <skywell/peerfinder/sim/Predicates.h>
#include <skywell/peerfinder/sim/FunctionQueue.h>
#include <skywell/peerfinder/sim/Message.h>
#include <skywell/peerfinder/sim/NodeSnapshot.h>
#include <skywell/peerfinder/sim/Params.h>
#include <skywell/peerfinder/sim/Tests.cpp>

#include <skywell/peerfinder/tests/Livecache.test.cpp>
#include <skywell/peerfinder/tests/PeerFinder_test.cpp>

#if DOXYGEN
#include <skywell/peerfinder/README.md>
#endif
