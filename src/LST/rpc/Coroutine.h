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

#ifndef SKYWELL_RPC_COROUTINE_H_INCLUDED
#define SKYWELL_RPC_COROUTINE_H_INCLUDED

#include <skywell/rpc/Yield.h>

namespace skywell {
namespace RPC {

/** Runs a function that takes a yield as a coroutine. */
class Coroutine
{
public:
    using YieldFunction = std::function <void (Yield const&)>;

    explicit Coroutine (YieldFunction const&);
    ~Coroutine();

    /** Is the coroutine finished? */
    operator bool() const;

    /** Run one more step of the coroutine. */
    void operator()() const;

private:
    struct Impl;

    std::shared_ptr<Impl> impl_;
    // We'd prefer to use std::unique_ptr here, but unfortunately, in C++11
    // move semantics don't work well with `std::bind` or lambdas.
};

} // RPC
} // skywell

#endif
