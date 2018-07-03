//------------------------------------------------------------------------------
/*
    This file is part of skywelld: https://github.com/skywell/skywelld
    Copyright (c) 2012-2014 Skywell Labs Inc.

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

namespace skywell {

// {
//   secret: <string>
// }
Json::Value doWalletSeed (RPC::Context& context)
{
    SkywellAddress   seed;
    bool bSecret = context.params.isMember (jss::secret);

    if (bSecret && !seed.setSeedGeneric (context.params[jss::secret].asString ()))
    {
        return rpcError (rpcBAD_SEED);
    }
    else
    {
        SkywellAddress   raAccount;

        if (!bSecret)
        {
            seed.setSeedRandom ();
        }

        SkywellAddress raGenerator = SkywellAddress::createGeneratorPublic (seed);

        raAccount.setAccountPublic (raGenerator, 0);

        Json::Value obj (Json::objectValue);

        obj[jss::seed]     = seed.humanSeed ();
        obj[jss::key]      = seed.humanSeed1751 ();
        obj[jss::deprecated] = "Use wallet_propose instead";

        return obj;
    }
}
} // skywell
