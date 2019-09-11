Mincoin Core integration/staging tree
=====================================

[![Build Status](https://travis-ci.org/mincoin/mincoin.svg?branch=0.14)](https://travis-ci.org/mincoin/mincoin)

https://www.mincoin.us

What is Mincoin?
----------------

Mincoin is an experimental digital currency that enables instant payments to
anyone, anywhere in the world. Mincoin uses peer-to-peer technology to operate
with no central authority: managing transactions and issuing money are carried
out collectively by the network. Mincoin Core is the name of open source
software which enables the use of this currency. Mincoin is bronze to Bitcoin
gold.

 - Only 10 million total coins will be generated
 - 1 minute block target for ultra fast transactions
 - 2 coins per block
 - SplashGuard retargets difficulty after every block

Block Explorers
---------------

- [Mincoin Explorer (primary)](https://www.mincoinexplorer.com/)
- [Crypto Explore](http://cryptoexplore.com/)
- [Explore the Mincoin](https://explore-the-minco.in/)

Pools
-----

- [MincoinPool (p2pool)](https://github.com/mincoin/mincoinpool)
- [Mining-Dutch](https://www.mining-dutch.nl/)
- [CoinMinerz](http://coinminerz.com/)
- [Hash-to-Coins](https://hash-to-coins.com/)
- [Fairpool](https://fairpool.pro/)
- [Block Masters](http://blockmasters.co/)
- [NLPool](https://nlpool.nl/)
- [CoinStop](https://coinstop.me/)
- [Zergpool](https://zergpool.com/)
- [REaL Pool](http://mine.realpool.eu/)
- [A Hash Pool](https://www.ahashpool.com/)
- [AikaPool](https://aikapool.com/)
- [CryptoPool](https://cryptopool.cash/)
- [Austpool](http://austpool.com/)

Pool Explorers
--------------

- [Mining Pool Stats](https://miningpoolstats.stream/mincoin)
- [Pool Explorer](https://poolexplorer.com/coin/3819)

For more information, as well as an immediately useable, binary version of
the Mincoin Core software, see https://www.mincoin.us.

License
-------

Mincoin Core is released under the terms of the MIT license. See [COPYING](COPYING) for more
information or see https://opensource.org/licenses/MIT.

Development Process
-------------------

The `master` branch is regularly built and tested, but is not guaranteed to be
completely stable. [Tags](https://github.com/mincoin/mincoin/tags) are created
regularly to indicate new official, stable release versions of Mincoin Core.

The contribution workflow is described in [CONTRIBUTING.md](CONTRIBUTING.md).

The developer [mailing list](https://groups.google.com/d/forum/mincoin-dev)
should be used to discuss complicated or controversial changes before working
on a patch set.

Developer IRC can be found on Freenode at #mincoin-dev.

Testing
-------

Testing and code review is the bottleneck for development; we get more pull
requests than we can review and test on short notice. Please be patient and help out by testing
other people's pull requests, and remember this is a security-critical project where any mistake might cost people
lots of money.

### Automated Testing

Developers are strongly encouraged to write [unit tests](src/test/README.md) for new code, and to
submit new unit tests for old code. Unit tests can be compiled and run
(assuming they weren't disabled in configure) with: `make check`. Further details on running
and extending unit tests can be found in [/src/test/README.md](/src/test/README.md).

There are also [regression and integration tests](/qa) of the RPC interface, written
in Python, that are run automatically on the build server.
These tests can be run (if the [test dependencies](/qa) are installed) with: `qa/pull-tester/rpc-tests.py`

The Travis CI system makes sure that every pull request is built for Windows, Linux, and OS X, and that unit/sanity tests are run automatically.

### Manual Quality Assurance (QA) Testing

Changes should be tested by somebody other than the developer who wrote the
code. This is especially important for large or high-risk changes. It is useful
to add a test plan to the pull request description if testing the changes is
not straightforward.

Translations
------------

We only accept translation fixes that are submitted through [Bitcoin Core's Transifex page](https://www.transifex.com/projects/p/bitcoin/).
Translations are converted to Mincoin periodically.
