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
#include <skywell/core/Config.h>
#include <skywell/legacy/0.27/Emulate027.h>

namespace skywell {

namespace legacy {

bool
emulate027 (Ledger::ref ledger)
{
    // In standalone mode, the server always uses 0.28 semantics to allow
    // unit tests to succeed.
    if (getConfig ().RUN_STANDALONE)
        return false;

    // The server also uses 0.28 semantics for all ledgers whose parent
    // closed after 2015-05-12 13:00:00 PDT.
    static std::uint32_t const legacy_cutoff = 484776000;

    if (ledger->getParentCloseTimeNC () > legacy_cutoff)
        return false;

    return true;
}

}

}
