Mincoin Core 0.14.3
=====================

Setup
---------------------
Mincoin Core is the original Mincoin client and it builds the backbone of the network. However, it downloads and stores the entire history of Mincoin transactions (which is currently 1 GB); depending on the speed of your computer and network connection, the synchronization process can take anywhere from an hour to a few hours or more.

To download Mincoin Core, visit [github.com](https://github.com/mincoin/mincoin/releases/).

Running
---------------------
The following are some helpful notes on how to run Mincoin on your native platform.

### Unix

Unpack the files into a directory and run:

- `bin/mincoin-qt` (GUI) or
- `bin/mincoind` (headless)

### Windows

Unpack the files into a directory, and then run mincoin-qt.exe.

### OS X

Drag Mincoin-Core to your applications folder, and then run Mincoin-Core.

### Need Help?

* See the documentation at the [Mincoin Forum](https://www.mincoinforum.com/)
for help and more information.
* Ask for help on [#mincoin](http://webchat.freenode.net?channels=mincoin) on Freenode. If you don't have an IRC client use [webchat here](http://webchat.freenode.net?channels=mincoin).
* Ask for help on the [BitcoinTalk](https://bitcointalk.org/) forums, in the [Altcoin Discussion board](https://bitcointalk.org/index.php?board=67.0).

Building
---------------------
The following are developer notes on how to build Mincoin on your native platform. They are not complete guides, but include notes on the necessary libraries, compile flags, etc.

- [OS X Build Notes](build-osx.md)
- [Unix Build Notes](build-unix.md)
- [Windows Build Notes](build-windows.md)
- [OpenBSD Build Notes](build-openbsd.md)
- [Gitian Building Guide](gitian-building.md)

Development
---------------------
The Mincoin repo's [root README](/README.md) contains relevant information on the development process and automated testing.

- [Developer Notes](developer-notes.md)
- [Release Notes](release-notes.md)
- [Release Process](release-process.md)
- [Source Code Documentation (External Link)](https://dev.visucore.com/bitcoin/doxygen/)
- [Translation Process](translation_process.md)
- [Translation Strings Policy](translation_strings_policy.md)
- [Travis CI](travis-ci.md)
- [Unauthenticated REST Interface](REST-interface.md)
- [Shared Libraries](shared-libraries.md)
- [BIPS](bips.md)
- [Dnsseed Policy](dnsseed-policy.md)
- [Benchmarking](benchmarking.md)

### Resources
* Discuss on the [Mincoin Forum](https://www.mincoinforum.com/), in the [Development Discussion board](https://www.mincoinforum.com/index.php?/forum/13-development-discussion/).
* Discuss project-specific development on #mincoin-core-dev on Freenode. If you don't have an IRC client use [webchat here](http://webchat.freenode.net/?channels=mincoin-core-dev).
* Discuss general Mincoin development on #mincoin-dev on Freenode. If you don't have an IRC client use [webchat here](http://webchat.freenode.net/?channels=mincoin-dev).

### Miscellaneous
- [Assets Attribution](assets-attribution.md)
- [Files](files.md)
- [Fuzz-testing](fuzzing.md)
- [Reduce Traffic](reduce-traffic.md)
- [Tor Support](tor.md)
- [Init Scripts (systemd/upstart/openrc)](init.md)
- [ZMQ](zmq.md)

License
---------------------
Distributed under the [MIT software license](/COPYING).
This product includes software developed by the OpenSSL Project for use in the [OpenSSL Toolkit](https://www.openssl.org/). This product includes
cryptographic software written by Eric Young ([eay@cryptsoft.com](mailto:eay@cryptsoft.com)), and UPnP software written by Thomas Bernard.
