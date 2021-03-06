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

#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable: 4309) // truncation of constant value
#endif
#include <skywell/app/paths/Node.cpp>
#include <skywell/app/paths/PathRequest.cpp>
#include <skywell/app/paths/PathRequests.cpp>
#include <skywell/app/paths/PathState.cpp>
#include <skywell/app/paths/SkywellCalc.cpp>
#include <skywell/app/paths/cursor/AdvanceNode.cpp>
#include <skywell/app/paths/cursor/DeliverNodeForward.cpp>
#include <skywell/app/paths/cursor/DeliverNodeReverse.cpp>
#include <skywell/app/paths/cursor/ForwardLiquidity.cpp>
#include <skywell/app/paths/cursor/ForwardLiquidityForAccount.cpp>
#include <skywell/app/paths/cursor/Liquidity.cpp>
#include <skywell/app/paths/cursor/NextIncrement.cpp>
#include <skywell/app/paths/cursor/ReverseLiquidity.cpp>
#include <skywell/app/paths/cursor/ReverseLiquidityForAccount.cpp>
#include <skywell/app/paths/cursor/SkywellLiquidity.cpp>

#include <skywell/app/paths/SkywellLineCache.cpp>

#ifdef _MSC_VER
#pragma warning (pop)
#endif
