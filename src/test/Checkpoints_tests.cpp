//
// Unit tests for block-chain checkpoints
//
#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/test/unit_test.hpp>
#include <boost/foreach.hpp>

#include "../checkpoints.h"
#include "../util.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(Checkpoints_tests)

BOOST_AUTO_TEST_CASE(sanity)
{
    uint256 p1500 = uint256("0x2eea744a7446933189ceb00078f9ce8fab68567f150aaf4ca86b42e31e43a296");
    uint256 p120000 = uint256("0xbfa8b4bf2ca7842cc5677b69ef066983daa70987d4e1ea8f72d0d2830a67fafa");
    BOOST_CHECK(Checkpoints::CheckBlock(1500, p1500));
    BOOST_CHECK(Checkpoints::CheckBlock(120000, p120000));

    
    // Wrong hashes at checkpoints should fail:
    BOOST_CHECK(!Checkpoints::CheckBlock(1500, p120000));
    BOOST_CHECK(!Checkpoints::CheckBlock(120000, p1500));

    // ... but any hash not at a checkpoint should succeed:
    BOOST_CHECK(Checkpoints::CheckBlock(1500+1, p120000));
    BOOST_CHECK(Checkpoints::CheckBlock(120000+1, p1500));

    BOOST_CHECK(Checkpoints::GetTotalBlocksEstimate() >= 120000);
}    

BOOST_AUTO_TEST_SUITE_END()
