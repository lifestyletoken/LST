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

#include <beast/nudb/nudb.cpp>

#include <skywell/nodestore/backend/MemoryFactory.cpp>
#include <skywell/nodestore/backend/NuDBFactory.cpp>
#include <skywell/nodestore/backend/NullFactory.cpp>
#include <skywell/nodestore/backend/RocksDBFactory.cpp>
#include <skywell/nodestore/backend/RocksDBQuickFactory.cpp>

#include <skywell/nodestore/impl/BatchWriter.cpp>
#include <skywell/nodestore/impl/DatabaseImp.h>
#include <skywell/nodestore/impl/DatabaseRotatingImp.cpp>
#include <skywell/nodestore/impl/DummyScheduler.cpp>
#include <skywell/nodestore/impl/DecodedBlob.cpp>
#include <skywell/nodestore/impl/EncodedBlob.cpp>
#include <skywell/nodestore/impl/ManagerImp.cpp>
#include <skywell/nodestore/impl/NodeObject.cpp>
#include <skywell/nodestore/impl/ScopedMetrics.cpp>

#include <skywell/nodestore/tests/Backend.test.cpp>
#include <skywell/nodestore/tests/Basics.test.cpp>
#include <skywell/nodestore/tests/Database.test.cpp>
#include <skywell/nodestore/tests/import_test.cpp>
#include <skywell/nodestore/tests/Timing.test.cpp>

