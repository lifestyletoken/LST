//------------------------------------------------------------------------------
/*
    This file is part of skywelld: https://github.com/skywell/skywelld
    Copyright 2014 Skywell Labs Inc.

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
#include <skywell/overlay/impl/TMHello.h>
#include <beast/unit_test/suite.h>

namespace skywell {

class TMHello_test : public beast::unit_test::suite
{
private:
    template <class FwdIt>
    static
    std::string
    join (FwdIt first, FwdIt last, char c = ',')
    {
        std::string result;
        if (first == last)
            return result;
        result = to_string(*first++);
        while(first != last)
            result += "," + to_string(*first++);
        return result;
    }

    void
    check(std::string const& s, std::string const& answer)
    {
        auto const result = parse_ProtocolVersions(s);
        expect(join(result.begin(), result.end()) == answer);
    }

public:
    void
    test_protocolVersions()
    {
        check("", "");
        check("RTXP/1.0", "1.0");
        check("RTXP/1.0, Websocket/1.0", "1.0");
        check("RTXP/1.0, RTXP/1.0", "1.0");
        check("RTXP/1.0, RTXP/1.1", "1.0,1.1");
        check("RTXP/1.1, RTXP/1.0", "1.0,1.1");
    }

    void
    run()
    {
        test_protocolVersions();
    }
};

BEAST_DEFINE_TESTSUITE(TMHello,overlay,skywell);

}
