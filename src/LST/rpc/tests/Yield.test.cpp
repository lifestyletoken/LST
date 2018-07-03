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
#include <skywell/rpc/Yield.h>
#include <skywell/rpc/tests/TestOutputSuite.test.h>

namespace skywell {
namespace RPC {

struct Yield_test : TestOutputSuite
{
    void chunkedYieldingTest ()
    {
        setup ("chunkedYieldingTest");
        std::string lastYield;

        auto yield = [&]() { lastYield = output_; };
        auto output = chunkedYieldingOutput (
            Json::stringOutput (output_), yield, 5);
        output ("hello");
        expectResult ("hello");
        expectEquals (lastYield, "");

        output (", th");  // Goes over the boundary.
        expectResult ("hello, th");
        expectEquals (lastYield, "");

        output ("ere!");  // Forces a yield.
        expectResult ("hello, there!");
        expectEquals (lastYield, "hello, th");

        output ("!!");
        expectResult ("hello, there!!!");
        expectEquals (lastYield, "hello, th");

        output ("");    // Forces a yield.
        expectResult ("hello, there!!!");
        expectEquals (lastYield, "hello, there!!!");
    }

    void trivialCountedYieldTest()
    {
        setup ("trivialCountedYield");

        auto didYield = false;
        auto yield = [&]() { didYield = true; };

        CountedYield cy (0, yield);

        for (auto i = 0; i < 4; ++i)
        {
            cy.yield();
            expect (!didYield, "We yielded when we shouldn't have.");
        }
    }

    void countedYieldTest()
    {
        setup ("countedYield");

        auto didYield = false;
        auto yield = [&]() { didYield = true; };

        CountedYield cy (5, yield);

        for (auto j = 0; j < 3; ++j)
        {
            for (auto i = 0; i < 4; ++i)
            {
                cy.yield();
                expect (!didYield, "We yielded when we shouldn't have.");
            }
            cy.yield();
            expect (didYield, "We didn't yield");
            didYield = false;
        }
    }

    void run () override
    {
        chunkedYieldingTest();
        trivialCountedYieldTest();
        countedYieldTest();
    }
};

BEAST_DEFINE_TESTSUITE(Yield, skywell_basics, skywell);

} // RPC
} // skywell
