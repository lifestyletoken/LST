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

#ifndef SKYWELL_APP_CREATEOFFER_H_INCLUDED
#define SKYWELL_APP_CREATEOFFER_H_INCLUDED

#include <skywell/app/book/OfferStream.h>
#include <skywell/app/book/Taker.h>
#include <skywell/app/book/Types.h>
#include <skywell/app/book/Amounts.h>
#include <skywell/app/transactors/Transactor.h>
#include <skywell/basics/Log.h>
#include <skywell/json/to_string.h>
#include <beast/cxx14/memory.h>
#include <utility>

namespace skywell {

namespace legacy {

class CreateOffer
    : public Transactor
{
private:
    // Determine if we are authorized to hold the asset we want to get
    TER
    checkAcceptAsset(IssueRef issue) const;

    /*  Fill offer as much as possible by consuming offers already on the books.
        We adjusts account balances and charges fees on top to taker.

        @param taker_amount.in How much the taker offers
        @param taker_amount.out How much the taker wants

        @return result.first crossing operation success/failure indicator.
                result.second amount of offer left unfilled - only meaningful
                              if result.first is tesSUCCESS.
    */
    std::pair<TER, core::Amounts>
    crossOffers (core::LedgerView& view,
        core::Amounts const& taker_amount);

public:
    CreateOffer (STTx const& txn,
        TransactionEngineParams params, TransactionEngine* engine);

    TER
    doApply() override;
};

std::pair <bool, TER>
transact_CreateOffer (STTx const& txn,
    TransactionEngineParams params, TransactionEngine* engine);

}

}

#endif
