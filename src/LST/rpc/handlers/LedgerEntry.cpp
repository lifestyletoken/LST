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
#include <skywell/protocol/Indexes.h>

namespace skywell {

// {
//   ledger_hash : <ledger>
//   ledger_index : <ledger_index>
//   ...
// }
Json::Value doLedgerEntry (RPC::Context& context)
{
    Ledger::pointer lpLedger;
    Json::Value jvResult = RPC::lookupLedger (
        context.params, lpLedger, context.netOps);

    if (!lpLedger)
        return jvResult;

    uint256     uNodeIndex;
    bool        bNodeBinary = false;

    if (context.params.isMember (jss::index))
    {
        // XXX Needs to provide proof.
        uNodeIndex.SetHex (context.params[jss::index].asString ());
        bNodeBinary = true;
    }
    else if (context.params.isMember (jss::account_root))
    {
        SkywellAddress   naAccount;

        if (!naAccount.setAccountID (
                context.params[jss::account_root].asString ())
            || !naAccount.getAccountID ())
        {
            jvResult[jss::error]   = "malformedAddress";
        }
        else
        {
            uNodeIndex
                    = getAccountRootIndex (naAccount.getAccountID ());
        }
    }
    else if (context.params.isMember (jss::directory))
    {
        if (!context.params[jss::directory].isObject ())
        {
            uNodeIndex.SetHex (context.params[jss::directory].asString ());
        }
        else if (context.params[jss::directory].isMember (jss::sub_index)
                 && !context.params[jss::directory][jss::sub_index].isIntegral ())
        {
            jvResult[jss::error]   = "malformedRequest";
        }
        else
        {
            std::uint64_t  uSubIndex
                    = context.params[jss::directory].isMember (jss::sub_index)
                    ? context.params[jss::directory][jss::sub_index].asUInt () : 0;

            if (context.params[jss::directory].isMember (jss::dir_root))
            {
                uint256 uDirRoot;

                uDirRoot.SetHex (context.params[jss::dir_root].asString ());

                uNodeIndex  = getDirNodeIndex (uDirRoot, uSubIndex);
            }
            else if (context.params[jss::directory].isMember (jss::owner))
            {
                SkywellAddress   naOwnerID;

                if (!naOwnerID.setAccountID (
                        context.params[jss::directory][jss::owner].asString ()))
                {
                    jvResult[jss::error]   = "malformedAddress";
                }
                else
                {
                    uint256 uDirRoot
                            = getOwnerDirIndex (
                                naOwnerID.getAccountID ());
                    uNodeIndex  = getDirNodeIndex (uDirRoot, uSubIndex);
                }
            }
            else
            {
                jvResult[jss::error]   = "malformedRequest";
            }
        }
    }
    else if (context.params.isMember (jss::generator))
    {
        SkywellAddress   naGeneratorID;

        if (!context.params[jss::generator].isObject ())
        {
            uNodeIndex.SetHex (context.params[jss::generator].asString ());
        }
        else if (!context.params[jss::generator].isMember (jss::regular_seed))
        {
            jvResult[jss::error]   = "malformedRequest";
        }
        else if (!naGeneratorID.setSeedGeneric (
            context.params[jss::generator][jss::regular_seed].asString ()))
        {
            jvResult[jss::error]   = "malformedAddress";
        }
        else
        {
            SkywellAddress na0Public;      // To find the generator's index.
            SkywellAddress naGenerator
                    = SkywellAddress::createGeneratorPublic (naGeneratorID);

            na0Public.setAccountPublic (naGenerator, 0);

            uNodeIndex  = getGeneratorIndex (na0Public.getAccountID ());
        }
    }
    else if (context.params.isMember (jss::offer))
    {
        SkywellAddress   naAccountID;

        if (!context.params[jss::offer].isObject ())
        {
            uNodeIndex.SetHex (context.params[jss::offer].asString ());
        }
        else if (!context.params[jss::offer].isMember (jss::account)
                 || !context.params[jss::offer].isMember (jss::seq)
                 || !context.params[jss::offer][jss::seq].isIntegral ())
        {
            jvResult[jss::error]   = "malformedRequest";
        }
        else if (!naAccountID.setAccountID (
            context.params[jss::offer][jss::account].asString ()))
        {
            jvResult[jss::error]   = "malformedAddress";
        }
        else
        {
            uNodeIndex  = getOfferIndex (naAccountID.getAccountID (),
                context.params[jss::offer][jss::seq].asUInt ());
        }
    }
    else if (context.params.isMember (jss::skywell_state))
    {
        SkywellAddress   naA;
        SkywellAddress   naB;
        Currency         uCurrency;
        Json::Value     jvSkywellState   = context.params[jss::skywell_state];

        if (!jvSkywellState.isObject ()
            || !jvSkywellState.isMember (jss::currency)
            || !jvSkywellState.isMember (jss::accounts)
            || !jvSkywellState[jss::accounts].isArray ()
            || 2 != jvSkywellState[jss::accounts].size ()
            || !jvSkywellState[jss::accounts][0u].isString ()
            || !jvSkywellState[jss::accounts][1u].isString ()
            || (jvSkywellState[jss::accounts][0u].asString ()
                == jvSkywellState[jss::accounts][1u].asString ())
           )
        {
            jvResult[jss::error]   = "malformedRequest";
        }
        else if (!naA.setAccountID (
                     jvSkywellState[jss::accounts][0u].asString ())
                 || !naB.setAccountID (
                     jvSkywellState[jss::accounts][1u].asString ()))
        {
            jvResult[jss::error]   = "malformedAddress";
        }
        else if (!to_currency (
            uCurrency, jvSkywellState[jss::currency].asString ()))
        {
            jvResult[jss::error]   = "malformedCurrency";
        }
        else
        {
            uNodeIndex  = getSkywellStateIndex (
                naA.getAccountID (), naB.getAccountID (), uCurrency);
        }
    }
    else
    {
        jvResult[jss::error]   = "unknownOption";
    }

    if (uNodeIndex.isNonZero ())
    {
        auto sleNode = lpLedger->getSLEi(uNodeIndex);

        if (context.params.isMember(jss::binary))
            bNodeBinary = context.params[jss::binary].asBool();

        if (!sleNode)
        {
            // Not found.
            // XXX Should also provide proof.
            jvResult[jss::error]       = "entryNotFound";
        }
        else if (bNodeBinary)
        {
            // XXX Should also provide proof.
            Serializer s;

            sleNode->add (s);

            jvResult[jss::node_binary] = strHex (s.peekData ());
            jvResult[jss::index]       = to_string (uNodeIndex);
        }
        else
        {
            jvResult[jss::node]        = sleNode->getJson (0);
            jvResult[jss::index]       = to_string (uNodeIndex);
        }
    }

    return jvResult;
}

} // skywell
