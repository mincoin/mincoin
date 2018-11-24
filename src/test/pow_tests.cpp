// Copyright (c) 2015 The Bitcoin Core developers
// Copyright (c) 2013-2019 The Mincoin Core developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chain.h"
#include "chainparams.h"
#include "pow.h"
#include "random.h"
#include "util.h"
#include "test/test_bitcoin.h"

#include <boost/test/unit_test.hpp>

using namespace std;

BOOST_FIXTURE_TEST_SUITE(pow_tests, BasicTestingSetup)

/* Test calculation of next difficulty target with no constraints applying */
BOOST_AUTO_TEST_CASE(get_next_work)
{
    SelectParams(CBaseChainParams::MAIN);
    const Consensus::Params& params = Params().GetConsensus();

    int64_t nLastRetargetTime = 1365569158; // Block #10799
    CBlockIndex pindexLast;
    pindexLast.nHeight = 11519;
    pindexLast.nTime = 1365612035;  // Block #11519
    pindexLast.nBits = 0x1d54f960;
    BOOST_CHECK_EQUAL(CalculateNextWorkRequired(&pindexLast, nLastRetargetTime, params), 0x1d5456ba);
}

/* Test the constraint on the upper bound for next work */
BOOST_AUTO_TEST_CASE(get_next_work_pow_limit)
{
    SelectParams(CBaseChainParams::MAIN);
    const Consensus::Params& params = Params().GetConsensus();

    int64_t nLastRetargetTime = 1317972665; // Block #0
    CBlockIndex pindexLast;
    pindexLast.nHeight = 719;
    pindexLast.nTime = 1364952160;  // Block #719
    pindexLast.nBits = 0x1e0ffff0;
    BOOST_CHECK_EQUAL(CalculateNextWorkRequired(&pindexLast, nLastRetargetTime, params), 0x1e3fffc0);
}

/* Test the constraint on the lower bound for actual time taken */
BOOST_AUTO_TEST_CASE(get_next_work_lower_limit_actual)
{
    SelectParams(CBaseChainParams::MAIN);
    const Consensus::Params& params = Params().GetConsensus();

    int64_t nLastRetargetTime = 1364952162; // Block #720
    CBlockIndex pindexLast;
    pindexLast.nHeight = 1439;
    pindexLast.nTime = 1364952914;  // Block #1439
    pindexLast.nBits = 0x1e3fffc0;
    BOOST_CHECK_EQUAL(CalculateNextWorkRequired(&pindexLast, nLastRetargetTime, params), 0x1e0ffff0);
}

/* Test the constraint on the upper bound for actual time taken */
BOOST_AUTO_TEST_CASE(get_next_work_upper_limit_actual)
{
    SelectParams(CBaseChainParams::MAIN);
    const Consensus::Params& params = Params().GetConsensus();

    int64_t nLastRetargetTime = 1369719352; // NOTE: Not an actual block time
    CBlockIndex pindexLast;
    pindexLast.nHeight = 72719;
    pindexLast.nTime = 1369935352;  // Block #72719
    pindexLast.nBits = 0x1c6e8b63;
    BOOST_CHECK_EQUAL(CalculateNextWorkRequired(&pindexLast, nLastRetargetTime, params), 0x1d01ba2d);
}

BOOST_AUTO_TEST_CASE(GetBlockProofEquivalentTime_test)
{
    SelectParams(CBaseChainParams::MAIN);
    const Consensus::Params& params = Params().GetConsensus();

    std::vector<CBlockIndex> blocks(10000);
    for (int i = 0; i < 10000; i++) {
        blocks[i].pprev = i ? &blocks[i - 1] : NULL;
        blocks[i].nHeight = i;
        blocks[i].nTime = 1269211443 + i * params.nPowTargetSpacing;
        blocks[i].nBits = 0x207fffff; /* target 0x7fffff000... */
        blocks[i].nChainWork = i ? blocks[i - 1].nChainWork + GetBlockProof(blocks[i - 1]) : arith_uint256(0);
    }

    for (int j = 0; j < 1000; j++) {
        CBlockIndex *p1 = &blocks[GetRand(10000)];
        CBlockIndex *p2 = &blocks[GetRand(10000)];
        CBlockIndex *p3 = &blocks[GetRand(10000)];

        int64_t tdiff = GetBlockProofEquivalentTime(*p1, *p2, *p3, params);
        BOOST_CHECK_EQUAL(tdiff, p1->GetBlockTime() - p2->GetBlockTime());
    }
}

BOOST_AUTO_TEST_SUITE_END()
