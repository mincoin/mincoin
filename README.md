Mincoin integration/staging tree
================================

http://www.mincoin.io

Copyright (c) 2009-2017 Bitcoin Developers
Copyright (c) 2013-2017 Mincoin Developers

What is Mincoin?
----------------

Mincoin is a nominal version of Bitcoin using scrypt as a proof-of-work algorithm.
 - 1 minute block targets for ultra fast transactions
 - Only 10 million total coins will be generated
 - 2 coins per block
 - 60 blocks to retarget difficulty

For more information, as well as an immediately useable, binary version of
the Mincoin client sofware, see http://www.mincoin.io.

License
-------

Mincoin is released under the terms of the MIT license. See `COPYING` for more
information or see http://opensource.org/licenses/MIT.

Development process
-------------------

Developers work in their own trees, then submit pull requests when they think
their feature or bug fix is ready.

If it is a simple/trivial/non-controversial change, then one of the Mincoin
development team members simply pulls it.

If it is a *more complicated or potentially controversial* change, then the patch
submitter will be asked to start a discussion with the devs and community.

The patch will be accepted if there is broad consensus that it is a good thing.
Developers should expect to rework and resubmit patches if the code doesn't
match the project's coding conventions (see `doc/coding.txt`) or are
controversial.

The `master` branch is regularly built and tested, but is not guaranteed to be
completely stable. [Tags](https://github.com/mincoin-project/mincoin/tags) are created
regularly to indicate new official, stable release versions of Mincoin.

Testing
-------

Testing and code review is the bottleneck for development; we get more pull
requests than we can review and test. Please be patient and help out, and
remember this is a security-critical project where any mistake might cost people
lots of money.

### Automated Testing

Developers are strongly encouraged to write unit tests for new code, and to
submit new unit tests for old code.

Unit tests for the core code are in `src/test/`. To compile and run them:

    cd src; make -f makefile.unix test

Unit tests for the GUI code are in `src/qt/test/`. To compile and run them:

    qmake BITCOIN_QT_TEST=1 -o Makefile.test mincoin-qt.pro
    make -f Makefile.test
    ./mincoin-qt_test

