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

// This has to be included early to prevent an obscure MSVC compile error
#include <boost/asio/deadline_timer.hpp>

#include <skywell/protocol/JsonFields.h>

#include <skywell/rpc/RPCHandler.h>

#include <skywell/rpc/impl/Coroutine.cpp>
#include <skywell/rpc/impl/Manager.cpp>
#include <skywell/rpc/impl/RPCHandler.cpp>
#include <skywell/rpc/impl/Status.cpp>
#include <skywell/rpc/impl/Yield.cpp>
#include <skywell/rpc/impl/Utilities.cpp>

#include <skywell/rpc/handlers/Handlers.h>
#include <skywell/rpc/handlers/AccountCurrencies.cpp>
#include <skywell/rpc/handlers/AccountInfo.cpp>
#include <skywell/rpc/handlers/AccountLines.cpp>
#include <skywell/rpc/handlers/AccountObjects.cpp>
#include <skywell/rpc/handlers/AccountOffers.cpp>
#include <skywell/rpc/handlers/AccountTx.cpp>
#include <skywell/rpc/handlers/AccountTxOld.cpp>
#include <skywell/rpc/handlers/AccountTxSwitch.cpp>
#include <skywell/rpc/handlers/BlackList.cpp>
#include <skywell/rpc/handlers/BookOffers.cpp>
#include <skywell/rpc/handlers/CanDelete.cpp>
#include <skywell/rpc/handlers/Connect.cpp>
#include <skywell/rpc/handlers/ConsensusInfo.cpp>
#include <skywell/rpc/handlers/Feature.cpp>
#include <skywell/rpc/handlers/FetchInfo.cpp>
#include <skywell/rpc/handlers/GetCounts.cpp>
#include <skywell/rpc/handlers/Internal.cpp>
#include <skywell/rpc/handlers/Ledger.cpp>
#include <skywell/rpc/handlers/LedgerAccept.cpp>
#include <skywell/rpc/handlers/LedgerCleaner.cpp>
#include <skywell/rpc/handlers/LedgerClosed.cpp>
#include <skywell/rpc/handlers/LedgerCurrent.cpp>
#include <skywell/rpc/handlers/LedgerData.cpp>
#include <skywell/rpc/handlers/LedgerEntry.cpp>
#include <skywell/rpc/handlers/LedgerHeader.cpp>
#include <skywell/rpc/handlers/LedgerRequest.cpp>
#include <skywell/rpc/handlers/LogLevel.cpp>
#include <skywell/rpc/handlers/LogRotate.cpp>
#include <skywell/rpc/handlers/NoSkywellCheck.cpp>
#include <skywell/rpc/handlers/OwnerInfo.cpp>
#include <skywell/rpc/handlers/PathFind.cpp>
#include <skywell/rpc/handlers/Peers.cpp>
#include <skywell/rpc/handlers/Ping.cpp>
#include <skywell/rpc/handlers/Print.cpp>
#include <skywell/rpc/handlers/Random.cpp>
#include <skywell/rpc/handlers/SkywellPathFind.cpp>
#include <skywell/rpc/handlers/ServerInfo.cpp>
#include <skywell/rpc/handlers/RPCInfo.cpp>
#include <skywell/rpc/handlers/ServerState.cpp>
#include <skywell/rpc/handlers/Sign.cpp>
#include <skywell/rpc/handlers/Stop.cpp>
#include <skywell/rpc/handlers/Submit.cpp>
#include <skywell/rpc/handlers/Subscribe.cpp>
#include <skywell/rpc/handlers/TransactionEntry.cpp>
#include <skywell/rpc/handlers/Tx.cpp>
#include <skywell/rpc/handlers/TxHistory.cpp>
#include <skywell/rpc/handlers/UnlAdd.cpp>
#include <skywell/rpc/handlers/UnlDelete.cpp>
#include <skywell/rpc/handlers/UnlList.cpp>
#include <skywell/rpc/handlers/UnlLoad.cpp>
#include <skywell/rpc/handlers/UnlNetwork.cpp>
#include <skywell/rpc/handlers/UnlReset.cpp>
#include <skywell/rpc/handlers/UnlScore.cpp>
#include <skywell/rpc/handlers/Unsubscribe.cpp>
#include <skywell/rpc/handlers/ValidationCreate.cpp>
#include <skywell/rpc/handlers/ValidationSeed.cpp>
#include <skywell/rpc/handlers/WalletPropose.cpp>
#include <skywell/rpc/handlers/WalletSeed.cpp>

#include <skywell/rpc/impl/AccountFromString.cpp>
#include <skywell/rpc/impl/Accounts.cpp>
#include <skywell/rpc/impl/GetAccountObjects.cpp>
#include <skywell/rpc/impl/Handler.cpp>
#include <skywell/rpc/impl/KeypairForSignature.cpp>
#include <skywell/rpc/impl/LegacyPathFind.cpp>
#include <skywell/rpc/impl/LookupLedger.cpp>
#include <skywell/rpc/impl/ParseAccountIds.cpp>
#include <skywell/rpc/impl/TransactionSign.cpp>
#include <skywell/rpc/impl/RPCVersion.cpp>

#include <skywell/rpc/tests/Coroutine.test.cpp>
#include <skywell/rpc/tests/JSONRPC.test.cpp>
#include <skywell/rpc/tests/KeyGeneration.test.cpp>
#include <skywell/rpc/tests/Status.test.cpp>
#include <skywell/rpc/tests/Yield.test.cpp>
