// Copyright (c) 2009-2017 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    // How many times we expect transactions after the last checkpoint to
    // be slower. This number is a compromise, as it can't be accurate for
    // every system. When reindexing from a fast disk with a slow CPU, it
    // can be up to 20, while when downloading from a slow network with a
    // fast multicore CPU, it won't be much higher than 1.
    static const double fSigcheckVerificationFactor = 5.0;

    struct CCheckpointData {
        const MapCheckpoints *mapCheckpoints;
        int64 nTimeLastCheckpoint;
        int64 nTransactionsLastCheckpoint;
        double fTransactionsPerDay;
    };

    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
        (   1500, uint256("0x2eea744a7446933189ceb00078f9ce8fab68567f150aaf4ca86b42e31e43a296"))
        (   4032, uint256("0x13031071c3ce42d97d347509d6a776d1d0ee16aa6cfdd878ea8ed30674e49a17"))
        (   8064, uint256("0x0e0d78a82aba2d5b4b58da1c113b379efab7d2471794216e6815b2e2306eefec"))
        (  16128, uint256("0xcc5d209ffd47e0f7ae904f5175f9b4e13433019184bb2e04823ffcac5ddaaf7c"))
        (  23420, uint256("0x53451a078d34207e0ec113ba1b03e9ddcac55f83bb5738678b1cb3cb092f98c0"))
        (  50000, uint256("0xc3278f6135f12693d27826858766eb16ea1aecbb49ea144de7eb0ed8d686c35f"))
        (  80000, uint256("0x6f836358452fb4cb2c688755f199b766a9fd09687b5aa91cc77dd5589ea5e07b"))
        ( 120000, uint256("0xbfa8b4bf2ca7842cc5677b69ef066983daa70987d4e1ea8f72d0d2830a67fafa"))
        ( 161500, uint256("0xf0bf13d3f0362d302699ee5c3e475d22b9e8347100a5b9aa4d22b484147e84f8"))
        ( 179620, uint256("0x96317650b8916f1d609276e24dad569636f1ad1978902c76deedc6085e89d4ba"))
        ( 240000, uint256("0xcf2014e087d048b168f785b8d175bd653559442909ea8334648504ebdf8b10e7"))
        ( 383640, uint256("0x4879989175bbd5c7ed25aa977510d78bba86fbca5c484edec05817c14de9cc97"))
        ( 409004, uint256("0xb2cb4414c203bcbbbce727b8fd4f68310ae7201305ab9975e7d0a2e2ff78245a"))
        ( 456000, uint256("0x9f83973136116bd70c98618698e02a6ed8a49d9da1440d74f7eb3d06893052ce"))
        ( 541794, uint256("0xd194da1fd16bb5f764cdba993b9ca816017dc16b57cc44c02744cfcc4eb699bb"))
        ( 585010, uint256("0x395592210cf8562c7fa5332b55a3ea65d7b366aae57124a86a3f2d5935338439"))
        ( 638902, uint256("0xd4fe4f5466dacc701445a9c741046d9f91a0f85cbcc63246c6c53b9dac5e8aa8"))
        ( 700000, uint256("0xf0fa5ad2acf2ec8cee0b1da02e6c878615944b14fa55bb467b5ea4b43e500cbb"))
        ( 800000, uint256("0x3611c1a19aabf2e23488b0d0397f2f2f89d90ee0f8e2d09cd95b57ed30b12c36"))
        ( 900000, uint256("0x401c1d320b94ee32471768da5317336412fb2c7ce862a8e47f7ce44a3785b20a"))
        (1000000, uint256("0xa3912eb1080b87a6d45a47bb1b4e4792b04eeacbd183aa4c5b29fd122c0a0cbb"))
        (1100000, uint256("0xf4fecd9c37d7ade4cc7d5c1b0524f92d23ea86416ac3f35247be7ccf7b20d3e6"))
        (1200000, uint256("0x609e764bfbaa38c459954439c9774464dd4c5d6688fb6f5fd83bc90f43c5f4e5"))
        (1300000, uint256("0x88060ed1d054e6b8949caaf69046d6eb18007599a07d40b69fa8be0c1d67352f"))
        (1350000, uint256("0x025a46315bd4a5f4b360ebd865281c4fa81bd3e7d4d7814a8a0d408e8a275659"))
        (1369835, uint256("0xcfa31addb0f3c01634529f3bd4415b01fbc67c5b2aa61f40ef015b9673e72df2"))
        (1383779, uint256("0xc2fd9b8e06d9f98bfb1d18bddd69a0e87aab6980d650bc5f4753e523604ccfab"))
        (1402079, uint256("0x2cba7e55d671d5e4018619ef929baea9c147a460ee6db49084cb4dfad476c320"))
        ;
    static const CCheckpointData data = {
        &mapCheckpoints,
        1503487902, // * UNIX timestamp of last checkpoint block
        1608940,    // * total number of transactions between genesis and last checkpoint
                    //   (the tx=... number in the SetBestChain debug.log lines)
        17500.0     // * estimated number of transactions per day after checkpoint
    };

    static MapCheckpoints mapCheckpointsTestnet =
        boost::assign::map_list_of
        (   546, uint256("0xe3578f91601c7f876ae18932036cbd1d638420bf362c316873cd4022ab8a4fa9"))
        (  1439, uint256("0x1d3cf90a8870bb0d81256fd45a02a57aa17875ffeef5444df2812a7e285269a3"))
        (  2879, uint256("0x16bfabd16f65feefea3644e82f639d073d656642a55f7ab42a52698ffbcdfaaa"))
        (  4319, uint256("0x26b0333266a169ded44297a885b2ed562f2167adfb96b68ee5b2049cbfe16e2d"))
        ( 11519, uint256("0x350d02262e7f1578701e0ca52786dc217fe51dd307cd6dd992b8c97744b97bdf"))
        ;
    static const CCheckpointData dataTestnet = {
        &mapCheckpointsTestnet,
        1502840987,
        11520,
        1440
    };

    const CCheckpointData &Checkpoints() {
        if (fTestNet)
            return dataTestnet;
        else
            return data;
    }

    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (!GetBoolArg("-checkpoints", true))
            return true;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        MapCheckpoints::const_iterator i = checkpoints.find(nHeight);
        if (i == checkpoints.end()) return true;
        return hash == i->second;
    }

    // Guess how far we are in the verification process at the given block index
    double GuessVerificationProgress(CBlockIndex *pindex) {
        if (pindex==NULL)
            return 0.0;

        int64 nNow = time(NULL);

        double fWorkBefore = 0.0; // Amount of work done before pindex
        double fWorkAfter = 0.0;  // Amount of work left after pindex (estimated)
        // Work is defined as: 1.0 per transaction before the last checkoint, and
        // fSigcheckVerificationFactor per transaction after.

        const CCheckpointData &data = Checkpoints();

        if (pindex->nChainTx <= data.nTransactionsLastCheckpoint) {
            double nCheapBefore = pindex->nChainTx;
            double nCheapAfter = data.nTransactionsLastCheckpoint - pindex->nChainTx;
            double nExpensiveAfter = (nNow - data.nTimeLastCheckpoint)/86400.0*data.fTransactionsPerDay;
            fWorkBefore = nCheapBefore;
            fWorkAfter = nCheapAfter + nExpensiveAfter*fSigcheckVerificationFactor;
        } else {
            double nCheapBefore = data.nTransactionsLastCheckpoint;
            double nExpensiveBefore = pindex->nChainTx - data.nTransactionsLastCheckpoint;
            double nExpensiveAfter = (nNow - pindex->nTime)/86400.0*data.fTransactionsPerDay;
            fWorkBefore = nCheapBefore + nExpensiveBefore*fSigcheckVerificationFactor;
            fWorkAfter = nExpensiveAfter*fSigcheckVerificationFactor;
        }

        return fWorkBefore / (fWorkBefore + fWorkAfter);
    }

    int GetTotalBlocksEstimate()
    {
        if (!GetBoolArg("-checkpoints", true))
            return 0;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        return checkpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (!GetBoolArg("-checkpoints", true))
            return NULL;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, checkpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }
}
