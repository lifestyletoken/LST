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

#ifndef SKYWELL_SHAMAP_TESTS_COMMON_H_INCLUDED
#define SKYWELL_SHAMAP_TESTS_COMMON_H_INCLUDED

#include <BeastConfig.h>
#include <skywell/shamap/Family.h>
#include <skywell/shamap/FullBelowCache.h>
#include <skywell/shamap/TreeNodeCache.h>
#include <skywell/shamap/SHAMap.h>
#include <skywell/basics/StringUtilities.h>
#include <skywell/nodestore/DummyScheduler.h>
#include <skywell/nodestore/Manager.h>
#include <beast/utility/Journal.h>
#include <beast/chrono/manual_clock.h>

namespace skywell {
namespace shamap {
namespace tests {

class TestFamily : public shamap::Family
{
private:
    beast::manual_clock <
        std::chrono::steady_clock> clock_;
    NodeStore::DummyScheduler scheduler_;
    TreeNodeCache treecache_;
    FullBelowCache fullbelow_;
    std::unique_ptr<NodeStore::Database> db_;

public:
    explicit
    TestFamily (beast::Journal j)
        : treecache_ ("TreeNodeCache", 65536, 60, clock_, j)
        , fullbelow_ ("full_below", clock_)
    {
        Section testSection;
        testSection.set("type", "memory");
        testSection.set("Path", "SHAMap_test");
        db_ = NodeStore::Manager::instance ().make_Database (
            "test", scheduler_, j, 1, testSection);
    }

    beast::manual_clock <std::chrono::steady_clock>
    clock()
    {
        return clock_;
    }

    FullBelowCache&
    fullbelow() override
    {
        return fullbelow_;
    }

    FullBelowCache const&
    fullbelow() const override
    {
        return fullbelow_;
    }

    TreeNodeCache&
    treecache() override
    {
        return treecache_;
    }

    TreeNodeCache const&
    treecache() const override
    {
        return treecache_;
    }

    NodeStore::Database&
    db() override
    {
        return *db_;
    }

    NodeStore::Database const&
    db() const override
    {
        return *db_;
    }

    void
    missing_node (std::uint32_t refNum) override
    {
        throw std::runtime_error("missing node");
    }
};

} // tests
} // shamap
} // skywell

#endif
