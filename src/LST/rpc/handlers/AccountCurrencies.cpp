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
#include <skywell/rpc/impl/AccountFromString.h>
#include <skywell/rpc/impl/LookupLedger.h>
#include <skywell/app/paths/SkywellState.h>

namespace skywell {

Json::Value doAccountCurrencies (RPC::Context& context)
{
    auto& params = context.params;

    // Get the current ledger
    Ledger::pointer ledger;
    Json::Value result (RPC::lookupLedger (params, ledger, context.netOps));

    if (!ledger)
        return result;

    if (!(params.isMember (jss::account) || params.isMember (jss::ident)))
        return RPC::missing_field_error (jss::account);

    std::string const strIdent (params.isMember (jss::account)
        ? params[jss::account].asString ()
        : params[jss::ident].asString ());

    int iIndex = 0;

    if (params.isMember (jss::account_index))
    {
        auto const& accountIndex = params[jss::account_index];
        if (!accountIndex.isUInt() && !accountIndex.isInt ())
            return RPC::invalid_field_message (jss::account_index);
        iIndex = accountIndex.asUInt ();
    }

    bool const bStrict = params.isMember (jss::strict) &&
            params[jss::strict].asBool ();

    // Get info on account.
    bool bIndex; // out param
    SkywellAddress naAccount; // out param
    Json::Value jvAccepted (RPC::accountFromString (
        ledger, naAccount, bIndex, strIdent, iIndex, bStrict, context.netOps));

    if (!jvAccepted.empty ())
        return jvAccepted;

    std::set<Currency> send, receive;
    for (auto const& item : getSkywellStateItems (naAccount.getAccountID (), ledger))
    {
        SkywellState* rspEntry = (SkywellState*) item.get ();
        STAmount const& saBalance = rspEntry->getBalance ();

        if (saBalance < rspEntry->getLimit ())
            receive.insert (saBalance.getCurrency ());
        if ((-saBalance) < rspEntry->getLimitPeer ())
            send.insert (saBalance.getCurrency ());
    }

    send.erase (badCurrency());
    receive.erase (badCurrency());

    Json::Value& sendCurrencies =
            (result[jss::send_currencies] = Json::arrayValue);
    for (auto const& c: send)
        sendCurrencies.append (to_string (c));

    Json::Value& recvCurrencies =
            (result[jss::receive_currencies] = Json::arrayValue);
    for (auto const& c: receive)
        recvCurrencies.append (to_string (c));

    return result;
}

} // skywell
